#include <Windows.h>
#include <shellapi.h>
#include <Shlwapi.h>
#include <comdef.h>
#include "CLI11.hpp"
#include "mumble-link.h"


LinkedMem* lm = NULL;
HANDLE hMapObject = NULL;
std::string mumble_exe = "C:\\Program Files (x86)\\Mumble\\mumble.exe";


// Initializes mumble IPC and RPC
int initMumble()
{
	// Setup argument parser
	CLI::App app{ "AmongUs-Mumble", "Among Us.exe" };
	app.allow_extras();
	app.add_option("-m,--mumble", mumble_exe, "Mumble executable path");
	// Get arguments from OS
	int argc;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	// Convert arguments from unicode to narrow
	_bstr_t** argv_bstr = (_bstr_t**)malloc(argc * sizeof(_bstr_t*));
	char** argv_narrow = (char**)malloc(argc * sizeof(char*));
	for (int i = 0; i < argc; i++)
	{
		argv_bstr[i] = new _bstr_t(argv[i]);
		argv_narrow[i] = *argv_bstr[i];
	}
	// Parse arguments
	app.parse(argc, argv_narrow);
	printf("%s", app.help().c_str());
	// Free temp buffers
	LocalFree(argv);
	for (int i = 0; i < argc; i++)
	{
		argv_bstr[i]->~_bstr_t();
		free(argv_bstr[i]);
	}
	free(argv_bstr);
	free(argv_narrow);

	// Open shared memory file IPC
	hMapObject = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink");
	if (hMapObject == NULL) return GetLastError();
	lm = (LinkedMem*)MapViewOfFile(hMapObject, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(LinkedMem));
	if (lm == NULL) 
	{
		int err = GetLastError();
		CloseHandle(hMapObject);
		hMapObject = NULL;
		return err;
	}

	// Write inital state to IPC
	if (lm->uiVersion != 2)
	{
		wcsncpy_s(lm->name, L"Among Us", 256);
		wcsncpy_s(lm->description, L"Among Us support via the Link plugin.", 2048);
		lm->uiVersion = 2;
	}
	lm->uiTick++;
	// Write identity and context
	wcsncpy_s(lm->identity, L"Default", 256);
	memcpy(lm->context, L"TEAM", 4);
	lm->context_len = 4;
	// Write position
	lm->fAvatarFront[0] = 0.0f;
	lm->fAvatarFront[1] = 0.0f;
	lm->fAvatarFront[2] = 1.0f;
	lm->fAvatarTop[0] = 0.0f;
	lm->fAvatarTop[1] = 1.0f;
	lm->fAvatarTop[2] = 0.0f;
	lm->fAvatarPosition[0] = 0.0f;
	lm->fAvatarPosition[1] = 0.0f;
	lm->fAvatarPosition[2] = 0.0f;
	for (int i = 0; i < 3; i++) {
		lm->fCameraFront[i] = lm->fAvatarFront[i];
		lm->fCameraTop[i] = lm->fAvatarTop[i];
		lm->fCameraPosition[i] = lm->fAvatarPosition[i];
	}

	return NO_ERROR;
}

// Cleans up mumble IPC and RPC
void closeMumble()
{
	// Unmap IPC and close handles
	if (lm != NULL)
	{
		UnmapViewOfFile(lm);
		lm = NULL;
	}
	if (hMapObject != NULL)
	{
		CloseHandle(hMapObject);
		hMapObject = NULL;
	}
}

// Mutes or unmutes mumble via RPC
void muteMumble(bool mute)
{
	if(mute) system(("\"" + mumble_exe + "\" rpc mute").c_str());
	else system(("\"" + mumble_exe + "\" rpc unmute").c_str());
}
