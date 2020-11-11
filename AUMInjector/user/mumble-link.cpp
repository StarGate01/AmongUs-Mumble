#include <Windows.h>
#include <shellapi.h>
#include <Shlwapi.h>
#include "mumble-link.h"
#include "settings.h"


LinkedMem* lm = NULL;
HANDLE hMapObject = NULL;

// Initializes mumble IPC and RPC
int initMumble()
{
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
	memcpy(lm->context, "TEAM", 4);
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
	if(mute) system(("\"" + app_settings.mumble_exe + "\" rpc mute").c_str());
	else system(("\"" + app_settings.mumble_exe + "\" rpc unmute").c_str());
}
