#pragma once
#include <vector>
#include <iomanip>
#include "Entities/ResultSet.h"
class PrintResults
{
public:
	void Print(ResultSet* objResultSet);
	void PrintTable(ResultSet* objResultSet);
	//void PrintObject(ResultSet objResultSet);
};

