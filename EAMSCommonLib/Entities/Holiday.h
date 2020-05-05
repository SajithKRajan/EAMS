#pragma once
#include<string>
class Holiday
{
private:
	int holidayid;
	int locationid;
	std::string description;
	
public:
	int getHolidayId();
	void setHolidayId(int id);
	int getLocatioId();
	void setLocationId(int id);
	std::string getDescription();
	void setDescription(std::string description);
	
};

