#include "LogConsoleAppender.h"

void MyLogger::LogConsoleAppender::out(std::string logContent)
{
	if (logContent.empty())
		return;
	std::cout << logContent << std::flush;
}
