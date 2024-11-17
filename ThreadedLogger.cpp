#include <ThreadedLogger.hpp>

namespace vp
{
/**
 * @brief Constructor for ThreadedLogger
 */
ThreadedLogger::ThreadedLogger()
{
	m_bStopThread = false;
	m_lMaxQueueSize = 4096;
	m_ulPollingSleepUs = 1000;
	m_pstQueueData = nullptr;
	m_atmUsedQueueCount.store(0);
	m_atmSeqence.store(0);
}

/**
 * @brief Destructor for ThreadedLogger
 */
ThreadedLogger::~ThreadedLogger()
{
}

/**
 * @brief Set the maximum queue size
 * @param lMaxQueueSize Maximum size of the queue
 */
auto ThreadedLogger::setMaxQueueSize(long lMaxQueueSize) -> void
{
	m_lMaxQueueSize = lMaxQueueSize;
}

auto ThreadedLogger::setPollingSleepUs(unsigned long ulPollingSleepUs) -> void
{
	m_ulPollingSleepUs = ulPollingSleepUs;
}

/**
 * @brief Initialize the logger
 * @return ret_t Return status
 */
auto ThreadedLogger::initialize() -> ret_t
{
	if (ALogger::initialize() != ret_t::RET_SUCCESS) {
		return ret_t::RET_FAILURE;
	}

	m_pstQueueData = new queue_data_t[m_lMaxQueueSize];
	for (long lIndex = 0; lIndex < m_lMaxQueueSize; lIndex++) {
		m_pstQueueData[lIndex].bLogEnabled = false;
	}
	m_logThread = std::thread(&ThreadedLogger::logThreadFunction, this);

	return ret_t::RET_SUCCESS;
}

/**
 * @brief Finalize the logger
 * @return  Return status
 */
auto ThreadedLogger::finalize() -> ret_t
{
	m_bStopThread = true;
	if (m_logThread.joinable()) {
		m_logThread.join();
	}
	if (ALogger::finalize() != ret_t::RET_SUCCESS) {
		return ret_t::RET_FAILURE;
	}

	return ret_t::RET_SUCCESS;
}

/**
 * @brief Write the log message
 * @param pzLogString Log message
 * @param nLogLength Length of the log message
 */
auto ThreadedLogger::writeLog(const char *pzLogString, int nLogLength) -> ret_t
{
	long lUsedQueueCount = m_atmUsedQueueCount.fetch_add(1);
	if (lUsedQueueCount >= m_lMaxQueueSize) {
		m_atmUsedQueueCount.fetch_sub(1);
		return ret_t::RET_SKIP;
	}

	long lSequence = getNextSequence();
	auto &stQueueData = m_pstQueueData[lSequence % m_lMaxQueueSize];
	stQueueData.strLogString = std::string(pzLogString, nLogLength);
	stQueueData.bLogEnabled = true;
	
	return ret_t::RET_SUCCESS;
}

/**
 * @brief Get the next sequence number
 * @return Next sequence number
 */
auto ThreadedLogger::getNextSequence() -> long
{
	return m_atmSeqence.fetch_add(1);
}

/**
 * @brief Log thread function
 */
auto ThreadedLogger::logThreadFunction() -> void
{
	long lSequence = 0;
	while (true) {
		long lCurrentSequence = m_atmSeqence.load();
		if (lSequence >= lCurrentSequence) {
			if (m_bStopThread) {
				lCurrentSequence = m_atmSeqence.load();
				if (lSequence >= lCurrentSequence) { 
					break;
				}
			}
			if (m_ulPollingSleepUs > 0) {
				std::this_thread::sleep_for(std::chrono::microseconds(m_ulPollingSleepUs));
			}
			continue;
		}
		for (; lSequence < lCurrentSequence; lSequence++) {
			auto &stQueueData = m_pstQueueData[lSequence % m_lMaxQueueSize];
			if (!stQueueData.bLogEnabled) {
				break;
			}
			write(stQueueData.strLogString.c_str(), stQueueData.strLogString.length());			
			stQueueData.bLogEnabled = false;
			m_atmUsedQueueCount.fetch_sub(1);
		}
	}
}
}
