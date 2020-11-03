// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "il2cpp-init.h"
#include "il2cpp-appdata.h"
#include "helpers.h"
#include <detours.h>
#include "mumble-link.h"

#define GAME_VERSION_2020_9_22s 2020922
#define GAME_VERSION_2020_10_22s 20201022
#ifndef GAME_VERSION
    #define GAME_VERSION GAME_VERSION_2020_10_22s
#endif

using namespace app;

// Deobfuscate game bindings, depending on version
#if GAME_VERSION == GAME_VERSION_2020_9_22s
    #define version_text "2020.9.22s"
    using InnerNetClient_GameState__Enum = InnerNetClient_IFLBIJFJPMK__Enum;
    using Player_Die_Reason__Enum = NPLMBOLMMLB__Enum;
    InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Joined = InnerNetClient_IFLBIJFJPMK__Enum_Joined;
    InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Ended = InnerNetClient_IFLBIJFJPMK__Enum_Ended;
    #define PlayerControl_FixedUpdate_Trampoline PlayerControl_FixedUpdate
    #define PlayerControl_GetTruePosition_Trampoline PlayerControl_GetTruePosition
    #define PlayerControl_Die_Trampoline PlayerControl_Die
    #define MeetingHud_Close_Trampoline MeetingHud_Close
    #define MeetingHud_Start_Trampoline MeetingHud_Start
    #define InnerNetClient_FixedUpdate_Trampoline InnerNetClient_FixedUpdate
#elif GAME_VERSION == GAME_VERSION_2020_10_22s
    #define version_text "2020.10.22s"
    using InnerNetClient_GameState__Enum = DNAFMCDBMCI_JPCEFDHGHAK__Enum;
    using PlayerControl = GLHCHLEDNBA;
    using Player_Die_Reason__Enum = CCCHKEBONBN__Enum;
    using MeetingHud = GPOHFPAIEMA;
    using InnerNetClient = DNAFMCDBMCI;
    InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Joined = DNAFMCDBMCI_JPCEFDHGHAK__Enum_Joined;
    InnerNetClient_GameState__Enum InnerNetClient_GameState__Enum_Ended = DNAFMCDBMCI_JPCEFDHGHAK__Enum_Ended;
    #define PlayerControl_FixedUpdate_Trampoline GLHCHLEDNBA_FixedUpdate
    #define PlayerControl_GetTruePosition_Trampoline GLHCHLEDNBA_GetTruePosition
    #define PlayerControl_Die_Trampoline GLHCHLEDNBA_Die
    #define MeetingHud_Close_Trampoline GPOHFPAIEMA_Close
    #define MeetingHud_Start_Trampoline GPOHFPAIEMA_Start
    #define InnerNetClient_FixedUpdate_Trampoline DNAFMCDBMCI_FixedUpdate
#else
    #error Unknown game version!
#endif

#pragma message("Compiling for game version " version_text)


extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";
extern HANDLE hExit; // Thread exit event
extern std::string mumble_exe;

// Game state
float cache_x = 0.0f; float cache_y = 0.0f;
bool voting = false;
InnerNetClient_GameState__Enum last_game_state = InnerNetClient_GameState__Enum_Joined;


// Fixed loop for a player object, but only get called when a player moves
void PlayerControl_FixedUpdate_Hook(PlayerControl* __this, MethodInfo* method)
{
    PlayerControl_FixedUpdate_Trampoline(__this, method);
    
    if (lm != NULL && __this->fields.LightPrefab != nullptr && !voting)
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
        printf("You died\n");
        muteMumble(true);
    }
}

// Gets called when a meeting ends
void MeetingHud_Close_Hook(MeetingHud* __this, MethodInfo* method)
{
    MeetingHud_Close_Trampoline(__this, method);
    printf("Meeting ended\n");
    voting = false;
}

// Gets called when a meeting starts
void MeetingHud_Start_Hook(MeetingHud* __this, MethodInfo* method)
{
    MeetingHud_Start_Trampoline(__this, method);
    printf("Meeting started\n");
    voting = true;
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
        printf("Game joined or ended\n");
        muteMumble(false);
    }
    last_game_state = __this->fields.GameState;

    if (lm->uiVersion != 2)
    {
        wcsncpy_s(lm->name, L"Among Us", 256);
        wcsncpy_s(lm->description, L"Among Us support via the Link plugin.", 2048);
        lm->uiVersion = 2;
    }
    lm->uiTick++;
    if (voting)
    {
        // When voting, all players can hear each other -> same position
        lm->fAvatarPosition[0] = 0.0f;
        lm->fCameraPosition[0] = 0.0f;
        lm->fAvatarPosition[2] = 0.0f;
        lm->fCameraPosition[2] = 0.0f;
    }
    else
    {
        lm->fAvatarPosition[0] = cache_x;
        lm->fCameraPosition[0] = cache_x;
        lm->fAvatarPosition[2] = cache_y;
        lm->fCameraPosition[2] = cache_y;
    }
}

// Entrypoint of the injected thread
void Run()
{
    NewConsole();
    printf("AmongUs-Mumble mod by StarGate01 (chrz.de)\nCompiled for game version %s\nDLL hosting successful\n\n", version_text);

    // Setup mumble
    int lErrMumble = initMumble();
    if (lErrMumble == NO_ERROR)
    {
        printf("Mumble link init successful\n");
        printf("Mumble exe: %s\n", mumble_exe.c_str());
    }
    else printf("Cannot init Mumble link: %d\n", lErrMumble);
    
    // Setup type and memory info
    printf("Waiting 10s for Unity to load\n");
    Sleep(10000);
    init_il2cpp();
    printf("Type and function memory mapping successful\n");
    
    // Setup hooks
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)PlayerControl_FixedUpdate_Trampoline, PlayerControl_FixedUpdate_Hook);
    DetourAttach(&(PVOID&)PlayerControl_Die_Trampoline, PlayerControl_Die_Hook);
    DetourAttach(&(PVOID&)MeetingHud_Close_Trampoline, MeetingHud_Close_Hook);
    DetourAttach(&(PVOID&)MeetingHud_Start_Trampoline, MeetingHud_Start_Hook);
    DetourAttach(&(PVOID&)InnerNetClient_FixedUpdate_Trampoline, InnerNetClient_FixedUpdate_Hook);
    LONG lError = DetourTransactionCommit();
    if (lError == NO_ERROR) printf("Successfully detoured game functions\n\n");
    else printf("Detouring game functions failed: %d\n", lError);

    // Wait for thread exit and then clean up
    WaitForSingleObject(hExit, INFINITE);
    closeMumble();
    printf("Unloading done\n");
}