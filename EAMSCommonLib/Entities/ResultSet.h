#pragma once
#include <iostream>
#include <vector>
using namespace std;
class ResultSet
{
public:
	bool isSuccess;
	bool isToBePrint;
	bool isStopExecution;
	string printType;
	string message;
	vector<string> ColumnNames;
	vector<vector<string>> resultData;
};