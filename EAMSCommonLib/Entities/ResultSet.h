#pragma once
#include <iostream>
#include <vector>
using namespace std;
class ResultSet
{
//Member variables
public:
	bool m_IsSuccess;
	bool m_IsToBePrint;
	bool m_IsStopExecution;
	std::string m_szPrintType;
	std::string m_szMessage;
	vector<std::string> m_ColumnNames;
	vector<vector<std::string>> m_resultData;
};