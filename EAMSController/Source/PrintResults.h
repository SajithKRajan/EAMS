#pragma once
#include <vector>
#include <iomanip>
#include "Entities/ResultSet.h"
class PrintResults
{
public:
	void print(ResultSet objResultSet);
	void printTable(ResultSet objResultSet);
	void printObject(ResultSet objResultSet);
};

