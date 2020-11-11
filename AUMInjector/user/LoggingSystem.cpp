#include "LoggingSystem.h"
#include <iostream>

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <string>
#include "helpers.h"

// Global externs for the logging system
LoggingSystem logger;
DevNullLogger devNullLogger;

LoggingSystem::LoggingSystem() : std::ostream(this)
{
	// Open a console (to log to)
	AllocConsole();
	freopen_s((FILE **) stdout, "CONOUT$", "w", stdout);
}

LoggingSystem::~LoggingSystem()
{
	// Close the file, if needed
	if (logToFile)
		logFile.close();
}

// Enables logging to file
void LoggingSystem::EnableFileLogging()
{
	// Only open the file if not already opened
	if (!logToFile)
	{
		logToFile = true;

		// Open the log file, based on the pre-defined location
		// Placement new because std::ofstream is NOT copyable
		new(&logFile) std::ofstream(LOGGING_FILE, std::ios::out);

		// Failed to open the log file
		if (!logFile.is_open())
		{
			// Don't log to file, something went wrong
			Log("Could not initalize the log file - will not log to file", LOG_CODE::LOG_CODE_WARNING);
			logToFile = false;
		}
	}
}

// Sets the max verbosity to print (anything above will not be printed)
void LoggingSystem::SetVerbosity(LOG_CODE verbosity)
{
	this->verbosity = verbosity;
}

void LoggingSystem::LogCode(LOG_CODE logCode)
{
	// Print to console
	std::cout << "[" + logPrefixes[(unsigned) logCode] + "] ";

	// Log to file (optionally)
	if (logToFile)
		logFile << "[" + logPrefixes[(unsigned) logCode] + "] ";
}

// Implemented for operator<< to work (from the inherited class)
int LoggingSystem::overflow(int c)
{
	// Print to console
	std::cout.put((char)c);

	// Log to file (optionally)
	if (logToFile)
		logFile << (char)c; //Would use "logFile.put(c);", but it has edge cases
	return 0;
}

void LoggingSystem::Log(std::string message, LOG_CODE logCode, bool addNewLine)
{
	// Don't log due to set verbosity level
	if (logCode > verbosity) return;

	// Log the given code (in the right format)
	LogCode(logCode);

	// Log to console
	std::cout << message << std::endl;

	// Log to file
	if (logToFile)
		logFile << message << std::endl;
}

// Sets up the logging system for operator<<
std::ostream &LoggingSystem::BeginLog(LOG_CODE logCode)
{
	// Return the null logger so the chained operators don't have any effect
	if (logCode > verbosity) return devNullLogger;

	// Prints the log and returns a reference to the extern
	LogCode(logCode);
	return *this;
}
