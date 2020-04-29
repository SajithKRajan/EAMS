#pragma once
#include <string>
class Absence
{
private:
	int absenceId;
	int id;
	std::string date;
public:
	Absence();
	int getAbsenceId();
	void setAbsenceId(int absenceid);
	int getId();
	void setId(int id);
	std::string getDate();
	void setDate(std::string date);
};


