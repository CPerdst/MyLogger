#include "LogFileAppender.h"

void MyLogger::LogFileAppender::out(std::string logContent)
{
	if (logContent.empty())
		return;
	m_logFile << logContent << std::flush;
}
