#include "printResults.h"

using namespace std;
void PrintResults::Print(ResultSet* objResultSet)
{
	if (objResultSet->m_IsToBePrint)
	{
		if (objResultSet->m_szPrintType == "TABLE")
		{
			PrintTable(objResultSet);
		}
		else if(objResultSet->m_szPrintType == "MESSAGE")
		{
			cout << objResultSet->m_szMessage << endl;
		}
		/*else if (objResultSet->printType == "OBJECT")
		{
			printObject(objResultSet);
		}*/		
	}
}
void PrintResults::PrintTable(ResultSet* objResultSet)
{
	for (int i = 0; i < objResultSet->m_ColumnNames.size(); i++)
	{
		cout << left << setw(20) << setfill('-') << left << '+';
	}
	cout << "+" << endl;
	for (int i = 0; i < objResultSet->m_ColumnNames.size(); i++)
	{
		cout << setfill(' ') << '|' << setw(19) << objResultSet->m_ColumnNames[i] << setfill(' ');
	}
	cout << '|' << endl;
	for (int i = 0; i < objResultSet->m_ColumnNames.size(); i++)
	{
		cout << left << setw(20) << setfill('-') << left << '+';
	}
	cout << "+" << endl;
	for (int i = 0; i < objResultSet->m_resultData.size(); i++)
	{
		for (int j = 0; j < objResultSet->m_ColumnNames.size(); j++)
		{
			cout << setfill(' ') << '|' << left << setw(19) << objResultSet->m_resultData[i][j];
		}
		cout << '|' << endl;
	}
	for (int i = 0; i < objResultSet->m_ColumnNames.size(); i++)
	{
		cout << left << setw(20) << setfill('-') << left << '+';
	}
	cout << "+" << endl;
}
