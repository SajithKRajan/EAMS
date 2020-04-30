#pragma once
#include <string>
#include <boost/any.hpp>

class ResultSet
{
private:
	bool isSuccess;
	bool isToBePrint;
	bool isStopExecution;
	std::string message;
	boost::any result;
public:
	template <typename T>
	T getResult() {
		return this->result;
	}
	template <typename T>
	void setResult(T res) {
		this->result = res;
	}
};

