#include <windows.h>

struct winhttp_dll { 
	HMODULE dll;
	FARPROC OrignalDllCanUnloadNow;
	FARPROC OrignalDllGetClassObject;
	FARPROC OrignalPrivate1;
	FARPROC OrignalSvchostPushServiceGlobals;
	FARPROC OrignalWinHttpAddRequestHeaders;
	FARPROC OrignalWinHttpAddRequestHeadersEx;
	FARPROC OrignalWinHttpAutoProxySvcMain;
	FARPROC OrignalWinHttpCheckPlatform;
	FARPROC OrignalWinHttpCloseHandle;
	FARPROC OrignalWinHttpConnect;
	FARPROC OrignalWinHttpConnectionDeletePolicyEntries;
	FARPROC OrignalWinHttpConnectionDeleteProxyInfo;
	FARPROC OrignalWinHttpConnectionFreeNameList;
	FARPROC OrignalWinHttpConnectionFreeProxyInfo;
	FARPROC OrignalWinHttpConnectionFreeProxyList;
	FARPROC OrignalWinHttpConnectionGetNameList;
	FARPROC OrignalWinHttpConnectionGetProxyInfo;
	FARPROC OrignalWinHttpConnectionGetProxyList;
	FARPROC OrignalWinHttpConnectionSetPolicyEntries;
	FARPROC OrignalWinHttpConnectionSetProxyInfo;
	FARPROC OrignalWinHttpConnectionUpdateIfIndexTable;
	FARPROC OrignalWinHttpCrackUrl;
	FARPROC OrignalWinHttpCreateProxyResolver;
	FARPROC OrignalWinHttpCreateUrl;
	FARPROC OrignalWinHttpDetectAutoProxyConfigUrl;
	FARPROC OrignalWinHttpFreeProxyResult;
	FARPROC OrignalWinHttpFreeProxyResultEx;
	FARPROC OrignalWinHttpFreeProxySettings;
	FARPROC OrignalWinHttpGetDefaultProxyConfiguration;
	FARPROC OrignalWinHttpGetIEProxyConfigForCurrentUser;
	FARPROC OrignalWinHttpGetProxyForUrl;
	FARPROC OrignalWinHttpGetProxyForUrlEx;
	FARPROC OrignalWinHttpGetProxyForUrlEx2;
	FARPROC OrignalWinHttpGetProxyForUrlHvsi;
	FARPROC OrignalWinHttpGetProxyResult;
	FARPROC OrignalWinHttpGetProxyResultEx;
	FARPROC OrignalWinHttpGetProxySettingsVersion;
	FARPROC OrignalWinHttpGetTunnelSocket;
	FARPROC OrignalWinHttpOpen;
	FARPROC OrignalWinHttpOpenRequest;
	FARPROC OrignalWinHttpPacJsWorkerMain;
	FARPROC OrignalWinHttpProbeConnectivity;
	FARPROC OrignalWinHttpQueryAuthSchemes;
	FARPROC OrignalWinHttpQueryDataAvailable;
	FARPROC OrignalWinHttpQueryHeaders;
	FARPROC OrignalWinHttpQueryOption;
	FARPROC OrignalWinHttpReadData;
	FARPROC OrignalWinHttpReadProxySettings;
	FARPROC OrignalWinHttpReadProxySettingsHvsi;
	FARPROC OrignalWinHttpReceiveResponse;
	FARPROC OrignalWinHttpResetAutoProxy;
	FARPROC OrignalWinHttpSaveProxyCredentials;
	FARPROC OrignalWinHttpSendRequest;
	FARPROC OrignalWinHttpSetCredentials;
	FARPROC OrignalWinHttpSetDefaultProxyConfiguration;
	FARPROC OrignalWinHttpSetOption;
	FARPROC OrignalWinHttpSetProxySettingsPerUser;
	FARPROC OrignalWinHttpSetStatusCallback;
	FARPROC OrignalWinHttpSetTimeouts;
	FARPROC OrignalWinHttpTimeFromSystemTime;
	FARPROC OrignalWinHttpTimeToSystemTime;
	FARPROC OrignalWinHttpWebSocketClose;
	FARPROC OrignalWinHttpWebSocketCompleteUpgrade;
	FARPROC OrignalWinHttpWebSocketQueryCloseStatus;
	FARPROC OrignalWinHttpWebSocketReceive;
	FARPROC OrignalWinHttpWebSocketSend;
	FARPROC OrignalWinHttpWebSocketShutdown;
	FARPROC OrignalWinHttpWriteData;
	FARPROC OrignalWinHttpWriteProxySettings;
} winhttp;

__declspec(naked) void FakeDllCanUnloadNow() { _asm { jmp[winhttp.OrignalDllCanUnloadNow] } }
__declspec(naked) void FakeDllGetClassObject() { _asm { jmp[winhttp.OrignalDllGetClassObject] } }
__declspec(naked) void FakePrivate1() { _asm { jmp[winhttp.OrignalPrivate1] } }
__declspec(naked) void FakeSvchostPushServiceGlobals() { _asm { jmp[winhttp.OrignalSvchostPushServiceGlobals] } }
__declspec(naked) void FakeWinHttpAddRequestHeaders() { _asm { jmp[winhttp.OrignalWinHttpAddRequestHeaders] } }
__declspec(naked) void FakeWinHttpAddRequestHeadersEx() { _asm { jmp[winhttp.OrignalWinHttpAddRequestHeadersEx] } }
__declspec(naked) void FakeWinHttpAutoProxySvcMain() { _asm { jmp[winhttp.OrignalWinHttpAutoProxySvcMain] } }
__declspec(naked) void FakeWinHttpCheckPlatform() { _asm { jmp[winhttp.OrignalWinHttpCheckPlatform] } }
__declspec(naked) void FakeWinHttpCloseHandle() { _asm { jmp[winhttp.OrignalWinHttpCloseHandle] } }
__declspec(naked) void FakeWinHttpConnect() { _asm { jmp[winhttp.OrignalWinHttpConnect] } }
__declspec(naked) void FakeWinHttpConnectionDeletePolicyEntries() { _asm { jmp[winhttp.OrignalWinHttpConnectionDeletePolicyEntries] } }
__declspec(naked) void FakeWinHttpConnectionDeleteProxyInfo() { _asm { jmp[winhttp.OrignalWinHttpConnectionDeleteProxyInfo] } }
__declspec(naked) void FakeWinHttpConnectionFreeNameList() { _asm { jmp[winhttp.OrignalWinHttpConnectionFreeNameList] } }
__declspec(naked) void FakeWinHttpConnectionFreeProxyInfo() { _asm { jmp[winhttp.OrignalWinHttpConnectionFreeProxyInfo] } }
__declspec(naked) void FakeWinHttpConnectionFreeProxyList() { _asm { jmp[winhttp.OrignalWinHttpConnectionFreeProxyList] } }
__declspec(naked) void FakeWinHttpConnectionGetNameList() { _asm { jmp[winhttp.OrignalWinHttpConnectionGetNameList] } }
__declspec(naked) void FakeWinHttpConnectionGetProxyInfo() { _asm { jmp[winhttp.OrignalWinHttpConnectionGetProxyInfo] } }
__declspec(naked) void FakeWinHttpConnectionGetProxyList() { _asm { jmp[winhttp.OrignalWinHttpConnectionGetProxyList] } }
__declspec(naked) void FakeWinHttpConnectionSetPolicyEntries() { _asm { jmp[winhttp.OrignalWinHttpConnectionSetPolicyEntries] } }
__declspec(naked) void FakeWinHttpConnectionSetProxyInfo() { _asm { jmp[winhttp.OrignalWinHttpConnectionSetProxyInfo] } }
__declspec(naked) void FakeWinHttpConnectionUpdateIfIndexTable() { _asm { jmp[winhttp.OrignalWinHttpConnectionUpdateIfIndexTable] } }
__declspec(naked) void FakeWinHttpCrackUrl() { _asm { jmp[winhttp.OrignalWinHttpCrackUrl] } }
__declspec(naked) void FakeWinHttpCreateProxyResolver() { _asm { jmp[winhttp.OrignalWinHttpCreateProxyResolver] } }
__declspec(naked) void FakeWinHttpCreateUrl() { _asm { jmp[winhttp.OrignalWinHttpCreateUrl] } }
__declspec(naked) void FakeWinHttpDetectAutoProxyConfigUrl() { _asm { jmp[winhttp.OrignalWinHttpDetectAutoProxyConfigUrl] } }
__declspec(naked) void FakeWinHttpFreeProxyResult() { _asm { jmp[winhttp.OrignalWinHttpFreeProxyResult] } }
__declspec(naked) void FakeWinHttpFreeProxyResultEx() { _asm { jmp[winhttp.OrignalWinHttpFreeProxyResultEx] } }
__declspec(naked) void FakeWinHttpFreeProxySettings() { _asm { jmp[winhttp.OrignalWinHttpFreeProxySettings] } }
__declspec(naked) void FakeWinHttpGetDefaultProxyConfiguration() { _asm { jmp[winhttp.OrignalWinHttpGetDefaultProxyConfiguration] } }
__declspec(naked) void FakeWinHttpGetIEProxyConfigForCurrentUser() { _asm { jmp[winhttp.OrignalWinHttpGetIEProxyConfigForCurrentUser] } }
__declspec(naked) void FakeWinHttpGetProxyForUrl() { _asm { jmp[winhttp.OrignalWinHttpGetProxyForUrl] } }
__declspec(naked) void FakeWinHttpGetProxyForUrlEx() { _asm { jmp[winhttp.OrignalWinHttpGetProxyForUrlEx] } }
__declspec(naked) void FakeWinHttpGetProxyForUrlEx2() { _asm { jmp[winhttp.OrignalWinHttpGetProxyForUrlEx2] } }
__declspec(naked) void FakeWinHttpGetProxyForUrlHvsi() { _asm { jmp[winhttp.OrignalWinHttpGetProxyForUrlHvsi] } }
__declspec(naked) void FakeWinHttpGetProxyResult() { _asm { jmp[winhttp.OrignalWinHttpGetProxyResult] } }
__declspec(naked) void FakeWinHttpGetProxyResultEx() { _asm { jmp[winhttp.OrignalWinHttpGetProxyResultEx] } }
__declspec(naked) void FakeWinHttpGetProxySettingsVersion() { _asm { jmp[winhttp.OrignalWinHttpGetProxySettingsVersion] } }
__declspec(naked) void FakeWinHttpGetTunnelSocket() { _asm { jmp[winhttp.OrignalWinHttpGetTunnelSocket] } }
__declspec(naked) void FakeWinHttpOpen() { _asm { jmp[winhttp.OrignalWinHttpOpen] } }
__declspec(naked) void FakeWinHttpOpenRequest() { _asm { jmp[winhttp.OrignalWinHttpOpenRequest] } }
__declspec(naked) void FakeWinHttpPacJsWorkerMain() { _asm { jmp[winhttp.OrignalWinHttpPacJsWorkerMain] } }
__declspec(naked) void FakeWinHttpProbeConnectivity() { _asm { jmp[winhttp.OrignalWinHttpProbeConnectivity] } }
__declspec(naked) void FakeWinHttpQueryAuthSchemes() { _asm { jmp[winhttp.OrignalWinHttpQueryAuthSchemes] } }
__declspec(naked) void FakeWinHttpQueryDataAvailable() { _asm { jmp[winhttp.OrignalWinHttpQueryDataAvailable] } }
__declspec(naked) void FakeWinHttpQueryHeaders() { _asm { jmp[winhttp.OrignalWinHttpQueryHeaders] } }
__declspec(naked) void FakeWinHttpQueryOption() { _asm { jmp[winhttp.OrignalWinHttpQueryOption] } }
__declspec(naked) void FakeWinHttpReadData() { _asm { jmp[winhttp.OrignalWinHttpReadData] } }
__declspec(naked) void FakeWinHttpReadProxySettings() { _asm { jmp[winhttp.OrignalWinHttpReadProxySettings] } }
__declspec(naked) void FakeWinHttpReadProxySettingsHvsi() { _asm { jmp[winhttp.OrignalWinHttpReadProxySettingsHvsi] } }
__declspec(naked) void FakeWinHttpReceiveResponse() { _asm { jmp[winhttp.OrignalWinHttpReceiveResponse] } }
__declspec(naked) void FakeWinHttpResetAutoProxy() { _asm { jmp[winhttp.OrignalWinHttpResetAutoProxy] } }
__declspec(naked) void FakeWinHttpSaveProxyCredentials() { _asm { jmp[winhttp.OrignalWinHttpSaveProxyCredentials] } }
__declspec(naked) void FakeWinHttpSendRequest() { _asm { jmp[winhttp.OrignalWinHttpSendRequest] } }
__declspec(naked) void FakeWinHttpSetCredentials() { _asm { jmp[winhttp.OrignalWinHttpSetCredentials] } }
__declspec(naked) void FakeWinHttpSetDefaultProxyConfiguration() { _asm { jmp[winhttp.OrignalWinHttpSetDefaultProxyConfiguration] } }
__declspec(naked) void FakeWinHttpSetOption() { _asm { jmp[winhttp.OrignalWinHttpSetOption] } }
__declspec(naked) void FakeWinHttpSetProxySettingsPerUser() { _asm { jmp[winhttp.OrignalWinHttpSetProxySettingsPerUser] } }
__declspec(naked) void FakeWinHttpSetStatusCallback() { _asm { jmp[winhttp.OrignalWinHttpSetStatusCallback] } }
__declspec(naked) void FakeWinHttpSetTimeouts() { _asm { jmp[winhttp.OrignalWinHttpSetTimeouts] } }
__declspec(naked) void FakeWinHttpTimeFromSystemTime() { _asm { jmp[winhttp.OrignalWinHttpTimeFromSystemTime] } }
__declspec(naked) void FakeWinHttpTimeToSystemTime() { _asm { jmp[winhttp.OrignalWinHttpTimeToSystemTime] } }
__declspec(naked) void FakeWinHttpWebSocketClose() { _asm { jmp[winhttp.OrignalWinHttpWebSocketClose] } }
__declspec(naked) void FakeWinHttpWebSocketCompleteUpgrade() { _asm { jmp[winhttp.OrignalWinHttpWebSocketCompleteUpgrade] } }
__declspec(naked) void FakeWinHttpWebSocketQueryCloseStatus() { _asm { jmp[winhttp.OrignalWinHttpWebSocketQueryCloseStatus] } }
__declspec(naked) void FakeWinHttpWebSocketReceive() { _asm { jmp[winhttp.OrignalWinHttpWebSocketReceive] } }
__declspec(naked) void FakeWinHttpWebSocketSend() { _asm { jmp[winhttp.OrignalWinHttpWebSocketSend] } }
__declspec(naked) void FakeWinHttpWebSocketShutdown() { _asm { jmp[winhttp.OrignalWinHttpWebSocketShutdown] } }
__declspec(naked) void FakeWinHttpWriteData() { _asm { jmp[winhttp.OrignalWinHttpWriteData] } }
__declspec(naked) void FakeWinHttpWriteProxySettings() { _asm { jmp[winhttp.OrignalWinHttpWriteProxySettings] } }


HMODULE payload;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	char path[MAX_PATH];
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		CopyMemory(path + GetSystemDirectory(path, MAX_PATH - 13), "\\winhttp.dll", 13);
		winhttp.dll = LoadLibrary(path);
		if (winhttp.dll == NULL)
		{
			MessageBox(0, TEXT("Cannot load original winhttp.dll library"), TEXT("Proxy"), MB_ICONERROR);
			ExitProcess(0);
		}
		winhttp.OrignalDllCanUnloadNow = GetProcAddress(winhttp.dll, "DllCanUnloadNow");
		winhttp.OrignalDllGetClassObject = GetProcAddress(winhttp.dll, "DllGetClassObject");
		winhttp.OrignalPrivate1 = GetProcAddress(winhttp.dll, "Private1");
		winhttp.OrignalSvchostPushServiceGlobals = GetProcAddress(winhttp.dll, "SvchostPushServiceGlobals");
		winhttp.OrignalWinHttpAddRequestHeaders = GetProcAddress(winhttp.dll, "WinHttpAddRequestHeaders");
		winhttp.OrignalWinHttpAddRequestHeadersEx = GetProcAddress(winhttp.dll, "WinHttpAddRequestHeadersEx");
		winhttp.OrignalWinHttpAutoProxySvcMain = GetProcAddress(winhttp.dll, "WinHttpAutoProxySvcMain");
		winhttp.OrignalWinHttpCheckPlatform = GetProcAddress(winhttp.dll, "WinHttpCheckPlatform");
		winhttp.OrignalWinHttpCloseHandle = GetProcAddress(winhttp.dll, "WinHttpCloseHandle");
		winhttp.OrignalWinHttpConnect = GetProcAddress(winhttp.dll, "WinHttpConnect");
		winhttp.OrignalWinHttpConnectionDeletePolicyEntries = GetProcAddress(winhttp.dll, "WinHttpConnectionDeletePolicyEntries");
		winhttp.OrignalWinHttpConnectionDeleteProxyInfo = GetProcAddress(winhttp.dll, "WinHttpConnectionDeleteProxyInfo");
		winhttp.OrignalWinHttpConnectionFreeNameList = GetProcAddress(winhttp.dll, "WinHttpConnectionFreeNameList");
		winhttp.OrignalWinHttpConnectionFreeProxyInfo = GetProcAddress(winhttp.dll, "WinHttpConnectionFreeProxyInfo");
		winhttp.OrignalWinHttpConnectionFreeProxyList = GetProcAddress(winhttp.dll, "WinHttpConnectionFreeProxyList");
		winhttp.OrignalWinHttpConnectionGetNameList = GetProcAddress(winhttp.dll, "WinHttpConnectionGetNameList");
		winhttp.OrignalWinHttpConnectionGetProxyInfo = GetProcAddress(winhttp.dll, "WinHttpConnectionGetProxyInfo");
		winhttp.OrignalWinHttpConnectionGetProxyList = GetProcAddress(winhttp.dll, "WinHttpConnectionGetProxyList");
		winhttp.OrignalWinHttpConnectionSetPolicyEntries = GetProcAddress(winhttp.dll, "WinHttpConnectionSetPolicyEntries");
		winhttp.OrignalWinHttpConnectionSetProxyInfo = GetProcAddress(winhttp.dll, "WinHttpConnectionSetProxyInfo");
		winhttp.OrignalWinHttpConnectionUpdateIfIndexTable = GetProcAddress(winhttp.dll, "WinHttpConnectionUpdateIfIndexTable");
		winhttp.OrignalWinHttpCrackUrl = GetProcAddress(winhttp.dll, "WinHttpCrackUrl");
		winhttp.OrignalWinHttpCreateProxyResolver = GetProcAddress(winhttp.dll, "WinHttpCreateProxyResolver");
		winhttp.OrignalWinHttpCreateUrl = GetProcAddress(winhttp.dll, "WinHttpCreateUrl");
		winhttp.OrignalWinHttpDetectAutoProxyConfigUrl = GetProcAddress(winhttp.dll, "WinHttpDetectAutoProxyConfigUrl");
		winhttp.OrignalWinHttpFreeProxyResult = GetProcAddress(winhttp.dll, "WinHttpFreeProxyResult");
		winhttp.OrignalWinHttpFreeProxyResultEx = GetProcAddress(winhttp.dll, "WinHttpFreeProxyResultEx");
		winhttp.OrignalWinHttpFreeProxySettings = GetProcAddress(winhttp.dll, "WinHttpFreeProxySettings");
		winhttp.OrignalWinHttpGetDefaultProxyConfiguration = GetProcAddress(winhttp.dll, "WinHttpGetDefaultProxyConfiguration");
		winhttp.OrignalWinHttpGetIEProxyConfigForCurrentUser = GetProcAddress(winhttp.dll, "WinHttpGetIEProxyConfigForCurrentUser");
		winhttp.OrignalWinHttpGetProxyForUrl = GetProcAddress(winhttp.dll, "WinHttpGetProxyForUrl");
		winhttp.OrignalWinHttpGetProxyForUrlEx = GetProcAddress(winhttp.dll, "WinHttpGetProxyForUrlEx");
		winhttp.OrignalWinHttpGetProxyForUrlEx2 = GetProcAddress(winhttp.dll, "WinHttpGetProxyForUrlEx2");
		winhttp.OrignalWinHttpGetProxyForUrlHvsi = GetProcAddress(winhttp.dll, "WinHttpGetProxyForUrlHvsi");
		winhttp.OrignalWinHttpGetProxyResult = GetProcAddress(winhttp.dll, "WinHttpGetProxyResult");
		winhttp.OrignalWinHttpGetProxyResultEx = GetProcAddress(winhttp.dll, "WinHttpGetProxyResultEx");
		winhttp.OrignalWinHttpGetProxySettingsVersion = GetProcAddress(winhttp.dll, "WinHttpGetProxySettingsVersion");
		winhttp.OrignalWinHttpGetTunnelSocket = GetProcAddress(winhttp.dll, "WinHttpGetTunnelSocket");
		winhttp.OrignalWinHttpOpen = GetProcAddress(winhttp.dll, "WinHttpOpen");
		winhttp.OrignalWinHttpOpenRequest = GetProcAddress(winhttp.dll, "WinHttpOpenRequest");
		winhttp.OrignalWinHttpPacJsWorkerMain = GetProcAddress(winhttp.dll, "WinHttpPacJsWorkerMain");
		winhttp.OrignalWinHttpProbeConnectivity = GetProcAddress(winhttp.dll, "WinHttpProbeConnectivity");
		winhttp.OrignalWinHttpQueryAuthSchemes = GetProcAddress(winhttp.dll, "WinHttpQueryAuthSchemes");
		winhttp.OrignalWinHttpQueryDataAvailable = GetProcAddress(winhttp.dll, "WinHttpQueryDataAvailable");
		winhttp.OrignalWinHttpQueryHeaders = GetProcAddress(winhttp.dll, "WinHttpQueryHeaders");
		winhttp.OrignalWinHttpQueryOption = GetProcAddress(winhttp.dll, "WinHttpQueryOption");
		winhttp.OrignalWinHttpReadData = GetProcAddress(winhttp.dll, "WinHttpReadData");
		winhttp.OrignalWinHttpReadProxySettings = GetProcAddress(winhttp.dll, "WinHttpReadProxySettings");
		winhttp.OrignalWinHttpReadProxySettingsHvsi = GetProcAddress(winhttp.dll, "WinHttpReadProxySettingsHvsi");
		winhttp.OrignalWinHttpReceiveResponse = GetProcAddress(winhttp.dll, "WinHttpReceiveResponse");
		winhttp.OrignalWinHttpResetAutoProxy = GetProcAddress(winhttp.dll, "WinHttpResetAutoProxy");
		winhttp.OrignalWinHttpSaveProxyCredentials = GetProcAddress(winhttp.dll, "WinHttpSaveProxyCredentials");
		winhttp.OrignalWinHttpSendRequest = GetProcAddress(winhttp.dll, "WinHttpSendRequest");
		winhttp.OrignalWinHttpSetCredentials = GetProcAddress(winhttp.dll, "WinHttpSetCredentials");
		winhttp.OrignalWinHttpSetDefaultProxyConfiguration = GetProcAddress(winhttp.dll, "WinHttpSetDefaultProxyConfiguration");
		winhttp.OrignalWinHttpSetOption = GetProcAddress(winhttp.dll, "WinHttpSetOption");
		winhttp.OrignalWinHttpSetProxySettingsPerUser = GetProcAddress(winhttp.dll, "WinHttpSetProxySettingsPerUser");
		winhttp.OrignalWinHttpSetStatusCallback = GetProcAddress(winhttp.dll, "WinHttpSetStatusCallback");
		winhttp.OrignalWinHttpSetTimeouts = GetProcAddress(winhttp.dll, "WinHttpSetTimeouts");
		winhttp.OrignalWinHttpTimeFromSystemTime = GetProcAddress(winhttp.dll, "WinHttpTimeFromSystemTime");
		winhttp.OrignalWinHttpTimeToSystemTime = GetProcAddress(winhttp.dll, "WinHttpTimeToSystemTime");
		winhttp.OrignalWinHttpWebSocketClose = GetProcAddress(winhttp.dll, "WinHttpWebSocketClose");
		winhttp.OrignalWinHttpWebSocketCompleteUpgrade = GetProcAddress(winhttp.dll, "WinHttpWebSocketCompleteUpgrade");
		winhttp.OrignalWinHttpWebSocketQueryCloseStatus = GetProcAddress(winhttp.dll, "WinHttpWebSocketQueryCloseStatus");
		winhttp.OrignalWinHttpWebSocketReceive = GetProcAddress(winhttp.dll, "WinHttpWebSocketReceive");
		winhttp.OrignalWinHttpWebSocketSend = GetProcAddress(winhttp.dll, "WinHttpWebSocketSend");
		winhttp.OrignalWinHttpWebSocketShutdown = GetProcAddress(winhttp.dll, "WinHttpWebSocketShutdown");
		winhttp.OrignalWinHttpWriteData = GetProcAddress(winhttp.dll, "WinHttpWriteData");
		winhttp.OrignalWinHttpWriteProxySettings = GetProcAddress(winhttp.dll, "WinHttpWriteProxySettings");

		payload = LoadLibrary("AUMPayload.dll");
		break;
	}
	case DLL_PROCESS_DETACH:
	{
		FreeLibrary(winhttp.dll);
		FreeLibrary(payload);
	}
	break;
	}
	return TRUE;
}
