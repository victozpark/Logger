#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdarg.h>
#include <string>
#include <fstream>

namespace vp
{
#define _LOG_TRC(logger, ...)  (logger).putLog(LogLevel::LOG_LEVEL_TRACE, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define _LOG_DBG(logger, ...)  (logger).putLog(LogLevel::LOG_LEVEL_DEBUG, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define _LOG_INFO(logger, ...) (logger).putLog(LogLevel::LOG_LEVEL_INFO, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define _LOG_WARN(logger, ...) (logger).putLog(LogLevel::LOG_LEVEL_WARNING, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define _LOG_ERR(logger, ...)  (logger).putLog(LogLevel::LOG_LEVEL_ERROR, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

enum LogLevel : long
{
	LOG_LEVEL_NONE = 0x00,
	LOG_LEVEL_TRACE = 0x01 << 0,
	LOG_LEVEL_DEBUG = 0x01 << 1,
	LOG_LEVEL_INFO = 0x01 << 2,
	LOG_LEVEL_WARNING = 0x01 << 3,
	LOG_LEVEL_ERROR = 0x01 << 4,
	LOG_LEVEL_ALL = -1,
};

enum RetType : long
{
    RET_FAILURE = -1,
    RET_SUCCESS = 0,
    RET_NOTFOUND = 100,
    RET_SKIP = 100,
};

typedef RetType ret_t;
}

#endif // __LOGGER_H__