#pragma once

#include "CLI11.hpp"
#include "LoggingSystem.h"


// Increase this every time sync options format or amount changes
#define SYNC_VERSION 1 
#define SYNC_SIZE 2 // Number of payload bytes
#define SYNC_RPC_ID 42

// Credits info string
static const std::string CREDITS = R"(AmongUs-Mumble mod by:
  StarGate01 (chrz.de): Proxy DLL, Framework, Setup, Features.
  Alisenai (Alien):     Fixes, More Features.
  BillyDaBongo (Billy): Installer, Management, Testing.
  LelouBil:             Deobfuscation.
  ShumWengSang:         Impostor Radio.
  Mogster7:             Debugging Tools, Radar.

Source code and download: https://github.com/StarGate01/AmongUs-Mumble
Freely available and licensed under the GNU GPLv3.

Press DEL to open/close the GUI.
)";


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
			PURGATORY = 0, // Only talk to other ghosts at full volume
			SPECTATE = 1,  // Can hear players, can't talk
			HAUNT = 2,     // Can hear and talk to players
			COUNT = 3      // Needed for UI
		};

		CLI::App app;

		std::vector<ConfigOption> optionDetails;

		// General options
		std::string mumbleExe;
		bool disableLogConsole;
		bool disableLogFile;
		bool disableOverlay;
		bool disableDirectx;
		LOG_CODE logVerbosity;
		std::string logFileName;
		int wineUID;

		// Computed options
		int audioCoordinateMap[3];

		// Sync options
		bool directionalAudio;
		GHOST_VOICE_MODE ghostVoiceMode;

		// Should the sync settings be broadcasted ont he next tick
		bool mustBroadcast = false;
		long long lastBroadcastMs = 0;


		// Setup argument parser
		Settings();

		// Saves the current config to the config file
		void Save();

		// Read the command line arguments and config file
		bool Parse();

		// Generate audio coordinate map
		void RecalculateAudioMap();

		// Prints the sync settings to a human readable string
		std::string HumanReadableSync();

		// Player control to use Radio
		char radioKey = 'E';
};

extern Settings appSettings;
