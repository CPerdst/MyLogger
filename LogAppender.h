#pragma once

#include <string>
#include <fstream>

namespace MyLogger {
	class LogAppender
	{
	public:
		LogAppender() {};
		virtual ~LogAppender() {};
		virtual void out(std::string logContent) = 0;
	};
};

