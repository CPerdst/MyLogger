#pragma once

#include "LogAppender.h"

namespace MyLogger {
	class LogFileAppender : public LogAppender
	{
	public:
		LogFileAppender(const char* path) {
			if (m_logFile.is_open())
				m_logFile.close();
			m_logFile.open(path, std::ofstream::app);
		};
		~LogFileAppender() {};

		void out(std::string logContent) override;

		std::ofstream m_logFile;
	};
};

