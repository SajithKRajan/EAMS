#pragma once
#include <string>
#include <algorithm>


class HandlerTypes {
public:
	enum Handler{ EMPLOYEE, ROLE, LOCATION, ATTENDANCE, ABSENCE, HOLIDAY };

	static Handler enumFromString(std::string value) {
		std::string data[] = { "EMPLOYEE", "ROLE", "LOCATION", "ATTENDANCE", "ABSENCE", "HOLIDAY" };
		int i=0;
		for (std::string str : data) {
			if (str == value) {
				return static_cast<Handler>(i);
			}
			i++;
		}
		return static_cast<Handler>(-1);
	}
};

