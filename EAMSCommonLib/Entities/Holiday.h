#pragma once
#include<string>
class Holiday
{
public:
	int GetHolidayId();
	void SetHolidayId(int Id);
	int GetLocatioId();
	void SetLocationId(int Id);
	std::string GetDescription();
	void SetDescription(std::string Description);

//Member variables
private:
	int m_nHolidayId;
	int m_nLocationId;
	std::string m_strDescription;
	

	
};

