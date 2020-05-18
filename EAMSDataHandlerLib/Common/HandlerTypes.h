#pragma once
#include <string>
#include <algorithm>


class HandlerTypes {
public:
	enum Handler
	{ 
		EMPLOYEE, 
		ROLE, 
		LOCATION, 
		ATTENDANCE, 
		ABSENCE, 
		HOLIDAY 
	};

	static Handler EnumFromString(std::string Value) {

		std::string strdata[] = { "EMPLOYEE", "ROLE", "LOCATION", "ATTENDANCE", "ABSENCE", "HOLIDAY" };

		int i=0;
		for (std::string strResult : strdata) {
			if (strResult == Value) {
				return static_cast<Handler>(i);
			}
			i++;
		}
		return static_cast<Handler>(-1);
	}
};

