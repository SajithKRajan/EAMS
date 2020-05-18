#pragma once
#include <string>

class Absence
{
//Member functions
public:
	int GetAbsenceId();
	void SetAbsenceId(int absenceid);
	int GetId();
	void SetId(int id);
	std::string GetDate();
	void SetDate(std::string date);

//Member variable
private:
	int m_nAbsenceId;
	int m_nId;
	std::string m_strDate;
};


