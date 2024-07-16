#pragma once

#include <thread>
#include <sstream>
//#include <ctime>

#define FILENAME	__FILE__
#define LINENUM		__LINE__
#define THREADID	std::this_thread::get_id()
#define TIMESTEMP	time(0)
#define RUNTIME		

#define LEVEL_DEBUG	 MyLogger::LOG_LEVEL::DEBUG
#define LEVEL_INFO	 MyLogger::LOG_LEVEL::INFO
#define LEVEL_ERROR	 MyLogger::LOG_LEVEL::ERROR


#define EVENT(LEVEL)	MyLogger::LogEvent(LEVEL, FILENAME, LINENUM, THREADID, TIMESTEMP)

#define LOG_ERROR		EVENT(LEVEL_ERROR)
#define LOG_INFO		EVENT(LEVEL_INFO)
#define LOG_DEBUG		EVENT(LEVEL_DEBUG)

static time_t PROGRAM_RUNNING_CLOCK = time(0);

namespace MyLogger {
	enum class LOG_LEVEL
	{
		DEBUG,
		INFO,
		ERROR
	};

	class LogEvent {
	public:
		LogEvent() {};
		LogEvent(LOG_LEVEL level, const char* fileName, int lineNumber, std::thread::id threadId, time_t timeStemp);
		LogEvent(LogEvent&& other) noexcept : m_fileName(other.m_fileName), m_level(other.m_level), m_timeStemp(other.m_timeStemp), \
			m_lineNumber(other.m_lineNumber), year(other.year), mouth(other.mouth), day(other.day), hour(other.hour), \
			minute(other.minute), second(other.second)
		{
			m_stringStream = std::move(other.m_stringStream);
			m_threadId = std::move(other.m_threadId);
		}

		LogEvent& operator=(LogEvent&& other) noexcept {
			m_stringStream = std::move(other.m_stringStream);
			m_threadId = std::move(other.m_threadId);
			m_fileName = other.m_fileName;
			m_level = other.m_level;
			m_timeStemp = other.m_timeStemp;
			m_lineNumber = other.m_lineNumber;
			year = other.year;
			mouth = other.mouth;
			day = other.day;
			hour = other.hour;
			minute = other.minute;
			second = other.second;
			return *this;
		}

		std::string getLogLevel();

		std::ostringstream m_stringStream;
		const char* m_fileName;
		LOG_LEVEL m_level;
		std::thread::id m_threadId;
		time_t m_timeStemp;
		int m_lineNumber;
		int year;
		int mouth;
		int day;
		int hour;
		int minute;
		int second;
	};
};



