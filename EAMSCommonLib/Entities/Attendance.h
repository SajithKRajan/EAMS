#pragma once
#include <string>
class Attendance
{
private:
	int id;
	int attid;
	int locationid;
	std::string checkin;
	std::string checkout;
	int totalhrs;
	
public:
	int getId();
	void setId(int id);
	int getAttId();
	void setAttId(int attid);
	int getLocationId();
	void setLocationId(int locationid);
	std::string getCheckIN();
	void setCheckIN(std::string checkin);
	std::string getCheckOUT();
	void setCheckOUT(std::string checkout);
	int getTotalHrs();
	void setTotalHrs(int totalhrs);
	
};

