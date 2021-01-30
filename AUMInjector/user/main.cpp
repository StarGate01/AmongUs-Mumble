// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "il2cpp-init.h"
#include "il2cpp-appdata.h"
#include "helpers.h"

#include "MumbleLink.h"
#include "deobfuscate.h"
#include "GameData.h"
#include "settings.h"
#include "LoggingSystem.h"
#include "MumblePlayer.h"
#include "GUI.h"
#include "Input.h"
//#include "dynamic_analysis.h"

using namespace app;

extern HANDLE hExit; // Thread exit event

// Game state
InnerNetClient_GameState__Enum lastGameState = InnerNetClient_GameState__Enum_Joined;

// Try to reconnect every 3s until program unloads or mumble connects
void TryConnectMumble()
{
    unsigned int attempt = 1;
    while (mumbleLink.linkedMem == nullptr && WaitForSingleObject(hExit, 3000) == WAIT_TIMEOUT)
    {
        DWORD mumbleError = mumbleLink.Init();
        if (mumbleError != NO_ERROR)
        {
            logger.LogVariadic(LOG_CODE::WRN, true, "Could not init Mumble link: %d, attempt %d", mumbleError, attempt);
            attempt++;
        }
        else
        {
            logger.LogVariadic(LOG_CODE::INF, false, "Mumble link init successful, attempt %d", attempt);
            mumblePlayer.TryLogPosition(true);
            mumbleLink.Mute(false);
        }
    }
}

// Awake call for the Game Data object, hook used to grab the singleton pointer
void GameData_Awake_Hook(GameData* __this, MethodInfo* method)
{
    GameData_Awake_Trampoline(__this, method);
    AUM::Game::SetGameData(__this);
}

// Hook for color updates
void GameData_UpdateColor_Hook(GameData* __this, uint8_t playerId, uint8_t colorId, MethodInfo* method)
{
    GameData_UpdateColor_Trampoline(__this, playerId, colorId, method);
}


// Fixed loop for a player object, but only get called when a player moves
void PlayerControl_FixedUpdate_Hook(PlayerControl* __this, MethodInfo* method)
{
    PlayerControl_FixedUpdate_Trampoline(__this, method);
    // This is a "hacky" but very fast check to see if this event is from the local player
    bool isClient = __this->fields.LightPrefab != nullptr;
    if (isClient)
    {
        // Cache position
        Vector2 pos = PlayerControl_GetTruePosition_Trampoline(__this, method);
        mumblePlayer.SetPosX(pos.x);
        mumblePlayer.SetPosY(pos.y);

        // Cache network ID
        mumblePlayer.SetNetID(__this->fields._.NetId);

        // From Player Control, get the Player Data
        PlayerData* Data = PlayerControl_GetData_Trampoline(__this, NULL);
        // And now we can get if we are imposter.
        bool isImposter = Data->fields.*IsImposter;
        mumblePlayer.SetImposter(isImposter);

        // Set if player is using radio
        mumblePlayer.SetUsingRadio(inputSingleton.GetKey(appSettings.radioKey));

        // Check if player is imposter and using radio
        if (mumblePlayer.IsImposter() && mumblePlayer.IsUsingRadio())
        {
            logger.Log(LOG_CODE::MSG, "Imposter Radio");
            // Location is moved to internal value in update player next loop.
        }
    }

}

// Gets called when a player dies
void PlayerControl_Die_Hook(PlayerControl* __this, Player_Die_Reason__Enum reason, MethodInfo* method)
{
    PlayerControl_Die_Trampoline(__this, reason, method);

    if (__this->fields.LightPrefab != nullptr)
    {
        logger.Log(LOG_CODE::MSG, "You died");
        mumblePlayer.EnterGhostState();
    }
}

// Gets called when a meeting ends
void MeetingHud_Close_Hook(MeetingHud* __this, MethodInfo* method)
{
    MeetingHud_Close_Trampoline(__this, method);
    logger.Log(LOG_CODE::MSG, "Meeting ended");
    // Spectators aren't allowd to talk
    mumblePlayer.EndMeeting();
}

// Gets called when a meeting starts
void MeetingHud_Start_Hook(MeetingHud* __this, MethodInfo* method)
{
    MeetingHud_Start_Trampoline(__this, method);
    logger.Log(LOG_CODE::MSG, "Meeting started");
    // Mute ALL ghosts
    mumblePlayer.StartMeeting();
}

// Broadcast the current settings
void BroadcastSettings(InnerNetClient* client)
{
    logger.Log(LOG_CODE::MSG, "Sending configuration: " + appSettings.HumanReadableSync());

    // Broadcast config via RPC
    MessageWriter* writer = InnerNetClient_StartRpc_Trampoline(client, mumblePlayer.GetNetID(), SYNC_RPC_ID, SendOption__Enum_Reliable, NULL);
    MessageWriter_Write_Byte_Trampoline(writer, SYNC_VERSION, NULL);
    // Serialize settings
    MessageWriter_Write_Byte_Trampoline(writer, (int8_t)appSettings.ghostVoiceMode, NULL);
    MessageWriter_Write_Byte_Trampoline(writer, appSettings.directionalAudio? 1:0, NULL);
    MessageWriter_EndMessage(writer, NULL);
}

// Broadcast the current settings
void ImposterRadioUse(InnerNetClient* client)
{
    logger.Log(LOG_CODE::MSG, "Imposter Radio Useage is sent");

    // Broadcast radio usage via RPC
    MessageWriter* writer = InnerNetClient_StartRpc_Trampoline(client, mumblePlayer.GetNetID(), IMPOSTER_RADIO_RPC_ID, SendOption__Enum_Reliable, NULL);
    MessageWriter_EndMessage(writer, NULL);
}

// Fixed loop for the game client
void InnerNetClient_FixedUpdate_Hook(InnerNetClient* __this, MethodInfo* method)
{
    InnerNetClient_FixedUpdate_Trampoline(__this, method);

    // Set if player is host
    mumblePlayer.SetHost(__this->fields.ClientId == __this->fields.HostId);

    // Check if the host should broadcast the settings due to GUI change
    if (appSettings.mustBroadcast && mumblePlayer.IsHost())
    {
        // Only broadcast at most every second to prevent network overload
        long long timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
        if ((timestamp - appSettings.lastBroadcastMs) >= 1000)
        {
            BroadcastSettings(__this);
            appSettings.mustBroadcast = false;
            appSettings.lastBroadcastMs = timestamp;
        }
    }

    if (mumblePlayer.IsImposter()) {
        long long timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
        if(mumblePlayer.IsUsingRadio()) 
        {
            // Only broadcast at most every second to prevent network overload
            if ((timestamp - appSettings.lastBroadcastRadioMs) >= 500)
            {
                ImposterRadioUse(__this);
                appSettings.lastBroadcastRadioMs = timestamp;
                mumblePlayer.SetLastRadioReceived(timestamp);
                mumblePlayer.SetRadioInUse(true);
            }
        }
        else {
            if ((timestamp - mumblePlayer.LastRadioReceived()) >= 600)
            {
                appSettings.lastBroadcastRadioMs = 0;
                mumblePlayer.SetLastRadioReceived(0);
                mumblePlayer.SetRadioInUse(false);
            }
        }
    }

    // Check if game state changed to lobby
    if (__this->fields.GameState != lastGameState)
    {
        if (__this->fields.GameState == InnerNetClient_GameState__Enum_Joined ||
            __this->fields.GameState == InnerNetClient_GameState__Enum_Ended)
        {
            logger.Log(LOG_CODE::MSG, "Game joined or ended");

            // Reset options to local version
            appSettings.Parse();
            mumblePlayer.ResetState();
            mumblePlayer.EnterLobby();
        }
        else if (__this->fields.GameState == InnerNetClient_GameState__Enum_Started)
        {
            logger.Log(LOG_CODE::MSG, "Round started");

            // Just to be sure in case some join events were missed
            if(mumblePlayer.IsHost()) appSettings.mustBroadcast = true;
            mumblePlayer.EnterGame();
        }
    }

    lastGameState = __this->fields.GameState;

    if (mumbleLink.linkedMem != nullptr)
    {
        // Update mumble info
        // Map player position to mumble according to directional / non directional setting
        #define UPDATEBLOCK(T, F, CW) { \
        if (((T)mumbleLink.linkedMem)->uiVersion != 2) \
        { \
            memcpy(((T)mumbleLink.linkedMem)->name, F##"Among Us\0", 9 * CW); \
			memcpy(((T)mumbleLink.linkedMem)->description, F##"Among Us support via the Link plugin.\0", 38 * CW); \
            ((T)mumbleLink.linkedMem)->uiVersion = 2; \
		} \
        ((T)mumbleLink.linkedMem)->uiTick++; \
		for (int i = 0; i < 3; i++) \
		{ \
            ((T)mumbleLink.linkedMem)->fAvatarPosition[i] = mumblePlayer.GetMumblePos(i); \
            ((T)mumbleLink.linkedMem)->fCameraPosition[i] = mumblePlayer.GetMumblePos(i); \
		} }
        if (mumbleLink.IsWine()) UPDATEBLOCK(LinkedMemWine*, U, 4)
        else UPDATEBLOCK(LinkedMemWindows*, L, 2)
        #undef UPDATEBLOCK
	}
	mumblePlayer.TryLogPosition();
}

// Gets called when the client disconencts for whatsever reason
void InnerNetClient_Disconnect_Hook(InnerNetClient* __this, InnerNet_DisconnectReasons__Enum reason, String* stringReason, MethodInfo* method)
{
    InnerNetClient_Disconnect_Trampoline(__this, reason, stringReason, method);
    logger.Log(LOG_CODE::MSG, "Disconnected from server");
    mumblePlayer.ResetState();
    mumblePlayer.ExitGame();
}

// Comms sabotage helper
void UpdateComms(bool isSabotaged)
{
    if (isSabotaged)
    {
        logger.Log(LOG_CODE::MSG, "Comms sabotaged");
        mumblePlayer.StartCommunicationsSabotaged();
    }
    else
    {
        logger.Log(LOG_CODE::MSG, "Comms repaired");
        mumblePlayer.EndCommunicationsSabotaged();
    }
}

// Gets called when comms on Mira HQ get sabotaged
void HqHudOverrideTask_Initialize_Hook(HqHudOverrideTask* __this, MethodInfo* method)
{
    HqHudOverrideTask_Initialize_Trampoline(__this, method);
    UpdateComms(true);
}

// Gets called when comms on Mira HQ get repaired
void HqHudOverrideTask_Complete_Hook(HqHudOverrideTask* __this, MethodInfo* method)
{
    HqHudOverrideTask_Complete_Trampoline(__this, method);
    UpdateComms(false);
}

// Gets called when comms on Skeld or Polus get sabotaged
void HudOverrideTask_Initialize_Hook(HudOverrideTask* __this, MethodInfo* method)
{
    HudOverrideTask_Initialize_Trampoline(__this, method);
    UpdateComms(true);
}

// Gets called when comms on Skeld or Polus get repaired
void HudOverrideTask_Complete_Hook(HudOverrideTask* __this, MethodInfo* method)
{
    HudOverrideTask_Complete_Trampoline(__this, method);
    UpdateComms(false);
}

// Gets called when a player joins
void AmongUsClient_OnPlayerJoined_Hook(AmongUsClient* __this, ClientData* data, MethodInfo* method)
{
    AmongUsClient_OnPlayerJoined_Trampoline(__this, data, method);
    logger.Log(LOG_CODE::MSG, "Player joined lobby");

    // New player joins -> Re-broadcast settings from host
    // Only if joining player is not host
    if ((__this->fields._.ClientId == __this->fields._.HostId) &&  
        (data->fields.Id != __this->fields._.HostId))
    {
        appSettings.mustBroadcast = true;
    }
}

//// This sets the keypad on mirahq to 10% speed for testing
//void IGHKMHLJFLI_Detoriorate_Hook(IGHKMHLJFLI* __this, float PCHPGLOMPLD, MethodInfo* method)
//{
//    IGHKMHLJFLI_Detoriorate(__this, PCHPGLOMPLD * 0.1f, method);
//}

// Gets called when a game data packet is received
void InnerNetClient_HandleGameDataInner_Hook(InnerNetClient* __this, MessageReader* reader, int32_t count, MethodInfo* method)
{
    // Tag 2 = RPC call
    if (reader->fields.Tag == 2)
    {
        // Read packet header
        int32_t pos = MessageReader_get_Position(reader, NULL);
        uint32_t targetObject = MessageReader_ReadPackedUInt32(reader, NULL); // Ignored
        uint8_t rpcId = MessageReader_ReadByte(reader, NULL);
        
        // Check if this is a mod config packet
        if (rpcId == SYNC_RPC_ID)
        {
            // Validate packet
            int32_t packetSize = MessageReader_get_BytesRemaining(reader, NULL);
            if (packetSize == 0)
            {
                logger.Log(LOG_CODE::ERR, "Got bad configuration (empty payload), ignoring");
                return;
            }
            uint8_t version = MessageReader_ReadByte(reader, NULL);
            if (version != SYNC_VERSION)
            {
                logger.Log(LOG_CODE::ERR, "Got bad configuration (wrong version), ignoring");
                return;
            }
            packetSize = MessageReader_get_BytesRemaining(reader, NULL);
            if (packetSize != SYNC_SIZE)
            {
                logger.Log(LOG_CODE::ERR, "Got bad configuration (invalid payload size), ignoring");
                return;
            }

            // Read configuration
            appSettings.ghostVoiceMode = (Settings::GHOST_VOICE_MODE)MessageReader_ReadByte(reader, NULL);
            appSettings.directionalAudio = (MessageReader_ReadByte(reader, NULL) == 1);
            appSettings.RecalculateAudioMap();
            logger.Log(LOG_CODE::MSG, "Got configuration: " + appSettings.HumanReadableSync());

            // Swallow this packet
            return;
        }
        // Check if this is an imposter radio call
        else if (rpcId == IMPOSTER_RADIO_RPC_ID) 
        {
            if (mumblePlayer.IsImposter()) {
                long long timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count();
                mumblePlayer.SetLastRadioReceived(timestamp);
                mumblePlayer.SetRadioInUse(true);
            }

            // Swallow this packet
            return;
        }
        else
        {

            // Rewind reader to allow reparsing packet in trampoline
            MessageReader_set_Position(reader, pos, NULL);
        }
    }

    InnerNetClient_HandleGameDataInner_Trampoline(__this, reader, count, method);
}

// Entrypoint of the injected thread
void Run()
{
    // Check what process the dll was loaded into
    // If loaded into the wrong process, exit injected thread
    TCHAR hostExe[MAX_PATH];
    GetModuleFileName(NULL, hostExe, MAX_PATH);
    char filename[_MAX_FNAME];
    _splitpath_s(hostExe, NULL, 0, NULL, 0, filename, _MAX_FNAME, NULL, 0);
    if (strcmp(filename, "Among Us") == 0)
    {
        // Load settings
        bool parseOk = appSettings.Parse();
        // Setup the logger
        logger.SetVerbosity(appSettings.logVerbosity);
        if (!appSettings.disableLogConsole) logger.EnableConsoleLogging();
        if (!appSettings.disableLogFile) logger.EnableFileLogging(appSettings.logFileName);

        // Credits & Info
        logger.Log(LOG_CODE::ERR, CREDITS, false);

        logger.LogVariadic(LOG_CODE::INF, false, "Compiled for game version %s", version_text);
        logger.Log(LOG_CODE::INF, "DLL hosting successful");
        if (mumbleLink.IsWine())
        {
            logger.Log(LOG_CODE::INF, "Running on Wine");
            if (appSettings.disableDirectx) logger.Log(LOG_CODE::INF, "DirectX hooks are disabled.");
            else logger.Log(LOG_CODE::INF, "DirectX hooks are enabled. Make sure your system and Wine installation support this.");
        }
        else
        {
            logger.Log(LOG_CODE::INF, "Running on Windows");
            if (appSettings.disableDirectx) logger.Log(LOG_CODE::INF, "DirectX hooks are disabled, but Windows supports them.");
            else logger.Log(LOG_CODE::INF, "DirectX hooks are enabled.");
        }

        // Print current config
        if (!parseOk)
        {
            logger.Log(LOG_CODE::ERR, "Error parsing configuration or command line!");
            logger.Log(LOG_CODE::ERR, "Falling back to default configuration");
        }
        logger.Log(LOG_CODE::MSG, "Current configuration:\n");
        logger.Log(LOG_CODE::MSG, appSettings.app.config_to_str(true, false) + "\n", false);

        // Setup type and memory info
        logger.Log(LOG_CODE::MSG, "Waiting 10s for Unity to load");
        Sleep(10000);
        init_il2cpp();
        logger.Log(LOG_CODE::INF, "Type and function memory mapping successful");

        // Print game version
        String* gameVersionRaw = Application_get_version(NULL);
        std::wstring_convert<std::codecvt_utf8<wchar_t>> wideToNarrow;
        std::string gameVersion = wideToNarrow.to_bytes(std::wstring((const wchar_t*)
            (&((Il2CppString*)gameVersionRaw)->chars), ((Il2CppString*)gameVersionRaw)->length));
        logger.Log(LOG_CODE::INF, "Running in game version " + gameVersion);

        // Start mumble connection thread
        std::thread mumbleReconnectionThread(TryConnectMumble);

		// Setup hooks
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
        if (!appSettings.disableDirectx) GUIDetourAttach();
		DetourAttach(&(PVOID&)PlayerControl_FixedUpdate_Trampoline, PlayerControl_FixedUpdate_Hook);
		DetourAttach(&(PVOID&)PlayerControl_Die_Trampoline, PlayerControl_Die_Hook);
		DetourAttach(&(PVOID&)GameData_Awake_Trampoline, GameData_Awake_Hook);
		DetourAttach(&(PVOID&)GameData_UpdateColor_Trampoline, GameData_UpdateColor_Hook);
		DetourAttach(&(PVOID&)MeetingHud_Close_Trampoline, MeetingHud_Close_Hook);
		DetourAttach(&(PVOID&)MeetingHud_Start_Trampoline, MeetingHud_Start_Hook);
		DetourAttach(&(PVOID&)InnerNetClient_FixedUpdate_Trampoline, InnerNetClient_FixedUpdate_Hook);
		DetourAttach(&(PVOID&)InnerNetClient_Disconnect_Trampoline, InnerNetClient_Disconnect_Hook);
        DetourAttach(&(PVOID&)HqHudOverrideTask_Initialize_Trampoline, HqHudOverrideTask_Initialize_Hook);
        DetourAttach(&(PVOID&)HqHudOverrideTask_Complete_Trampoline, HqHudOverrideTask_Complete_Hook);
        DetourAttach(&(PVOID&)HudOverrideTask_Initialize_Trampoline, HudOverrideTask_Initialize_Hook);
        DetourAttach(&(PVOID&)HudOverrideTask_Complete_Trampoline, HudOverrideTask_Complete_Hook);
        DetourAttach(&(PVOID&)AmongUsClient_OnPlayerJoined_Trampoline, AmongUsClient_OnPlayerJoined_Hook);
        DetourAttach(&(PVOID&)InnerNetClient_HandleGameDataInner_Trampoline, InnerNetClient_HandleGameDataInner_Hook);
        //DetourAttach(&(PVOID&)IGHKMHLJFLI_Detoriorate, IGHKMHLJFLI_Detoriorate_Hook);

        //dynamic_analysis_attach();
        LONG errDetour = DetourTransactionCommit();
        if (errDetour == NO_ERROR) logger.Log(LOG_CODE::INF, "Successfully detoured game functions");
        else logger.LogVariadic(LOG_CODE::ERR, false, "Detouring game functions failed: %d", errDetour);

        // Wait for thread exit and then clean up
        WaitForSingleObject(hExit, INFINITE);
        mumbleLink.Close();
        logger.Log(LOG_CODE::MSG, "Unloading done");
    }
}