#pragma once

#include <string>
#include <iostream>
#include "LogEvent.h"

/*
%d {%Y-%M-%D %H:%M:%S} [%rms]%T%t%T%N%T%F%T[%p]%T%f:%l%T%m%n
%m 消息
%p 日志级别
%c 日志器名称		(x)
%d 日期时间，后面可跟一对括号指定时间格式，比如%d{%Y-%m-%d %H:%M:%S}，这里的格式字符与C语言strftime一致
%r 该日志器创建后的累计运行毫秒数		(x)
%f 文件名
%l 行号
%t 线程id
%F 协程id			(x)
%N 线程名称			(x)
%% 百分号			(x)
%T 制表符			(x)
%n 换行
*/

namespace MyLogger {
	class LogFormater
	{
	public:
		LogFormater() : format("[%f:%l]: %m%n") {};
		LogFormater(std::string _format) : format(_format) {};
		LogFormater(LogFormater& other) {
			format = other.format;
		};
		LogFormater(LogFormater&& other) noexcept {
			format = std::move(other.format);
		}
		LogFormater& operator= (LogFormater& other) {
			format = other.format;
			return *this;
		};
		LogFormater& operator= (LogFormater&& other) noexcept {
			format = std::move(other.format);
			return *this;
		}
		void setFormat(std::string format);
		std::string initFormat(MyLogger::LogEvent _event);

		std::string format;
	};
}

