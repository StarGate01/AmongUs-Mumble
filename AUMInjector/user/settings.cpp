#include <Windows.h>
#include <comdef.h>
#include <string>  
#include <iostream> 
#include <sstream>   
#include "settings.h"
#include "helpers.h"

Settings::Settings() :
	app("AmongUs-Mumble", "Among Us.exe"),
	mumbleExe("C:\\Program Files\\Mumble\\mumble.exe"),
	disableLogConsole(false),
	disableLogFile(false),
	logVerbosity(LOG_CODE::MSG),
	logFileName("ProximityLog.txt"),
	directionalAudio(false), 
	ghostVoiceMode(GHOST_VOICE_MODE::PURGATORY)
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
	app.add_option("--ghost-voice-mode", ghostVoiceMode, "Set ghost voice mode\n0 = Purgatory\n1 = Spectate\n2 = Haunt", true);
}

// Read the command line arguments and config file
void Settings::Parse()
{
	// Get arguments from OS
	int argc;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	// Convert arguments from unicode to narrow
	// Todo use c++11 codeconv instead of winapi
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

	RecalculateAudioMap();
}

// Generate audio coordinate map
void Settings::RecalculateAudioMap()
{
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

// Serialize the sync settings to a string
std::string Settings::SerializeSync()
{
	// Concat options using delemiter
	std::stringstream b;
	b << SYNC_VERSION;
	b << SYNC_DELEMITER;
	b << (directionalAudio? 1 : 0);
	b << SYNC_DELEMITER;
	b << static_cast<int>(ghostVoiceMode);
	return b.str();
}

// Deserialize the sync settings from a string
int Settings::DeserializeSync(std::string& input)
{
	// Split string by delemiter
	std::stringstream ss(input);
	std::string token;
	std::vector<std::string> cont;
	while (std::getline(ss, token, SYNC_DELEMITER)) cont.push_back(token);

	// Check version 
	if (cont.size() == 0) return SYNC_ERROR_NUM_ARGS;
	try { if (std::stoi(cont[0]) != SYNC_VERSION) return SYNC_ERROR_VERSION; }
	catch (...) { return SYNC_ERROR_FORMAT; }

	// Check number of parameters ( + 1 for version flag)
	if (cont.size() != SYNC_NUM_OPTIONS + 1) return SYNC_ERROR_NUM_ARGS;
	try
	{
		// Parse parameters
		directionalAudio = (std::stoi(cont[1]) == 1);
		ghostVoiceMode = static_cast<GHOST_VOICE_MODE>(std::stoi(cont[2]));
	}
	catch (...) { return SYNC_ERROR_FORMAT; }

	// Rebuild audio map for directional audio
	RecalculateAudioMap();
	return SYNC_SUCCESS;
}

// Prints the sync settings to a human readable string
std::string Settings::HumanReadableSync()
{
	std::stringstream b;
	b << "directional-audio=";
	b << (directionalAudio? "true":"false");
	b << ", ghost-voice-mode=";
	b << static_cast<int>(ghostVoiceMode);
	return b.str();
}

Settings appSettings;
