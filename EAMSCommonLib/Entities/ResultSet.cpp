#include "ResultSet.h"
ResultSet::ResultSet() {}
void  ResultSet::printTable()
{
	if (isToBePrint)
	{
		for (int i = 0; i < ColumnNames.size(); i++)
		{
			cout << left << setw(20) << setfill('-') << left << '+';
		}
		cout << "+" << endl;
		for (int i = 0; i < ColumnNames.size(); i++)
		{
			cout << setfill(' ') << '|' << setw(19) << ColumnNames[i] << setfill(' ');
		}
		cout << '|' << endl;
		for (int i = 0; i < ColumnNames.size(); i++)
		{
			cout << left << setw(20) << setfill('-') << left << '+';
		}
		cout << "+" << endl;
		for (int i = 0; i < results.size(); i++)
		{
			for (int j = 0; j < ColumnNames.size(); j++)
			{
				cout << setfill(' ') << '|' << left << setw(19) << results[i][j];
			}
			cout << '|' << endl;
		}
		for (int i = 0; i < ColumnNames.size(); i++)
		{
			cout << left << setw(20) << setfill('-') << left << '+';
		}
		cout << "+" << endl;

	}
}
