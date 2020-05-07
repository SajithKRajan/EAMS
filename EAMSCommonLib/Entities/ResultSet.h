#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
class ResultSet
{
private:
	bool isSuccess;
	bool isToBePrint = true;
	bool isStopExecution;
	//std::string message;
	//boost::any result;
	vector<string> ColumnNames = { "EMPLOYEE_ID","USERNAME","PASSWORD","ROLE_NAME" };
	vector<vector<string>> results{ {"1","jeslin","password1","employee"},{"2","jinu","password2","employee"},{"3","joe","password3","Admin"} };
public:
	ResultSet();
	void printTable();

};

