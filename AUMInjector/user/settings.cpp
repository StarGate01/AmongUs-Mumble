#include <Windows.h>
#include <comdef.h>
#include <iostream>
#include "settings.h"
#include "helpers.h"

Settings::Settings():
	app("AmongUs-Mumble", "Among Us.exe"),
	mumbleExe("C:\\Program Files\\Mumble\\mumble.exe"),
	disableLogConsole(false),
	disableLogFile(false),
	logVerbosity(LOG_CODE::MSG),
	logFileName("ProximityLog.txt"),
	directionalAudio(false),
	ghostVoiceMode(Settings::GHOST_VOICE_MODE::PURGATORY)
{ }

void Settings::Parse()
{
	// Setup argument parser
	app.allow_extras(true);
	app.allow_config_extras(true);
	app.set_config("-c,--config", "ProximityConfig.ini", "Read an INI configuration file", false);
	app.add_option("-m,--mumble", mumbleExe, "Mumble executable path", true);
	app.add_flag("--no-log-console", disableLogConsole, "Disable logging to the console");
	app.add_flag("--no-log-file", disableLogFile, "Disable logging to a file");
	app.add_option("--log-file-path", logFileName, "Path to the log file", true);
	app.add_option("--log-verbosity", logVerbosity, "Log verbosity", true);
	app.add_flag("--directional-audio", directionalAudio, "Enable directional audio");
	app.add_option("--ghost-voice-mode", ghostVoiceMode, "Set ghost voice mode", true);
	// Get arguments from OS
	int argc;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	// Convert arguments from unicode to narrow
	_bstr_t** argv_bstr = (_bstr_t**)malloc(argc * sizeof(_bstr_t*));
	char** argv_narrow = (char**)malloc(argc * sizeof(char*));
	for (int i = 0; i < argc; i++)
	{
		argv_bstr[i] = (_bstr_t*)new _bstr_t(argv[i]);
		argv_narrow[i] = (_bstr_t)*argv_bstr[i];
	}
	// Parse arguments
	app.parse(argc, argv_narrow);
	// Free temp buffers
	LocalFree(argv);
	for (int i = 0; i < argc; i++)
	{
		argv_bstr[i]->~_bstr_t();
		free(argv_bstr[i]);
	}
	free(argv_bstr);
	free(argv_narrow);

	// Write out config file
	std::ofstream configFileOut;
	configFileOut.open(app.get_config_ptr()->as<std::string>(), std::ios::out | std::ios::trunc);
	// Serialize settings with annotations
	configFileOut << app.config_to_str(true, true);
	configFileOut.close();

	// Generate audio coordinate map
	// Mumble -> Ingame
	if (directionalAudio)
	{
		audioCoordinateMap[0] = 0; // X -> X
		audioCoordinateMap[1] = 2; // Y -> 0
		audioCoordinateMap[2] = 1; // Z -> Y
	}
	else
	{
		audioCoordinateMap[0] = 2; // X -> 0
		audioCoordinateMap[1] = 0; // Y -> X
		audioCoordinateMap[2] = 1; // Z -> Y
	}
}

Settings appSettings;
