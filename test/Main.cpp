#include <vector>
#include <SimpleLogger.hpp>
#include <ThreadedLogger.hpp>
#include <DefaultLogFormatter.hpp>

using namespace vp;

#define LOG_TRC(...)  _LOG_TRC(logger, __VA_ARGS__)
#define LOG_DBG(...)  _LOG_DBG(logger, __VA_ARGS__)
#define LOG_INFO(...) _LOG_INFO(logger, __VA_ARGS__)
#define LOG_WARN(...) _LOG_WARN(logger, __VA_ARGS__)
#define LOG_ERR(...)  _LOG_ERR(logger, __VA_ARGS__)

auto TestSimpleLogger() -> int; // Test simple logger
auto TestThreadedLogger() -> int; // Test threaded logger
auto TestUserLogFomatter() -> int; // Test new log formatter

//----------------------------------------
// Main
//----------------------------------------
int main(void)
{
	TestSimpleLogger();
	TestThreadedLogger();
	TestUserLogFomatter();

	return 0;
}

//----------------------------------------
// Test simple logger
//----------------------------------------
auto TestSimpleLogger() -> int
{
	SimpleLogger logger;

	{ // Bassic logger settings
		ALogger &abst = logger;
		abst.setFilePath("."); // Set the log file path
		abst.setFileName("test.log"); // Set the log file name
		abst.setMaxLogLength(4096); // Set the maximum log length
		abst.setLogLevel(LogLevel::LOG_LEVEL_ALL); // LogLevel::LOG_LEVEL_ALL for all Log Levels.
													// You can set multiple log levels using the logical operation "|".
													// For example, if you only want to print “Error” and “Warning”,
													// you can input LogLevel::LOG_LEVEL_WARNING | LogLevel::LOG_LEVEL_ERROR.
		abst.setLogStdoutEnabled(true); // Enable printing log to standard output
	}

	// Initialize the logger
	if (logger.initialize() != RetType::RET_SUCCESS) {
		fprintf(stderr, "Failed to initialize logger\n");
		return -1;
	}

	LOG_TRC( "Hello world!! [T]");
	LOG_DBG( "Hello world!! [D]");
	LOG_INFO("Hello world!! [I]");
	LOG_WARN("Hello world!! [W]");
	LOG_ERR( "Hello world!! [E]");

	// Finalize the logger
	if (logger.finalize() != RetType::RET_SUCCESS) {
		fprintf(stderr, "Failed to finalize logger\n");
		return -1;
	}

	return 0;
}

//----------------------------------------
// Test threaded logger
//----------------------------------------
auto TestThreadedLogger() -> int
{
	ThreadedLogger logger;

	{ // Bassic logger settings
		ALogger &abst = logger;
		abst.setFilePath(".");
		abst.setFileName("test.log");
		abst.setMaxLogLength(4096);
		abst.setLogLevel(LogLevel::LOG_LEVEL_ALL);
		abst.setLogStdoutEnabled(true);
	}

	{ // Threaded logger settings
		logger.setMaxQueueSize(8192); // Set the maximum queue size (Default 4096)
		logger.setPollingSleepUs(1); // Set the polling sleep time in micro seconds (0 means no sleep but polling, Default 1000)
	}

	// Initialize the logger
	if (logger.initialize() != RetType::RET_SUCCESS) {
		fprintf(stderr, "Failed to initialize logger\n");
		return -1;
	}

	// Print log
	LOG_TRC( "Hello world!! [T]");
	LOG_DBG( "Hello world!! [D]");
	LOG_INFO("Hello world!! [I]");
	LOG_WARN("Hello world!! [W]");
	LOG_ERR( "Hello world!! [E]");

	// Finalize the logger
	if (logger.finalize() != RetType::RET_SUCCESS) {
		fprintf(stderr, "Failed to finalize logger\n");
		return -1;
	}

	return 0;
}

//----------------------------------------
// Test user log formatter
//----------------------------------------
auto TestUserLogFomatter() -> int
{
	// User log formatter class
	class UserLogFormatter : public ILogFormatter
	{
	public:
		UserLogFormatter() = default;
		virtual ~UserLogFormatter() = default;
		virtual auto format(char *pzLogBuffer, int nLogBufferLength,
							LogLevel eLogLevel, const char *pzFileName, const char *pzFunctionName, int nLine,
							const char *pzFormat, va_list &vaList) -> int
		{
			int nLength = 0;
			nLength = snprintf(pzLogBuffer, nLogBufferLength, "[%02ld] [%s:%d] [%s] ", eLogLevel, pzFileName, nLine, pzFunctionName);
			nLength += vsnprintf(pzLogBuffer + nLength, nLogBufferLength - nLength, pzFormat, vaList);
			return nLength;
		}
	};

	SimpleLogger logger;
	UserLogFormatter fomatter;

	{ // Bassic logger settings
		ALogger &abst = logger;
		abst.setFilePath(".");
		abst.setFileName("test.log");
		abst.setMaxLogLength(4096);
		abst.setLogLevel(LogLevel::LOG_LEVEL_ALL);
		abst.setLogStdoutEnabled(true);
		abst.setLogFormatter(&fomatter); // Set a user log formatter
	}

	// Initialize the logger
	if (logger.initialize() != RetType::RET_SUCCESS) {
		fprintf(stderr, "Failed to initialize logger\n");
		return -1;
	}

	// Print log
	LOG_TRC( "Hello world!! [T]");
	LOG_DBG( "Hello world!! [D]");
	LOG_INFO("Hello world!! [I]");
	LOG_WARN("Hello world!! [W]");
	LOG_ERR( "Hello world!! [E]");

	// Finalize the logger
	if (logger.finalize() != RetType::RET_SUCCESS) {
		fprintf(stderr, "Failed to finalize logger\n");
		return -1;
	}

	return 0;
}

