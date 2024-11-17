#ifndef __I_LOG_FORMATTER_HPP__
#define __I_LOG_FORMATTER_HPP__

#include <Logger.h>

namespace vp
{
/**
 * @brief Interface for log formatter
 */
class ILogFormatter
{
public:
	virtual ~ILogFormatter() = 0;
	virtual auto format(char *pzLogBuffer, int nLogBufferLength,
						LogLevel eLogLevel, const char *pzFileName, const char *pzFunctionName, int nLine,
						const char *pzFormat, va_list &vaList) -> int = 0;
};

inline ILogFormatter::~ILogFormatter() = default;
}

#endif // __I_LOG_FORMATTER_HPP__