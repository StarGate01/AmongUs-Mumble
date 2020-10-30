// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "il2cpp-appdata.h"
#include "helpers.h"

#include <detours.h>

using namespace app;

extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

void PlayerControl_FixedUpdate_Hook(PlayerControl* __this, MethodInfo* method)
{
    PlayerControl_FixedUpdate(__this, method);

    app::Vector2 pos = PlayerControl_GetTruePosition(__this, method);
    printf("%.6f, %.6f\n", pos.x, pos.y);
}

void Run()
{
    NewConsole();
    printf("DLL hosting successfull\n");

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetourAttach(&(PVOID&)PlayerControl_FixedUpdate, PlayerControl_FixedUpdate_Hook);
    LONG lError = DetourTransactionCommit();
    if (lError == NO_ERROR) printf("Successfully detoured PlayerControl_FixedUpdate\n");
    else printf("Detouring failed\n");

    while (true);
}