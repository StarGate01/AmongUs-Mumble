#include "mumble-link.h"

LinkedMem* lm = NULL;

int initMumble()
{
	HANDLE hMapObject = OpenFileMappingW(FILE_MAP_ALL_ACCESS, FALSE, L"MumbleLink");
	if (hMapObject == NULL) return GetLastError();

	lm = (LinkedMem*)MapViewOfFile(hMapObject, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(LinkedMem));
	if (lm == NULL) 
	{
		int err = GetLastError();
		CloseHandle(hMapObject);
		hMapObject = NULL;
		return err;
	}

	wcsncpy_s(lm->name, L"Among Us", 256);
	wcsncpy_s(lm->description, L"Among Us support via the Link plugin.", 2048);
	lm->uiVersion = 2;

	wcsncpy_s(lm->identity, L"Default", 256);
	memcpy(lm->context, L"ALIV", 4);

	lm->fAvatarFront[0] = 0.0f;
	lm->fAvatarFront[1] = 0.0f;
	lm->fAvatarFront[2] = 1.0f;
	lm->fAvatarTop[0] = 0.0f;
	lm->fAvatarTop[1] = 1.0f;
	lm->fAvatarTop[2] = 0.0f;
	lm->fAvatarPosition[0] = 0.0f;
	lm->fAvatarPosition[2] = 0.0f;
	lm->fAvatarPosition[1] = 0.0f;

	for (int i = 0; i < 3; i++) {
		lm->fCameraFront[i] = lm->fAvatarFront[i];
		lm->fCameraTop[i] = lm->fAvatarTop[i];
		lm->fCameraPosition[i] = lm->fAvatarPosition[i];
	}

	lm->context_len = 4;

	return NO_ERROR;
}
