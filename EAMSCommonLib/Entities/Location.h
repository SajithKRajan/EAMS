#pragma once
//Set and get methods 
#include <string>
class Location
{
//Member functions
public:
	int getLocationId();
	void setLocationId(int LocationId);
	std::string getName();
	void setName(std::string Name);

//Member variables
private:
	int m_nLocationId;
	std::string m_strLocationName;
};


