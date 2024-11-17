#ifndef __SIMPLE_LOGGER_HPP__
#define __SIMPLE_LOGGER_HPP__

#include <ALogger.hpp>

namespace vp
{
/**
 * @brief Simple logger class
 */
class SimpleLogger : public ALogger
{
public:
	SimpleLogger();
	virtual ~SimpleLogger();
	virtual auto initialize() -> ret_t;
	virtual auto finalize() -> ret_t;
protected:
	virtual auto writeLog(const char *pzLogString, int nLogLength) -> ret_t;
};
}

#endif // __SIMPLE_LOGGER_HPP__