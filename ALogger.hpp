#ifndef __A_LOGGER_HPP__
#define __A_LOGGER_HPP__

#include <Logger.h>
#include <ILogFormatter.hpp>

namespace vp
{
/**
 * @brief Abstract Logger class
 */
class ALogger
{

public:
	ALogger();
	virtual ~ALogger();
	virtual auto setFilePath(const char *pzFilePath) -> void;
	virtual auto setFileName(const char *pzFileName) -> void;
	virtual auto setMaxLogLength(long lMaxLogLength) -> void;
	virtual auto setLogStdoutEnabled(bool bLogStdoutEnabled) -> void;
	virtual auto setLogLevel(long lLogLevels) -> void;
	virtual auto setLogFormatter(ILogFormatter *pclLogFormatter) -> void;
	virtual auto initialize() -> ret_t;
	virtual auto finalize() -> ret_t;
	virtual auto putLog(LogLevel eLogLevel, const char *pzFileName, const char *pzFunctionName, int nLine,
						const char *pzFormat, ...) -> ret_t;
protected:
	virtual auto writeLog(const char *pzLogString, int nLogLength) -> ret_t = 0;
	virtual auto write(const char *pzLogString, int nLogLength) -> ret_t;

private:
	bool m_bLogStdoutEnabled;
	long m_lMaxLogLength;
	std::string m_strFilePath;
	std::string m_strFileName;
	std::ofstream m_ofsLogFile;
	long m_lLogLevels;
	std::pair<ILogFormatter *, ILogFormatter *> m_prLogFormatter;
};
}

#endif // __A_LOGGER_HPP__