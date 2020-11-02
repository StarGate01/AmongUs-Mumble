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


//void updateMumbleName(const wchar_t* name)
//{
//	wcsncpy_s(lm->identity, name, 256);
//}
//
//int updateMumbleTeam(const wchar_t* team)
//{
//	memcpy(lm->context, team, 4);
//}

using namespace app;

extern HANDLE hExit;
extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

const wchar_t* team_alive = L"ALIV";
const wchar_t* team_dead = L"DEAD";


void PlayerControl_FixedUpdate_Hook(PlayerControl* __this, MethodInfo* method)
{
    PlayerControl_FixedUpdate(__this, method);
    
    if (lm != NULL && __this->fields.LightPrefab != nullptr)
    {
        app::Vector2 pos = PlayerControl_GetTruePosition(__this, method);
        writeMumble();
        lm->fAvatarPosition[0] = pos.x;
        lm->fCameraPosition[0] = pos.x;
        lm->fAvatarPosition[2] = pos.y;
        lm->fCameraPosition[2] = pos.y;
        lm->uiTick++;
    }
}

void PlayerControl_Die_Hook(PlayerControl* __this, NPLMBOLMMLB__Enum NMGPLGPEHPP, MethodInfo* method)
{
    PlayerControl_Die(__this, NMGPLGPEHPP, method);

    if (lm != NULL && __this->fields.LightPrefab != nullptr)
    {
        printf("YOU DIED\n");
    }
}

void Run()
{
    NewConsole();
    printf("AmongUs-Mumble mod by StarGate01 (chrz.de)\n\nDLL hosting successfull\n");

    int lErrMumble = initMumble();
    if (lErrMumble == NO_ERROR) printf("Mumble link init successfull\n");
    else printf("Cannot init Mumble link: %d\n", lErrMumble);
    
    printf("Waiting 10s for Unity to load\n");
    Sleep(10000);
    init_il2cpp();
    printf("Type and function memory mapping successfull\n");
    
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)PlayerControl_FixedUpdate, PlayerControl_FixedUpdate_Hook);
    DetourAttach(&(PVOID&)PlayerControl_Die, PlayerControl_Die_Hook);
    LONG lError = DetourTransactionCommit();
    if (lError == NO_ERROR) printf("Successfully detoured game functions\n\n");
    else printf("Detouring game functions failed: %d\n", lError);

    WaitForSingleObject(hExit, INFINITE);
    printf("Exit\n");
}