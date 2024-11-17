#include <iostream>
#include <ALogger.hpp>
#include <DefaultLogFormatter.hpp>

namespace vp
{
/**
 * @brief Constructor for ALogger
 */
ALogger::ALogger()
{
	m_bLogStdoutEnabled = false;
	m_lMaxLogLength = 4096;
	m_strFilePath = ".";
	m_strFileName = "logs";
	m_lLogLevels = LogLevel::LOG_LEVEL_ALL;
	m_prLogFormatter.first = nullptr;
	m_prLogFormatter.second = nullptr;
}

/**
 * @brief Destructor for ALogger
 */
ALogger::~ALogger()
{
}

/**
 * @brief Set the file path for the log file
 * @param pzFilePath Path to the log file
 */
auto ALogger::setFilePath(const char *pzFilePath) -> void
{
	m_strFilePath = std::string(pzFilePath);
}

/**
 * @brief Set the file name for the log file
 * @param pzFileName Name of the log file
 */
auto ALogger::setFileName(const char *pzFileName) -> void
{
	m_strFileName = std::string(pzFileName);
}

/**
 * @brief Set the maximum log length
 * @param lMaxLogLength Maximum length of a log message
 */
auto ALogger::setMaxLogLength(long lMaxLogLength) -> void
{
	m_lMaxLogLength = lMaxLogLength;
}

/**
 * @brief Set the log standard out enabled flag
 * @param bLogStdoutEnabled True to enable log output, false to disable
 */
auto ALogger::setLogStdoutEnabled(bool bLogStdoutEnabled) -> void
{
	m_bLogStdoutEnabled = bLogStdoutEnabled;
}

/**
 * @brief Set the log level
 * 
 * You can set the log level using the logical operation "&".
 * For example, if you only want to print “Error” and “Warning”,
 * you can input LOG_LEVEL_WARNING & LOG_LEVEL_ERROR = 0x01.
 * 
 * @param eLogLevels Log level to set
 */
auto ALogger::setLogLevel(long lLogLevels) -> void
{
	m_lLogLevels = lLogLevels;
}

/**
 * @brief Set the log formatter
 * @param pclLogFormatter Pointer to the log formatter
 */
auto ALogger::setLogFormatter(ILogFormatter *pclLogFormatter) -> void
{
	m_prLogFormatter.second = pclLogFormatter;
}

/**
 * @brief Initialize the logger
 * @return ret_t Return status
 */
auto ALogger::initialize() -> ret_t
{
	if (m_prLogFormatter.second == nullptr) {
		m_prLogFormatter.first = new DefaultLogFormatter();
		m_prLogFormatter.second = m_prLogFormatter.first;
	}
	m_ofsLogFile.open(m_strFilePath + "/" + m_strFileName, std::ios_base::app);
	if (!m_ofsLogFile.is_open()) {
		std::error_code ec(errno, std::system_category());
		std::cerr << "Failed to open log file : " << ec.message() << std::endl;
		return ret_t::RET_FAILURE;
	}

	return ret_t::RET_SUCCESS;
}

/**
 * @brief Finalize the logger
 * @return ret_t Return status
 */
auto ALogger::finalize() -> ret_t
{
	m_ofsLogFile.close();
	if (m_prLogFormatter.first != nullptr) {
		delete m_prLogFormatter.first;
		m_prLogFormatter.first = nullptr;
		m_prLogFormatter.second = nullptr;
	}

	return ret_t::RET_SUCCESS;
}

/**
 * @brief Log a message
 * @param eLogLevel Log level
 * @param pzFileName File name
 * @param pzFunctionName Function name
 * @param nLine Line number
 * @param pzFormat Format string
 * @param ... Additional arguments
 * @return ret_t Return status
 */
auto ALogger::putLog(LogLevel eLogLevel, const char *pzFileName, const char *pzFunctionName, int nLine, const char *pzFormat, ...)  -> ret_t
{
	if (!(m_lLogLevels & eLogLevel)) {
		return ret_t::RET_SUCCESS;
	}
	
	char zBuffer[m_lMaxLogLength + 1];
	int nLogLength;
	va_list args;
	va_start(args, pzFormat);
	nLogLength = m_prLogFormatter.second->format(zBuffer, m_lMaxLogLength, eLogLevel, pzFileName, pzFunctionName, nLine, pzFormat, args);
	va_end(args);
	return writeLog(zBuffer, nLogLength);
}

/**
 * @brief Write a log sring on file and/or console
 * @param pzLogString Log string
 * @param nLogLength Log length
 * @return ret_t Return status
 */
auto ALogger::write(const char *pzLogString, int nLogLength) -> ret_t
{
	if (m_bLogStdoutEnabled) {
		std::cout << pzLogString << std::endl;
	}
	m_ofsLogFile << pzLogString << std::endl;

	return ret_t::RET_SUCCESS;
}
}
