#include "printResults.h"

using namespace std;
void PrintResults::print(ResultSet* objResultSet)
{
	if (objResultSet->isToBePrint)
	{
		if (objResultSet->printType == "TABLE")
		{
			printTable(objResultSet);
		}
		else if(objResultSet->printType == "MESSAGE")
		{
			cout << objResultSet->message << endl;
		}
		/*else if (objResultSet->printType == "OBJECT")
		{
			printObject(objResultSet);
		}*/

			
	}
}
void PrintResults::printTable(ResultSet* objResultSet)
{
	for (int i = 0; i < objResultSet->ColumnNames.size(); i++)
	{
		cout << left << setw(20) << setfill('-') << left << '+';
	}
	cout << "+" << endl;
	for (int i = 0; i < objResultSet->ColumnNames.size(); i++)
	{
		cout << setfill(' ') << '|' << setw(19) << objResultSet->ColumnNames[i] << setfill(' ');
	}
	cout << '|' << endl;
	for (int i = 0; i < objResultSet->ColumnNames.size(); i++)
	{
		cout << left << setw(20) << setfill('-') << left << '+';
	}
	cout << "+" << endl;
	for (int i = 0; i < objResultSet->resultData.size(); i++)
	{
		for (int j = 0; j < objResultSet->ColumnNames.size(); j++)
		{
			cout << setfill(' ') << '|' << left << setw(19) << objResultSet->resultData[i][j];
		}
		cout << '|' << endl;
	}
	for (int i = 0; i < objResultSet->ColumnNames.size(); i++)
	{
		cout << left << setw(20) << setfill('-') << left << '+';
	}
	cout << "+" << endl;
}
void PrintResults::printObject(ResultSet objResultSet)
{

}
