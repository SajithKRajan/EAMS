#pragma once
//Set and get methods 
#include <string>

class Attendance
{	
//Member functions
public:
	void SetId(int id);
	int GetId();
	void SetAttId(int attid);
	int GetAttId();
	void SetLocationId(int locationid);
	int GetLocationId();
	void SetCheckIn(std::string checkin);
	std::string GetCheckIn();
	void SetCheckOut(std::string checkout);
	std::string GetCheckOut();
	void SetTotalHrs(int totalhrs);
	int GetTotalHrs();
	
//Member variables

private:
	int m_nId;
	int m_nAttId;
	int m_nLocationId;
	std::string m_strCheckIn;
	std::string m_strCheckOut;
	int m_nTotalHrs;
	
};

