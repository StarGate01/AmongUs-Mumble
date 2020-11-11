#include <string>
#include <fstream>
#include <iostream>

// File to use for logging messages from the logging system
#define LOGGING_FILE "ProximityLogFile.txt"

enum class LOG_CODE
{
	// Something went wrong
	LOG_CODE_ERROR = 3,
	ERR = 3,
	// Something bad may have happened
	LOG_CODE_WARNING = 2,
	WRN = 2,
	// Information about what's happening
	LOG_CODE_INFO = 1,
	INF = 1,
	// Telling the user something
	LOG_CODE_MESSAGE = 0,
	MSG = 0,
	// Verbose output
	LOG_CODE_DEBUG = 4,
	DBG = 4,
	// Enum length
	COUNT
};


// Logging system that is similar to /dev/null
// Used when no output is desired (used by the LoggingSystem) 
class DevNullLogger : public std::streambuf, public std::ostream
{
private:
	int overflow(int c)
	{ return 0; }

public:
	DevNullLogger() : std::ostream(this)
	{}
};


class LoggingSystem : public std::streambuf, public std::ostream
{
private:
	// Lookup tabe to be used with the LOG_CODE enum for message prefixes
	std::string logPrefixes[(unsigned) LOG_CODE::COUNT] = {
			"ERR", "WRN", "INF", "MSG", "DBG"
	};

	// If the logging system log to a file
	bool logToFile = false;

	// Output log file
	std::ofstream logFile;

	// Verbosity level, anything above will not be logged
	LOG_CODE verbosity = LOG_CODE::DBG;

	// Prints the string for the code to the log (and possibly the file)
	void LogCode(LOG_CODE logCode);

	// Implemented for operator<< to work (from the inherited class)
	int overflow(int c);

public:
	// Opens a console to prepare for logging
	LoggingSystem();

	// Closes the file, if needed
	~LoggingSystem();

	// Enables logging to file
	void EnableFileLogging();

	// Sets the max verbosity to print (anything above will not be printed)
	void SetVerbosity(LOG_CODE verbosity);

	// Logs a message to the console window, defaults to a message log type
	void Log(std::string message, LOG_CODE logCode = LOG_CODE::MSG, bool addNewLine = true);

	// Sets up the logging system for operator<<
	std::ostream &BeginLog(LOG_CODE logCode);
};

// Global extern logging system
extern LoggingSystem logger;
extern DevNullLogger devNullLogger;
