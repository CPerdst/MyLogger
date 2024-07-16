#include "LogFormater.h"

void MyLogger::LogFormater::setFormat(std::string _format)
{
	this->format = _format;
}

/*
%d {%Y-%M-%D %H:%M:%S} [%rms]%T%t%T%N%T%F%T[%p]%T%f:%l%T%m%n
%m 消息
%p 日志级别
%c 日志器名称
%d 日期时间，后面可跟一对括号指定时间格式，比如%d{%Y-%m-%d %H:%M:%S}，这里的格式字符与C语言strftime一致
%r 该日志器创建后的累计运行毫秒数
%f 文件名
%l 行号
%t 线程id
%F 协程id
%N 线程名称
%% 百分号
%T 制表符
%n 换行
*/

std::string MyLogger::LogFormater::initFormat(MyLogger::LogEvent _event)
{
	enum class STATE
	{
		NORMAL,
		FORMAT,
		DATE,
		DATEBEGIN,
		DATABEGINFORMAT,
		DATEEND
	};
	STATE state = STATE::NORMAL;
	std::string result;
	std::ostringstream s_stream;
	if (this->format.begin() == this->format.end()) {
		result = s_stream.str();
		return result;
	}
	for (auto ite = this->format.begin(); ite != this->format.end(); ite++) {
		if (state == STATE::FORMAT) {
			switch (*ite)
			{
			case 'f': {
				s_stream << _event.m_fileName;
				break;
			}
			case 'l': {
				s_stream << _event.m_lineNumber;
				break;
			}
			case 'T': {
				s_stream << "\t";
				break;
			}
			case 't': {
				std::hash<std::thread::id> hash_value;
				size_t value = hash_value(_event.m_threadId);
				s_stream << value;
				break;
			}
			case 'n': {
				s_stream << "\n";
				break;
			}
			case 'm': {
				std::string tmpString = _event.m_stringStream.str();
				s_stream << tmpString;
				break;
			}
			case 'p': {
				s_stream << _event.getLogLevel();
				break;
			}
			case 'r': {
				time_t now = time(0);
				s_stream << now - PROGRAM_RUNNING_CLOCK;
				break;
			}
			default:
				break;
			}
			state = STATE::NORMAL;
			if (*ite == 'd')
				state = STATE::DATE;
		}
		else if (state == STATE::NORMAL) {
			if (*ite == '%') {
				state = STATE::FORMAT;
				continue;
			}
			s_stream << *ite;
		}
		else if (state == STATE::DATE) {
			if (*ite == '{') {
				state = STATE::DATEBEGIN;
				continue;
			}
			s_stream << *ite;
		}
		else if (state == STATE::DATEBEGIN) {
			if (*ite == '%') {
				state = STATE::DATABEGINFORMAT;
				continue;
			}
			else if (*ite == '}') {
				state = STATE::NORMAL;
				continue;
			}
			s_stream << *ite;
		}
		else if (state == STATE::DATABEGINFORMAT) {
			switch (*ite)
			{
			case 'Y': {
				s_stream << _event.year;
				break;
			}
			case 'M': {
				s_stream << _event.mouth;
				break;
			}
			case 'D': {
				s_stream << _event.mouth;
				break;
			}
			case 'h': {
				s_stream << _event.hour;
				break;
			}
			case 'm': {
				s_stream << _event.minute;
				break;
			}
			case 's': {
				s_stream << _event.second;
				break;
			}
			default:
				break;
			}
			state = STATE::DATEBEGIN;
		}

	}
	result = s_stream.str();
	return result;
}
