#pragma once
#include <string>

template <class T>
class ResultSet
{
private:
	bool isSuccess;
	bool isToBePrint;
	bool isStopExecution;
	std::string message;
	T result;
public:

};

