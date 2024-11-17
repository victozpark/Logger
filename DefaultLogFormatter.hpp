#ifndef __DEFAULT_LOG_FORMATTER_HPP__
#define __DEFAULT_LOG_FORMATTER_HPP__

#include <ILogFormatter.hpp>

namespace vp
{
/**
 * @brief Default log formatter
 */
class DefaultLogFormatter : public ILogFormatter
{
public:
	DefaultLogFormatter() = default;
	virtual ~DefaultLogFormatter() = default;
	virtual auto getLogLevelChar(LogLevel eLogLevel) -> char;
	virtual auto getThreadId() -> std::string;
	virtual auto format(char *pzLogBuffer, int nLogBufferLength,
						LogLevel eLogLevel, const char *pzFileName, const char *pzFunctionName, int nLine,
						const char *pzFormat, va_list &vaList) -> int;
};
}

#endif // __DEFAULT_LOG_FORMATTER_HPP__