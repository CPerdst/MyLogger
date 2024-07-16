#include <chrono>
#include <iostream>
#include <map>
#include <vector>

class Operation {
public:
	Operation() {}
	~Operation() { std::cout << "Operation destructed" << std::endl; }
	virtual int getResult(int a, int b) = 0;
};

class OperationAdd : public Operation {
public:
	OperationAdd() {}
	~OperationAdd() { std::cout << "OperationAdd destructed" << std::endl; }
	int getResult(int a, int b) override {
		return a + b;
	}
};

class OperationMulti : public Operation {
public:
	OperationMulti() {}
	int getResult(int a, int b) override {
		return a * b;
	}
};

class OperationFactory {
public:
	static std::unique_ptr<Operation> createOperation(std::string operation) {
		if (strcmp(operation.c_str(), "+") == 0) {
			std::unique_ptr<Operation> oper = std::make_unique<OperationAdd>();
			return oper;
		}
		else if (strcmp(operation.c_str(), "*") == 0) {
			std::unique_ptr<Operation> oper = std::make_unique<OperationMulti>();
			return oper;
		}
	}
};

#include <sstream>
#include "Logger.h"
#include "LoggerWarp.h"

using namespace MyLogger;

void asd(MyLogger::LogEvent& e) {

}

#define __LOGGER__	logger
#define LOGERROR()	LOG_ERROR(__LOGGER__)
#define LOGINFO()	LOG_INFO(__LOGGER__)
#define LOGDEBUG()	LOG_DEBUG(__LOGGER__)

int main() {
	/*std::unique_ptr<Operation> other;
	{
		std::unique_ptr<Operation> oper = OperationFactory::createOperation("+");
		std::cout << oper->getResult(1, 2) << std::endl;
		other = std::move(oper);
	}
	std::cout << "out" << std::endl;*/

	//std::this_thread::sleep_for(std::chrono::seconds(3));
	MyLogger::LogFormater formater;
	formater.setFormat("[%p]%T[%d{%Y-%M-%D %h:%m:%s} %r] [%f:%l]: %m%n");
	MyLogger::LogAppender* appender = new MyLogger::LogConsoleAppender();
	MyLogger::Logger logger(formater, appender, MyLogger::LOG_LEVEL::INFO);

	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		LOGERROR() << "hello world!";
	}
	LOG_DEBUG(logger) << "hello";
}