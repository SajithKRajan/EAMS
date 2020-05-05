#include "pch.h"
#include <string>
#include <iostream>

class Utility
{
public:
	static int parse_int(std::string value) {
		int int_val = 0;
		try
		{
			int int_val = std::stoi(value);
		}
		catch (std::invalid_argument const& e)
		{
			std::cout << "Bad input: Utility::parseInt thrown" << '\n';
		}
		catch (std::out_of_range const& e)
		{
			std::cout << "Integer overflow: Utility::parseInt thrown" << '\n';
		}
		return int_val;
	}

	static constexpr unsigned int str2int(const char* str, int h = 0)
	{
		return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
	}

};
