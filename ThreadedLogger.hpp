#ifndef __THREADED_LOGGER_HPP__
#define __THREADED_LOGGER_HPP__

#include <thread>
#include <atomic>
#include <ALogger.hpp>

namespace vp
{
/**
 * @brief Threaded logger class
 */
class ThreadedLogger : public ALogger
{
private:
	typedef struct
	{
		bool bLogEnabled;
		std::string strLogString;
	} queue_data_t;

public:
	ThreadedLogger();
	virtual ~ThreadedLogger();
	virtual auto setMaxQueueSize(long lMaxQueueSize) -> void;
	virtual auto setPollingSleepUs(unsigned long ulPollingSleepUs) -> void;
	virtual auto initialize() -> ret_t;
	virtual auto finalize() -> ret_t;
protected:
	virtual auto writeLog(const char *pzLogString, int nLogLength) -> ret_t;
private:
	virtual auto getNextSequence() -> long;
	virtual auto logThreadFunction() -> void;

private:
	bool m_bStopThread;
	long m_lMaxQueueSize;
	unsigned long m_ulPollingSleepUs;
	queue_data_t *m_pstQueueData;
	std::atomic<long> m_atmUsedQueueCount;
	std::atomic<long> m_atmSeqence;
    std::thread m_logThread;
};
}

#endif // __THREADED_LOGGER_HPP__