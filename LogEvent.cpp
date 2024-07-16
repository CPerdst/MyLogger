#include "LogEvent.h"

MyLogger::LogEvent::LogEvent(LOG_LEVEL level, const char* fileName, int lineNumber, std::thread::id threadId, time_t timestemp)
{
	m_level = level;
	m_fileName = fileName;
	m_lineNumber = lineNumber;
	m_threadId = threadId;
	m_timeStemp = timestemp;
	std::shared_ptr<tm> s = std::make_shared<tm>();
	localtime_s(s.get(), &m_timeStemp);
	year = s->tm_year + 1900;
	mouth = s->tm_mon + 1;
	day = s->tm_wday;
	hour = s->tm_hour;
	minute = s->tm_min;
	second = s->tm_sec;
}

std::string MyLogger::LogEvent::getLogLevel()
{
	switch (m_level)
	{
	case LOG_LEVEL::DEBUG: {
		return "DEBUG";
	}
	case LOG_LEVEL::ERROR: {
		return "ERROR";
	}
	case LOG_LEVEL::INFO: {
		return "INFO";
	}
	default:
		return "";
	}
}
