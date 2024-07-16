#pragma once

#include <string>
#include <iostream>
#include "LogEvent.h"

/*
%d {%Y-%M-%D %H:%M:%S} [%rms]%T%t%T%N%T%F%T[%p]%T%f:%l%T%m%n
%m ��Ϣ
%p ��־����
%c ��־������		(x)
%d ����ʱ�䣬����ɸ�һ������ָ��ʱ���ʽ������%d{%Y-%m-%d %H:%M:%S}������ĸ�ʽ�ַ���C����strftimeһ��
%r ����־����������ۼ����к�����		(x)
%f �ļ���
%l �к�
%t �߳�id
%F Э��id			(x)
%N �߳�����			(x)
%% �ٷֺ�			(x)
%T �Ʊ��			(x)
%n ����
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

