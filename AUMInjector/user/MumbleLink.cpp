#include <Windows.h>
#include <shellapi.h>
#include <Shlwapi.h>
#include <thread>
#include "MumbleLink.h"
#include "Settings.h"


MumbleLink mumbleLink;

// Initializes mumble IPC and RPC
DWORD MumbleLink::Init()
{
	// Open shared memory file IPC
	mapHandle = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink");
	if (mapHandle == NULL) return GetLastError();
	linkedMem = (LinkedMem*)MapViewOfFile(mapHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(LinkedMem));
	if (linkedMem == NULL) 
	{
		DWORD err = GetLastError();
		CloseHandle(mapHandle);
		mapHandle = NULL;
		return err;
	}

	// Write inital state to IPC
	if (linkedMem->uiVersion != 2)
	{
		wcsncpy_s(linkedMem->name, L"Among Us", 256);
		wcsncpy_s(linkedMem->description, L"Among Us support via the Link plugin.", 2048);
		linkedMem->uiVersion = 2;
	}
	linkedMem->uiTick++;
	// Write identity and context
	wcsncpy_s(linkedMem->identity, L"Default", 256);
	memcpy(linkedMem->context, "TEAM", 4);
	linkedMem->context_len = 4;
	// Write position
	linkedMem->fAvatarFront[0] = 0.0f;
	linkedMem->fAvatarFront[1] = 0.0f;
	linkedMem->fAvatarFront[2] = 1.0f;
	linkedMem->fAvatarTop[0] = 0.0f;
	linkedMem->fAvatarTop[1] = 1.0f;
	linkedMem->fAvatarTop[2] = 0.0f;
	linkedMem->fAvatarPosition[0] = 0.0f;
	linkedMem->fAvatarPosition[1] = 0.0f;
	linkedMem->fAvatarPosition[2] = 0.0f;
	for (int i = 0; i < 3; i++) 
	{
		linkedMem->fCameraFront[i] = linkedMem->fAvatarFront[i];
		linkedMem->fCameraTop[i] = linkedMem->fAvatarTop[i];
		linkedMem->fCameraPosition[i] = linkedMem->fAvatarPosition[i];
	}

	return NO_ERROR;
}

// Cleans up mumble IPC and RPC
void MumbleLink::Close()
{
	// Unmap IPC and close handles
	if (linkedMem != NULL)
	{
		UnmapViewOfFile(linkedMem);
		linkedMem = NULL;
	}
	if (mapHandle != NULL)
	{
		CloseHandle(mapHandle);
		mapHandle = NULL;
	}
}

// Mutes or unmutes mumble via RPC
void MumbleLink::Mute(bool mute)
{
	std::thread t([mute] 
	{
		if (mute) system(("\"" + appSettings.mumbleExe + "\" rpc mute").c_str());
		else system(("\"" + appSettings.mumbleExe + "\" rpc unmute").c_str());
	});
	t.detach();
}
