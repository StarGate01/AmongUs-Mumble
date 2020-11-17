#pragma once

#include <string>
#include "CLI11.hpp"
#include "LoggingSystem.h"


class Settings
{
	public:
		enum class GHOST_VOICE_MODE
		{
			PURGATORY,
			SPECTATE,
			HAUNT
		};

		CLI::App app;
		std::string mumbleExe;
		bool disableLogConsole;
		bool disableLogFile;
		LOG_CODE logVerbosity;
		std::string logFileName;
		bool directionalAudio;
		int audioCoordinateMap[3];
		GHOST_VOICE_MODE ghostVoiceMode;

		Settings();
		void Parse();
};

extern Settings appSettings;
