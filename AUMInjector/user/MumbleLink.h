#pragma once

#include <windows.h>
#include <string>

struct LinkedMem
{
#ifdef _WIN32
	UINT32	uiVersion;
	DWORD	uiTick;
#else
	uint32_t uiVersion;
	uint32_t uiTick;
#endif
	float	fAvatarPosition[3];
	float	fAvatarFront[3];
	float	fAvatarTop[3];
	wchar_t	name[256];
	float	fCameraPosition[3];
	float	fCameraFront[3];
	float	fCameraTop[3];
	wchar_t	identity[256];
#ifdef _WIN32
	UINT32	context_len;
#else
	uint32_t context_len;
#endif
	unsigned char context[256];
	wchar_t description[2048];
};

class MumbleLink
{

	public:
		LinkedMem* linkedMem = nullptr;
		DWORD Init();
		void Close();
		void Mute(bool mute = true);

	private:
		HANDLE mapHandle = nullptr;
		void ExecCommand(const char* cmd);

};

extern MumbleLink mumbleLink;
