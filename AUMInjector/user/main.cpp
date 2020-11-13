// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <limits>
#include "il2cpp-init.h"
#include "il2cpp-appdata.h"
#include "helpers.h"
#include <detours.h>
#include "MumbleLink.h"
#include "deobfuscate.h"
#include "settings.h"
#include "LoggingSystem.h"
//#include "dynamic_analysis.h"

using namespace app;

extern HANDLE hExit; // Thread exit event

// Game state
float posCache[2] = { 0.0f, 0.0f };
bool sendPosition = true;
InnerNetClient_GameState__Enum lastGameState = InnerNetClient_GameState__Enum_Joined;

// Couters for tracking when to print the position
unsigned int frameCounter = 0;
const unsigned int framesToPrintPosition = 15;
// Start old cache as an impossible limit, for first-frame printing
float prevPosCache[2] = { std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest() };
// Position difference treshold for printing
float cachePosEpsilon = 0.001f;

// Will log the position, if needed
void TryLogPosition(bool isLinked) 
{
    // Only print the player position every so many frames, and if it has changed
    if (++frameCounter > framesToPrintPosition && 
            (std::abs(prevPosCache[0] - posCache[0]) > cachePosEpsilon ||
            std::abs(prevPosCache[1] - posCache[1]) > cachePosEpsilon)
       )
    {
        frameCounter = 0;
        // Store the old position
        prevPosCache[0] = posCache[0];
        prevPosCache[1] = posCache[1];
        // Log the current player position to let the player know it is working
        logger.LogVariadic(LOG_CODE::MSG, true, "%s - Position: (%.3f, %.3f)      ", 
            (isLinked ? "Linked" : "Not linked"), posCache[0], posCache[1]);
    }
}

// Fixed loop for a player object, but only get called when a player moves
void PlayerControl_FixedUpdate_Hook(PlayerControl* __this, MethodInfo* method)
{
    PlayerControl_FixedUpdate_Trampoline(__this, method);
    
    if (__this->fields.LightPrefab != nullptr && sendPosition)
    {
        // Cache position
        Vector2 pos = PlayerControl_GetTruePosition_Trampoline(__this, method);
        posCache[0] = pos.x;
        posCache[1] = pos.y;
    }
}

// Gets called when a player dies
void PlayerControl_Die_Hook(PlayerControl* __this, Player_Die_Reason__Enum reason, MethodInfo* method)
{
    PlayerControl_Die_Trampoline(__this, reason, method);

    if (__this->fields.LightPrefab != nullptr)
    {
        logger.Log(LOG_CODE::MSG, "You died\n");
        mumbleLink.Mute(true);
    }
}

// Gets called when a meeting ends
void MeetingHud_Close_Hook(MeetingHud* __this, MethodInfo* method)
{
    MeetingHud_Close_Trampoline(__this, method);
    logger.Log(LOG_CODE::MSG, "Meeting ended\n");
    sendPosition = true;
}

// Gets called when a meeting starts
void MeetingHud_Start_Hook(MeetingHud* __this, MethodInfo* method)
{
    MeetingHud_Start_Trampoline(__this, method);
    logger.Log(LOG_CODE::MSG, "Meeting started\n");
    sendPosition = false;
    posCache[0] = 0.0f;
    posCache[1] = 0.0f;
}

// Fixed loop for the game client
void InnerNetClient_FixedUpdate_Hook(InnerNetClient* __this, MethodInfo* method)
{
    InnerNetClient_FixedUpdate_Trampoline(__this, method);

    // Check if game state changed to lobby
    if (__this->fields.GameState != lastGameState &&
            (__this->fields.GameState == InnerNetClient_GameState__Enum_Joined ||
            __this->fields.GameState == InnerNetClient_GameState__Enum_Ended)
       )
    {
        sendPosition = true;
        logger.Log(LOG_CODE::MSG, "Game joined or ended");
        mumbleLink.Mute(false);
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
        if (sendPosition)
        {
            mumbleLink.linkedMem->fAvatarPosition[0] = posCache[0];
            mumbleLink.linkedMem->fCameraPosition[0] = posCache[0];
            mumbleLink.linkedMem->fAvatarPosition[2] = posCache[1];
            mumbleLink.linkedMem->fCameraPosition[2] = posCache[1];
        }
        else
        {
            // When voting or in menu, all players can hear each other
            mumbleLink.linkedMem->fAvatarPosition[0] = 0.0f;
            mumbleLink.linkedMem->fCameraPosition[0] = 0.0f;
            mumbleLink.linkedMem->fAvatarPosition[2] = 0.0f;
            mumbleLink.linkedMem->fCameraPosition[2] = 0.0f;
            // Reset cached position for logging
            posCache[0] = 0.0f;
            posCache[1] = 0.0f;
		}
	}
    TryLogPosition(mumbleLink.linkedMem != nullptr);
}

void InnerNetClient_Disconnect_Hook(InnerNetClient* __this, InnerNet_DisconnectReasons__Enum reason, String* stringReason, MethodInfo* method)
{
    InnerNetClient_Disconnect_Trampoline(__this, reason, stringReason, method);
    logger.Log(LOG_CODE::MSG, "Disconnected from server");
    sendPosition = false;
    mumbleLink.Mute(false);
    posCache[0] = 0.0f;
    posCache[1] = 0.0f;
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
        logger.Log(LOG_CODE::ERR, "AmongUs-Mumble mod by:", false);
        logger.Log(LOG_CODE::ERR, "  StarGate01 (chrz.de):\tProxy DLL, Framework, Setup, Features.", false);
        logger.Log(LOG_CODE::ERR, "  Alisenai (Alien):\tFixes, More Features.", false);
        logger.Log(LOG_CODE::ERR, "  BillyDaBongo (Billy):\tManagement, Testing.", false);
        logger.Log(LOG_CODE::ERR, "  LelouBi:\t\tDeobfuscation.\n\n", false);

        logger.LogVariadic(LOG_CODE::INF, false, "Compiled for game version %s", version_text);
        logger.Log(LOG_CODE::INF, "DLL hosting successful");

        // Print current config
        logger.Log(LOG_CODE::MSG, "Current configuration:\n");
        logger.Log(LOG_CODE::MSG, appSettings.app.config_to_str(true, false) + "\n", false);

		// Setup mumble
		DWORD errMumble = mumbleLink.Init();
		if (errMumble == NO_ERROR) logger.Log(LOG_CODE::INF, "Mumble link init successful");
		else logger.LogVariadic(LOG_CODE::ERR, false, "Cannot init Mumble link: %d", errMumble);

		// Setup type and memory info
		logger.Log(LOG_CODE::MSG, "Waiting 10s for Unity to load");
		Sleep(10000);
		init_il2cpp();
		logger.Log(LOG_CODE::INF, "Type and function memory mapping successful");

		// Setup hooks
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)PlayerControl_FixedUpdate_Trampoline, PlayerControl_FixedUpdate_Hook);
		DetourAttach(&(PVOID&)PlayerControl_Die_Trampoline, PlayerControl_Die_Hook);
		DetourAttach(&(PVOID&)MeetingHud_Close_Trampoline, MeetingHud_Close_Hook);
		DetourAttach(&(PVOID&)MeetingHud_Start_Trampoline, MeetingHud_Start_Hook);
		DetourAttach(&(PVOID&)InnerNetClient_FixedUpdate_Trampoline, InnerNetClient_FixedUpdate_Hook);
		DetourAttach(&(PVOID&)InnerNetClient_Disconnect_Trampoline, InnerNetClient_Disconnect_Hook);

		//dynamic_analysis_attach();
		LONG errDetour = DetourTransactionCommit();
		if (errDetour == NO_ERROR) logger.Log(LOG_CODE::INF, "Successfully detoured game functions");
		else logger.LogVariadic(LOG_CODE::ERR, false, "Detouring game functions failed: %d", errDetour);

		// Wait for thread exit and then clean up
		WaitForSingleObject(hExit, INFINITE);
		mumbleLink.Close();
		logger.Log(LOG_CODE::MSG, "Unloading done\n");
	}
}
