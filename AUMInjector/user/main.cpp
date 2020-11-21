// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <limits>
#include <thread>
#include <codecvt>
#include "il2cpp-init.h"
#include "il2cpp-appdata.h"
#include "helpers.h"
#include <detours.h>
#include "MumbleLink.h"
#include "deobfuscate.h"
#include "settings.h"
#include "LoggingSystem.h"
#include "MumblePlayer.h"
#include "GUI.h"
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

// Fixed loop for a player object, but only get called when a player moves
void PlayerControl_FixedUpdate_Hook(PlayerControl* __this, MethodInfo* method)
{
    PlayerControl_FixedUpdate_Trampoline(__this, method);
    
    if (__this->fields.LightPrefab != nullptr)
    {
        // Cache position
        Vector2 pos = PlayerControl_GetTruePosition_Trampoline(__this, method);
        mumblePlayer.SetPosX(pos.x);
        mumblePlayer.SetPosY(pos.y);
        // Cache network ID
        mumblePlayer.netID = __this->fields._.NetId;
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

// Fixed loop for the game client
void InnerNetClient_FixedUpdate_Hook(InnerNetClient* __this, MethodInfo* method)
{
    InnerNetClient_FixedUpdate_Trampoline(__this, method);

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
            mumblePlayer.ExitGame();

            // For testing ghost voice modes (set user to "ghost" by default)
            //        Sleep(1000);
            //        mumblePlayer.EnterGhostState();
        }
        else if (__this->fields.GameState == InnerNetClient_GameState__Enum_Started)
        {
            logger.Log(LOG_CODE::MSG, "Round started");

            mumblePlayer.EnterGame();

            // Check if client is hosting
            if (__this->fields.ClientId == __this->fields.HostId)
            {
                logger.Log(LOG_CODE::MSG, "Sending configuration: " + appSettings.HumanReadableSync());

                // Broadcast config via chat
                std::string messageText = SYNC_HEADER + appSettings.SerializeSync();
                String* messageString = (String*)il2cpp_string_new(messageText.c_str());
                MessageWriter* writer = InnerNetClient_StartRpc(__this, mumblePlayer.netID, 13, SendOption__Enum_Reliable, method);
                MessageWriter_Write_String(writer, messageString, method);
                MessageWriter_EndMessage(writer, NULL);
            }
            else
            {
                logger.Log(LOG_CODE::MSG, "Will not broadcast configuration, waiting for host");
            }
        }
    }
    lastGameState = __this->fields.GameState;

    if (mumbleLink.linkedMem != nullptr)
    {
        if (mumbleLink.linkedMem->uiVersion != 2)
        {
            wcsncpy_s(mumbleLink.linkedMem->name, L"Among Us", 256);
			wcsncpy_s(mumbleLink.linkedMem->description, L"Among Us support via the Link plugin.", 2048);
			mumbleLink.linkedMem->uiVersion = 2;
		}
		mumbleLink.linkedMem->uiTick++;

		// Map player position to mumble according to directional / non directional setting
		for (int i = 0; i < 3; i++)
		{
			mumbleLink.linkedMem->fAvatarPosition[i] = mumblePlayer.GetMumblePos(i);
			mumbleLink.linkedMem->fCameraPosition[i] = mumblePlayer.GetMumblePos(i);
		}
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

//// This sets the keypad on mirahq to 10% speed for testing
//void IGHKMHLJFLI_Detoriorate_Hook(IGHKMHLJFLI* __this, float PCHPGLOMPLD, MethodInfo* method)
//{
//    IGHKMHLJFLI_Detoriorate(__this, PCHPGLOMPLD * 0.1f, method);
//}

// gets called when a chat message is received
std::wstring_convert<std::codecvt_utf8<wchar_t>> wideToNarrow;
void ChatController_AddChat_Hook(ChatController* __this, PlayerControl* sourcePlayer, String* chatText, MethodInfo* method)
{
    // Convert chat message to string
    std::string messageText = wideToNarrow.to_bytes(std::wstring((const wchar_t*)(&((Il2CppString*)chatText)->chars), ((Il2CppString*)chatText)->length));
    if (messageText.at(0) == SYNC_HEADER)
    {
        // Strip header character
        std::string config = messageText.substr(1, std::string::npos);

        // Parse config string
        int result = appSettings.DeserializeSync(config);
        switch (result)
        {
        case SYNC_SUCCESS:
            logger.Log(LOG_CODE::INF, "Got configuration: " + appSettings.HumanReadableSync());
            break;
        case SYNC_ERROR_NUM_ARGS:
            logger.Log(LOG_CODE::ERR, "Got bad configuration (invalid number of arguments), ignoring");
            break;
        case SYNC_ERROR_VERSION:
            logger.Log(LOG_CODE::ERR, "Got bad configuration (incompatible version), ignoring");
            break;
        case SYNC_ERROR_FORMAT:
            logger.Log(LOG_CODE::ERR, "Got bad configuration (invalid format), ignoring");
            break;
        }

        // Swallow message if it was a config
        return;
    }

    ChatController_AddChat_Trampoline(__this, sourcePlayer, chatText, method);
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
        appSettings.Parse();
        // Setup the logger
        logger.SetVerbosity(appSettings.logVerbosity);
        if (!appSettings.disableLogConsole) logger.EnableConsoleLogging();
        if (!appSettings.disableLogFile) logger.EnableFileLogging(appSettings.logFileName);

        // Credits & Info
        logger.Log(LOG_CODE::ERR, CREDITS, false);

        logger.LogVariadic(LOG_CODE::INF, false, "Compiled for game version %s", version_text);
        logger.Log(LOG_CODE::INF, "DLL hosting successful");

        // Print current config
        logger.Log(LOG_CODE::MSG, "Current configuration:\n");
        logger.Log(LOG_CODE::MSG, appSettings.app.config_to_str(true, false) + "\n", false);

		// Setup type and memory info
		logger.Log(LOG_CODE::MSG, "Waiting 10s for Unity to load");
		Sleep(10000);
		init_il2cpp();
		logger.Log(LOG_CODE::INF, "Type and function memory mapping successful");

        // Start mumble connection thread
        std::thread mumbleReconnectionThread(TryConnectMumble);

		// Setup hooks
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
        GUIDetourAttach();
		DetourAttach(&(PVOID&)PlayerControl_FixedUpdate_Trampoline, PlayerControl_FixedUpdate_Hook);
		DetourAttach(&(PVOID&)PlayerControl_Die_Trampoline, PlayerControl_Die_Hook);
		DetourAttach(&(PVOID&)MeetingHud_Close_Trampoline, MeetingHud_Close_Hook);
		DetourAttach(&(PVOID&)MeetingHud_Start_Trampoline, MeetingHud_Start_Hook);
		DetourAttach(&(PVOID&)InnerNetClient_FixedUpdate_Trampoline, InnerNetClient_FixedUpdate_Hook);
		DetourAttach(&(PVOID&)InnerNetClient_Disconnect_Trampoline, InnerNetClient_Disconnect_Hook);
        DetourAttach(&(PVOID&)HqHudOverrideTask_Initialize_Trampoline, HqHudOverrideTask_Initialize_Hook);
        DetourAttach(&(PVOID&)HqHudOverrideTask_Complete_Trampoline, HqHudOverrideTask_Complete_Hook);
        DetourAttach(&(PVOID&)HudOverrideTask_Initialize_Trampoline, HudOverrideTask_Initialize_Hook);
        DetourAttach(&(PVOID&)HudOverrideTask_Complete_Trampoline, HudOverrideTask_Complete_Hook);
        DetourAttach(&(PVOID&)ChatController_AddChat_Trampoline, ChatController_AddChat_Hook);
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
