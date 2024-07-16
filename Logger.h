#pragma once

#include <string>
#include <memory>
#include <queue>
#include <vector>
#include "LogEvent.h"
#include "LogConsoleAppender.h"
#include "LogFileAppender.h"
#include "LogFormater.h"

namespace MyLogger {
	class Logger
	{
	public:
		Logger() :m_level(LOG_LEVEL::DEBUG), m_loggerName("root"), m_logFormater(LogFormater()) {}
		Logger(LogFormater formater, LogAppender* appender, LOG_LEVEL level) : m_logFormater(formater), m_level(level) {
			m_vectorLogAppender.reserve(10);
			m_vectorLogAppender.push_back(appender);
		};
		Logger(Logger& other) {
			m_level = other.m_level;
			m_logFormater = other.m_logFormater;
			m_loggerName = other.m_loggerName;
			m_vectorLogAppender = other.m_vectorLogAppender;
		};
		Logger(Logger&& other) noexcept {
			m_level = std::move(m_level);
			m_logFormater = std::move(m_logFormater);
			m_loggerName = std::move(m_loggerName);
			m_vectorLogAppender = std::move(other.m_vectorLogAppender);
		}
		Logger& operator=(Logger& other) {
			m_level = other.m_level;
			m_loggerName = other.m_loggerName;
			m_logFormater = other.m_logFormater;
			m_vectorLogAppender = other.m_vectorLogAppender;
			return *this;
		};
		Logger& operator=(Logger&& other) noexcept {
			m_level = other.m_level;
			m_loggerName = std::move(other.m_loggerName);
			m_logFormater = std::move(other.m_logFormater);
			m_vectorLogAppender = std::move(other.m_vectorLogAppender);
			return *this;
		};
		LOG_LEVEL getLevel() { return m_level; };
		LogFormater& getLogFormater() { return m_logFormater; };
		std::vector<LogAppender*>& getVec() {
			return m_vectorLogAppender;
		}
	private:
		LOG_LEVEL m_level;
		std::string	m_loggerName;
		LogFormater m_logFormater;
		std::vector<LogAppender*> m_vectorLogAppender;
	};
}