#include <unistd.h>
#include <thread>
#include <iostream>
#include <sstream>
#include <DefaultLogFormatter.hpp>

namespace vp
{
/**
 * @brief Get the log level character
 * @param eLogLevel Log level
 * @return Log level character (T, D, I, W, E)
 */
auto DefaultLogFormatter::getLogLevelChar(LogLevel eLogLevel) -> char
{
	switch (eLogLevel) {
	case LogLevel::LOG_LEVEL_TRACE:
		return 'T';
	case LogLevel::LOG_LEVEL_DEBUG:
		return 'D';
	case LogLevel::LOG_LEVEL_INFO:
		return 'I';
	case LogLevel::LOG_LEVEL_WARNING:
		return 'W';
	case LogLevel::LOG_LEVEL_ERROR:
		return 'E';
	default:
		return 'U';
	}
	return 'U';
}

/**
 * @brief Get the thread ID
 * @return Thread ID
 */
auto DefaultLogFormatter::getThreadId() -> std::string
{
	std::stringstream ss;
  	ss << std::hex << std::this_thread::get_id();
	size_t nTidPrintSize = 6;
	int nSsPos = (ss.str().length() - 2) <= nTidPrintSize ? 2 : ss.str().length() - nTidPrintSize;
	return ss.str().substr(nSsPos).c_str();
}

/**
 * @brief Format the log message
 * @param pzLogBuffer Buffer to store the formatted log message
 * @param nLogBufferLength Length of the buffer
 * @param eLogLevel Log level
 * @param pzFileName File name
 * @param pzFunctionName Function name
 * @param nLine Line number
 * @param pzFormat Format string
 * @param vaList Additional arguments
 * @return Length of the formatted log message
 */
auto DefaultLogFormatter::format(char *pzLogBuffer, int nLogBufferLength,
						LogLevel eLogLevel, const char *pzFileName, const char *pzFunctionName, int nLine,
						const char *pzFormat, va_list &vaList) -> int
{
	int nLogBufferLength_1 = nLogBufferLength - 1;
	auto sckNow = std::chrono::system_clock::now();
    auto ttmNow = std::chrono::system_clock::to_time_t(sckNow);
	std::tm tmNow;
    localtime_r(&ttmNow, &tmNow);;
	auto usec = std::chrono::duration_cast<std::chrono::microseconds>(sckNow.time_since_epoch()) % 1000000;
	int nLength = snprintf(pzLogBuffer, nLogBufferLength_1, "[%c][%02d:%02d:%02d.%06ld][%-16.16s:%-16.16s:%04d][%06d][%s] ",
							getLogLevelChar(eLogLevel), tmNow.tm_hour, tmNow.tm_min, tmNow.tm_sec, (long)usec.count(),
							pzFileName, pzFunctionName, nLine, (int)getpid(), getThreadId().c_str());
	nLength += vsnprintf(pzLogBuffer + nLength, nLogBufferLength_1 - nLength, pzFormat, vaList);
	pzLogBuffer[nLogBufferLength_1] = 0x00;

	return nLength;
}
}
