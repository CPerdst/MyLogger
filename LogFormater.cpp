#include "LogFormater.h"

void MyLogger::LogFormater::setFormat(std::string _format)
{
	this->format = _format;
}

/*
%d {%Y-%M-%D %H:%M:%S} [%rms]%T%t%T%N%T%F%T[%p]%T%f:%l%T%m%n
%m ��Ϣ
%p ��־����
%c ��־������
%d ����ʱ�䣬����ɸ�һ������ָ��ʱ���ʽ������%d{%Y-%m-%d %H:%M:%S}������ĸ�ʽ�ַ���C����strftimeһ��
%r ����־����������ۼ����к�����
%f �ļ���
%l �к�
%t �߳�id
%F Э��id
%N �߳�����
%% �ٷֺ�
%T �Ʊ��
%n ����
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
