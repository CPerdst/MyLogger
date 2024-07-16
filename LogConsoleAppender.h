#pragma once

#include <iostream>
#include "LogAppender.h"

namespace MyLogger {
	class LogConsoleAppender : public LogAppender
	{
	public:
		LogConsoleAppender() {};
		~LogConsoleAppender() {};

		void out(std::string logContent) override;
	};
};

