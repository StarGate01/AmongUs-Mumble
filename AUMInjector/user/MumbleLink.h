#pragma once

struct LinkedMemWindows
{
	UINT32	uiVersion;
	DWORD	uiTick;
	float	fAvatarPosition[3];
	float	fAvatarFront[3];
	float	fAvatarTop[3];
	wchar_t name[256];
	float	fCameraPosition[3];
	float	fCameraFront[3];
	float	fCameraTop[3];
	wchar_t identity[256];
	UINT32	context_len;
	unsigned char context[256];
	wchar_t description[2048];
};

struct LinkedMemWine
{
	UINT32	uiVersion;
	DWORD	uiTick;
	float	fAvatarPosition[3];
	float	fAvatarFront[3];
	float	fAvatarTop[3];
	char32_t name[256];
	float	fCameraPosition[3];
	float	fCameraFront[3];
	float	fCameraTop[3];
	char32_t identity[256];
	UINT32	context_len;
	unsigned char context[256];
	char32_t description[2048];
};


class MumbleLink
{

	public:
		void* linkedMem = nullptr;

		MumbleLink();
		DWORD Init();
		void Close();
		void Mute(bool mute = true);
		bool IsWine() { return isWine; }

	private:
		bool isWine;
		HANDLE mapHandle = nullptr;
		void ExecCommand(const char* cmd);

};

extern MumbleLink mumbleLink;
