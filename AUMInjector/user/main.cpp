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
#include "mumble-link.h"
#include "deobfuscate.h"
#include "settings.h"
#include "LoggingSystem.h"
//#include "dynamic_analysis.h"

using namespace app;

extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";
extern HANDLE hExit; // Thread exit event

// Game state
float cache_x = 0.0f; float cache_y = 0.0f;
bool send_position = true;
InnerNetClient_GameState__Enum last_game_state = InnerNetClient_GameState__Enum_Joined;

// Ints for tracking when to print the position
int frameCounter = 0;
const int timeToPrintPosition = 15;
// Start old cache as an impossible limit, for first-frame printing
float cacheXOld = std::numeric_limits<float>::lowest();
float cacheYOld = std::numeric_limits<float>::lowest();
// Floating-point epsilon for position printing
float cachePosEpsilon = 0.001f;

// Will log the position, if needed
void TryLogPosition() 
{
    // Only print the player position every so many frames, and if it has changed
    if (++frameCounter > timeToPrintPosition && (
        std::abs(cacheXOld - cache_x) > cachePosEpsilon ||
        std::abs(cacheYOld - cache_y) > cachePosEpsilon
        ))
    {
        frameCounter = 0;
        // Store the old position
        cacheXOld = cache_x;
        cacheYOld = cache_y;
        // Log the current player position to let the player know it is working
        logger.LogVariadic(LOG_CODE::INF, "Position: (% 7.3f, % 7.3f)", cache_x, cache_y);
    }
}

// Fixed loop for a player object, but only get called when a player moves
void PlayerControl_FixedUpdate_Hook(PlayerControl* __this, MethodInfo* method)
{
    PlayerControl_FixedUpdate_Trampoline(__this, method);
    
    if (__this->fields.LightPrefab != nullptr && send_position)
    {
        // Cache position
        Vector2 pos = PlayerControl_GetTruePosition_Trampoline(__this, method);
        cache_x = pos.x;
        cache_y = pos.y;
    }
}

// Gets called when a player dies
void PlayerControl_Die_Hook(PlayerControl* __this, Player_Die_Reason__Enum reason, MethodInfo* method)
{
    PlayerControl_Die_Trampoline(__this, reason, method);

    if (__this->fields.LightPrefab != nullptr)
    {
        logger.Log(LOG_CODE::MSG, "You died\n");
        muteMumble(true);
    }
}

// Gets called when a meeting ends
void MeetingHud_Close_Hook(MeetingHud* __this, MethodInfo* method)
{
    MeetingHud_Close_Trampoline(__this, method);
    logger.Log(LOG_CODE::MSG, "Meeting ended\n");
    send_position = true;
}

// Gets called when a meeting starts
void MeetingHud_Start_Hook(MeetingHud* __this, MethodInfo* method)
{
    MeetingHud_Start_Trampoline(__this, method);
    logger.Log(LOG_CODE::MSG, "Meeting started\n");
    send_position = false;
}

// Fixed loop for the game client
void InnerNetClient_FixedUpdate_Hook(InnerNetClient* __this, MethodInfo* method)
{
    InnerNetClient_FixedUpdate_Trampoline(__this, method);

    // Check if game state changed to lobby
    if (__this->fields.GameState != last_game_state &&
            (__this->fields.GameState == InnerNetClient_GameState__Enum_Joined ||
            __this->fields.GameState == InnerNetClient_GameState__Enum_Ended))
    {
        send_position = true;
        logger.Log(LOG_CODE::MSG, "Game joined or ended");
        muteMumble(false);
    }
    last_game_state = __this->fields.GameState;

    if (lm != NULL)
    {
        if (lm->uiVersion != 2)
        {
            wcsncpy_s(lm->name, L"Among Us", 256);
            wcsncpy_s(lm->description, L"Among Us support via the Link plugin.", 2048);
            lm->uiVersion = 2;
        }
        lm->uiTick++;
        if (send_position)
        {
            lm->fAvatarPosition[0] = cache_x;
            lm->fCameraPosition[0] = cache_x;
            lm->fAvatarPosition[2] = cache_y;
            lm->fCameraPosition[2] = cache_y;
        }
        else
        {
            // When voting or in menu, all players can hear each other
            lm->fAvatarPosition[0] = 0.0f;
            lm->fCameraPosition[0] = 0.0f;
            lm->fAvatarPosition[2] = 0.0f;
            lm->fCameraPosition[2] = 0.0f;
            // Reset cached position
            cache_x = 0.0f;
            cache_y = 0.0f;
		}
        TryLogPosition();
	}
}

void InnerNetClient_Disconnect_Hook(InnerNetClient* __this, InnerNet_DisconnectReasons__Enum reason, String* stringReason, MethodInfo* method)
{
    InnerNetClient_Disconnect_Trampoline(__this, reason, stringReason, method);
    logger.Log(LOG_CODE::MSG, "Disconnected from server");
    send_position = false;
    muteMumble(false);
}

// Entrypoint of the injected thread
void Run()
{
    // Check what process the dll was loaded into
    // If loaded into the wrong process, exit injected thread
    TCHAR hostExe[MAX_PATH];
    GetModuleFileName(NULL, hostExe, MAX_PATH);
    char fname[_MAX_FNAME];
    _splitpath_s(hostExe, NULL, 0, NULL, 0, fname, _MAX_FNAME, NULL, 0);
    if (strcmp(fname, "Among Us") == 0)
    {
        // Load settings
        app_settings.parse();
        app_settings.print_usage();
        logger.Log(LOG_CODE::MSG, "Current configuration:\n----\n");
        app_settings.print_config();
        printf("----\n\n");

        // Enable the logger
        if (!app_settings.noConsole) logger.EnableConsoleLogging();
        logger.EnableFileLogging(); // File logging enabled by defa

        // Credits & Info
		logger.Log(LOG_CODE::MSG, "AmongUs-Mumble mod by:");
		logger.Log(LOG_CODE::MSG, "\tStarGate01 (chrz.de): Proxy DLL, Framework, Setup, Features.");
		logger.Log(LOG_CODE::MSG, "\tAlisenai (Alien): Fixes, More Features.");
		logger.Log(LOG_CODE::MSG, "\tBillyDaBongo (Billy): Management, Testing.");
		logger.Log(LOG_CODE::MSG, "\tLelouBi:\t\tDeobfuscation.\n\n");

    	logger.LogVariadic(LOG_CODE::MSG, "Compiled for game version %s", version_text);
    	logger.Log(LOG_CODE::INF, "DLL hosting successful");

		// Setup mumble
		int lErrMumble = initMumble();
		if (lErrMumble == NO_ERROR) logger.Log(LOG_CODE::INF, "Mumble link init successful");
		else logger.LogVariadic(LOG_CODE::ERR, "Cannot init Mumble link: ", lErrMumble);

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
		LONG lError = DetourTransactionCommit();
		if (lError == NO_ERROR) logger.Log(LOG_CODE::INF, "Successfully detoured game functions");
		else logger.LogVariadic(LOG_CODE::ERR, "Detouring game functions failed: ", lError);

		// Wait for thread exit and then clean up
		WaitForSingleObject(hExit, INFINITE);
		closeMumble();
		logger.Log(LOG_CODE::MSG, "Unloading done\n");
	}
}
