#pragma once

#include <string>
#include "CLI11.hpp"
#include "LoggingSystem.h"


// Options for settings sync
#define SYNC_HEADER '\a'
#define SYNC_DELEMITER ';'
#define SYNC_NUM_OPTIONS 2
#define SYNC_VERSION 0 // Increase this every time sync options format or amount changes

// Settings sync error codes
#define SYNC_SUCCESS 0
#define SYNC_ERROR_NUM_ARGS 1
#define SYNC_ERROR_VERSION 2
#define SYNC_ERROR_FORMAT 3

// This class holds the settings for the game
class Settings
{

public:

	// Type of a config option
	enum class OPTION_TYPE : int
	{
		STRING = 0,
		INTEGER = 1,
		FLAG = 2
	};

	// Stores metadata for a config option
	struct ConfigOption
	{
		std::string name;
		std::string description;
		void* target;
		OPTION_TYPE type;
	};

	// Choices for ghost modes
	enum class GHOST_VOICE_MODE : int
	{
		PURGATORY, // Only talk to other ghosts at full volume
		SPECTATE,  // Can hear players, can't talk
		HAUNT,     // Can hear and talk to players
		COUNT
	};

	CLI::App app;

	std::vector<ConfigOption> optionDetails;

	// General options
	std::string mumbleExe;
	bool disableLogConsole;
	bool disableLogFile;
	LOG_CODE logVerbosity;
	std::string logFileName;

	// Computed options
	int audioCoordinateMap[3];

	// Sync options
	bool directionalAudio;
	GHOST_VOICE_MODE ghostVoiceMode;

	// Setup argument parser
	Settings();

	// Saves the current config to the config file
	void Save();

	// Read the command line arguments and config file
	bool Parse();

	// Generate audio coordinate map
	void RecalculateAudioMap();

	// Serialize the sync settings to a string
	std::string SerializeSync();

	// Deserialize the sync settings from a string
	int DeserializeSync(std::string& input);

	// Prints the sync settings to a human readable string
	std::string HumanReadableSync();

};

extern Settings appSettings;
