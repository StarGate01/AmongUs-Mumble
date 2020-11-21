#include <windows.h>
#include <iostream>
#include <string>
#include "helpers.h"
#include "LoggingSystem.h"


// Global externs for the logging system
LoggingSystem logger;

// Closes the file, if needed
LoggingSystem::~LoggingSystem()
{
	// Close the file, if needed
	if (logToFile)
		logFile.close();
}

// Enables logging to console
void LoggingSystem::EnableConsoleLogging()
{
	// Only open the console if not already opened
	if (!logToConsole)
	{
		logToConsole = true;

		// Open a console (to log to)
		AllocConsole();
		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
		ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
	}
}

// Enables logging to file
void LoggingSystem::EnableFileLogging(const std::string& logFilePath)
{
	// Only open the file if not already opened
	if (!logToFile)
	{
		logToFile = true;

		// Open the log file, based on the pre-defined location
		// Placement new because std::ofstream is NOT copyable
		new(&logFile) std::ofstream(logFilePath, std::ios::out | std::ios::trunc);

		if (!logFile.is_open())
		{
			// Don't log to file, something went wrong
			Log(LOG_CODE::LOG_CODE_WARNING, "Could not initialize the log file - will not log to file");
			logToFile = false;
		}
	}
}

// Sets the max verbosity to print (anything above will not be printed)
void LoggingSystem::SetVerbosity(LOG_CODE verbosity)
{
	this->verbosity = verbosity;
}

// Prints the string for the code to the log (and possibly the file)
std::string LoggingSystem::GetLogCodeString(LOG_CODE logCode)
{
	// Return the log code string
	return ("[" + logPrefixes[(unsigned) logCode] + "] ");
}

// Checks if the cursor is at the end of the line
bool LoggingSystem::CursorAtEnd()
{
	if (logToConsole)
	{
		CONSOLE_SCREEN_BUFFER_INFO cbsi;
		if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi))
			return (cbsi.dwCursorPosition.X != 0);
	}
	return false;
}


// Logs a message to the console window
// Newline is ensured (for flushing)
void LoggingSystem::Log(LOG_CODE logCode, std::string message, bool includePrefix)
{
	// Don't log due to set verbosity level
	if (logCode > verbosity) return;

	// Build the whole string in advance, to prevent thread cross-printing
	std::string finalText = (CursorAtEnd()? "\n":"") + (includePrefix? GetLogCodeString(logCode) : "") +
		message + "\n";

	// Print the message, if needed
	if (logToConsole)
		std::cout << finalText << std::flush;

	// Log to file, if needed
	if (logToFile)
	{
		logFile << finalText;
		logFile.flush();
	}
}

// Logs a message to the console window, using the familiar "printf" format
// Newline is ensured (for flushing)
void LoggingSystem::LogVariadic(LOG_CODE logCode, bool sameLine, const char* formatString, ...)
{
	// Don't log due to set verbosity level
	if (logCode > verbosity) return;

	va_list argp = { nullptr };

	// Get the exact size needed by getting the size of the result string
	va_start(argp, formatString);
	int bufferLen = vsnprintf(nullptr, 0, formatString, argp) + 1;
	va_end(argp);

	// Create a buffer for the string
	char* newString = (char*)malloc(bufferLen);

	// Malloc returned null (bad, but only a single message is missed)
	if (!newString) return;

	// Null-terminate the string
	newString[bufferLen - 1] = '\0';

	// Format the string into the buffer
	va_start(argp, formatString);
	vsprintf_s(newString, bufferLen, formatString, argp);
	va_end(argp);

	// Add the prefix to the gives format string
	// Do not print a new line if current line should be overwritten
	sameLine = sameLine && logToConsole;
	std::string message = (sameLine? "\r":(CursorAtEnd()? "\n":"")) +
		GetLogCodeString(logCode) + newString + (sameLine? "":"\n");
	
	// Print the message, if needed
	if (logToConsole) std::cout << message.c_str() << std::flush;

	// Log to file, if needed
	if (logToFile) logFile << message << std::flush;

	// Clean up dynamic memory
	free(newString);
}
