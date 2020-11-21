#include <Windows.h>
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
	// Define config options
	optionDetails = {
		{ "mumble", "Mumble executable path", &mumbleExe, OPTION_TYPE::STRING },
		{ "log-file-path", "Path to the log file", &logFileName, OPTION_TYPE::STRING },
		{ "no-log-console", "Disable logging to the console", &disableLogConsole, OPTION_TYPE::FLAG },
		{ "no-log-file", "Disable logging to a file", &disableLogFile, OPTION_TYPE::FLAG },
		{ "log-verbosity", "Log verbosity", &logVerbosity, OPTION_TYPE::INTEGER },
		{ "ghost-voice-mode", "Set ghost voice mode\n; 0 = Purgatory\n; 1 = Spectate\n; 2 = Haunt", &ghostVoiceMode, OPTION_TYPE::INTEGER },
		{ "directional-audio", "Enable directional audio", &directionalAudio, OPTION_TYPE::FLAG }
	};

	// Setup argument parser
	app.allow_extras(true);
	app.allow_config_extras(true);
	app.set_config("-c,--config", "ProximityConfig.ini", "Read an INI configuration file", false);
	for (auto const& op : optionDetails)
	{
		switch (op.type)
		{
		case OPTION_TYPE::FLAG:
			app.add_flag("--" + op.name, *(bool*)op.target, op.description);
			break;
		case OPTION_TYPE::INTEGER:
			app.add_option("--" + op.name, *(int*)op.target, op.description, true);
			break;
		case OPTION_TYPE::STRING:
			app.add_option("--" + op.name, *(std::string*)op.target, op.description, true);
			break;
		}
	}
}

// Saves the current config to the config file
void Settings::Save()
{
	// Create ini string
	std::stringstream res;
	res << "; " << app.get_description() << std::endl << std::endl;
	for (auto const& op : optionDetails)
	{
		switch (op.type)
		{
		case OPTION_TYPE::FLAG:
			res << "; " << op.description << std::endl << op.name << "=" << 
				((*(bool*)op.target) ? "true" : "false") << std::endl << std::endl;
			break;
		case OPTION_TYPE::INTEGER:
			res << "; " << op.description << std::endl << op.name << "=" <<
				*(int*)op.target << std::endl << std::endl;
			break;
		case OPTION_TYPE::STRING:
			res << "; " << op.description << std::endl << op.name << "=\"" <<
				*(std::string*)op.target << "\"" << std::endl << std::endl;
			break;
		}
	}

	// Write out config file
	std::ofstream configFileOut;
	configFileOut.open(app.get_config_ptr()->as<std::string>(), std::ios::out | std::ios::trunc);
	configFileOut << res.str();
	configFileOut.close();

	// Settings have changed, update the audio map
	RecalculateAudioMap();
}

// Read the command line arguments and config file
bool Settings::Parse()
{
	// Get arguments
	std::string cmdLine = GetCommandLine();

	// Parse arguments
	bool result = true;
	try { app.parse(cmdLine, true); }
	catch (...) 
	{ 
		// Ensure the user gets to see the error message
		result = false;
		disableLogConsole = false;
		disableLogFile = false;
		logVerbosity = LOG_CODE::MSG;
	}

	// Ensure valid config file exists
	Save();
	if (!result)
	{
		// If previous parse failes, try to read cleaned config file
		try { app.parse(cmdLine, true); }
		catch (...) {} // :(
	}

	// Rebuild computed options
	RecalculateAudioMap();

	return result;
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
