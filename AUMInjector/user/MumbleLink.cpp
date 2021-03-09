#include "MumbleLink.h"
#include "Settings.h"
#include "OrderedLock.h"

MumbleLink mumbleLink;
OrderedLock mumbleRPCLock;


MumbleLink::MumbleLink()
{
	HMODULE hntdll = GetModuleHandle("ntdll.dll");
	isWine = (hntdll && GetProcAddress(hntdll, "wine_get_version"));
}

// Initializes mumble IPC and RPC
DWORD MumbleLink::Init()
{
	// Open shared memory file IPC
	if (!IsWine())
	{
		mapHandle = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink");
	}
	else
	{
		std::stringstream ss;
		ss << "/dev/shm/MumbleLink." << appSettings.wineUID;
		std::string shmPath = ss.str();
		HANDLE fhandle = CreateFile(shmPath.c_str(), GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (fhandle != INVALID_HANDLE_VALUE)
			mapHandle = CreateFileMapping(fhandle, NULL, PAGE_READWRITE, 0, 0, NULL);
		else return ERROR_FILE_NOT_FOUND;
	}

	if (mapHandle == NULL) return GetLastError();
	linkedMem = MapViewOfFile(mapHandle, FILE_MAP_ALL_ACCESS, 0, 0, isWine? sizeof(LinkedMemWine): sizeof(LinkedMemWindows));
	if (linkedMem == NULL) 
	{
		DWORD err = GetLastError();
		CloseHandle(mapHandle);
		mapHandle = NULL;
		return err;
	}

	// Write inital state to IPC, write identity and context
	// and init shared memeory
	// This macro trickery is needed to select the correct memory layout for NT or Linux
	#define INITBLOCK(T, F, CW) {\
	if (((T)linkedMem)->uiVersion != 2) \
	{ \
		memcpy(((T)linkedMem)->name, F##"Among Us\0", 9 * CW); \
		memcpy(((T)linkedMem)->description, F##"Among Us support via the Link plugin.\0", 38 * CW); \
		((T)linkedMem)->uiVersion = 2; \
	} \
	((T)linkedMem)->uiTick++; \
	memcpy(((T)linkedMem)->identity, F##"Default\0", 8 * CW); \
	memcpy(((T)linkedMem)->context, "TEAM", 4); \
	((T)linkedMem)->context_len = 4; \
	((T)linkedMem)->fAvatarFront[0] = 0.0f; \
	((T)linkedMem)->fAvatarFront[1] = 0.0f; \
	((T)linkedMem)->fAvatarFront[2] = 1.0f; \
	((T)linkedMem)->fAvatarTop[0] = 0.0f; \
	((T)linkedMem)->fAvatarTop[1] = 1.0f; \
	((T)linkedMem)->fAvatarTop[2] = 0.0f; \
	((T)linkedMem)->fAvatarPosition[0] = 0.0f; \
	((T)linkedMem)->fAvatarPosition[1] = 0.0f; \
	(((T)linkedMem))->fAvatarPosition[2] = 0.0f; \
	for (int i = 0; i < 3; i++) \
	{ \
		((T)linkedMem)->fCameraFront[i] = ((T)linkedMem)->fAvatarFront[i]; \
		((T)linkedMem)->fCameraTop[i] = ((T)linkedMem)->fAvatarTop[i]; \
		((T)linkedMem)->fCameraPosition[i] = ((T)linkedMem)->fAvatarPosition[i]; \
	} }
	if (isWine) INITBLOCK(LinkedMemWine*, U, 4)
	else INITBLOCK(LinkedMemWindows*, L, 2)
	#undef INITBLOCK

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
	bool iswine = IsWine();
	// Defer to new thread because system() is slow
	std::thread t([mute, iswine]
	{
		// Aquire mutex to ensure sequential order of operation
		// Autodestructor on scope exit will release it
		OrderedLockRAII lock(mumbleRPCLock);
		std::string prefix = "";
		if (!iswine)
		{
			if (mute) system(("\"" + appSettings.mumbleExe + "\" rpc mute").c_str());
			else system(("\"" + appSettings.mumbleExe + "\" rpc unmute").c_str());
		}
		else
		{
			if (mute) system(("start /unix " + appSettings.mumbleExe + " rpc mute").c_str());
			else system(("start /unix " + appSettings.mumbleExe + " rpc unmute").c_str());
		}
	});
	t.detach();
}