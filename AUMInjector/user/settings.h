#pragma once

#include <string>
#include "CLI11.hpp"
#include "LoggingSystem.h"

class Settings
{
	public:
		CLI::App app;
		std::string mumbleExe;
		bool disableLogConsole;
		bool disableLogFile;
		LOG_CODE logVerbosity;
		std::string logFileName;
		bool directionalAudio;
		int audioCoordinateMap[3];

		Settings();
		void Parse();
};

extern Settings appSettings;
