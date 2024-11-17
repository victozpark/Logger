#include <SimpleLogger.hpp>

namespace vp
{
/**
 * @brief Constructor for SimpleLogger
 */
SimpleLogger::SimpleLogger()
{
}

/**
 * @brief Destructor for SimpleLogger
 */
SimpleLogger::~SimpleLogger()
{
}

/**
 * @brief Initialize the logger
 * @return ret_t Return status
 */
auto SimpleLogger::initialize() -> ret_t
{
	return ALogger::initialize();
}

/**
 * @brief Finalize the logger
 * @return  Return status
 */
auto SimpleLogger::finalize() -> ret_t
{
	return ALogger::finalize();
}

/**
 * @brief Write the log message
 * @param pzLogString Log message
 * @param nLogLength Length of the log message
 * @return ret_t Return status
 */
auto SimpleLogger::writeLog(const char *pzLogString, int nLogLength) -> ret_t
{
	return write(pzLogString, nLogLength);
}
}
