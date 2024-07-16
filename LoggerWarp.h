#pragma once

#include "Logger.h"
#include "LogEvent.h"

#define LOG_PROGRAM(LOGGER, LEVEL)	\
	if(LEVEL >= LOGGER.getLevel()) \
		MyLogger::LoggerWarp(LOGGER, EVENT(LEVEL)).Oss()

#define LOG_INFO(LOGGER)	LOG_PROGRAM(LOGGER, LEVEL_INFO)
#define LOG_ERROR(LOGGER)	LOG_PROGRAM(LOGGER, LEVEL_ERROR)
#define LOG_DEBUG(LOGGER)	LOG_PROGRAM(LOGGER, LEVEL_DEBUG)

namespace MyLogger {
	class LoggerWarp
	{
	public:
		LoggerWarp(Logger& logger, LogEvent&& _event) {
			m_logger = logger;
			m_event = std::forward<LogEvent>(_event);
		};
		~LoggerWarp() {
			std::vector<LogAppender*>& tmp = m_logger.getVec();
			for (auto appender : tmp) {
				std::string res = m_logger.getLogFormater().initFormat(std::move(m_event));
				appender->out(res);
			}
		};
		std::ostringstream& Oss() { return m_event.m_stringStream; };
		Logger m_logger;
		LogEvent m_event;
	};
}



