#pragma once
#include <string>
class Location
{
private:
	int locationid;
	std::string locationName;
public:
	int getLocationId();
	void setLocationId(int locationid);
	std::string getName();
	void setName(std::string Name);
	
};


