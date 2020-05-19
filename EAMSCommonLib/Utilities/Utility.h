//Etra utility methods
#include "pch.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <sstream>

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

	static std::string toCamelCase(std::string data) {
		std::for_each(data.begin(), data.end(), [](char& c) {
			c = ::tolower(c);
			});
		data[0] = toupper(data[0]);
		return data;
	}

	static std::string toCamelCase(std::string data, char delimitter) {
		std::for_each(data.begin(), data.end(), [delimitter](char& ch) {
			static int last = delimitter;
			if (last == delimitter && ch != delimitter && ::isalpha(ch))
				ch = ::toupper(ch);
			else
				ch = ::tolower(ch);
			last = ch;
			if (ch == delimitter)
				ch = ' ';
			});
		data[0] = toupper(data[0]);
		return data;
	}

	static std::string getValueFromMap(std::map<std::string, std::string> map, std::string key) {
		auto pos = map.find(key);
		std::string str;
		if (pos == map.end()) {
			return str;
		}
		else {
			return pos->second;
		}
	}

	static std::vector<std::string> splitString(std::string str,char delimitter) {
		std::vector<std::string> result;
		std::stringstream s_stream(str); //create string stream from the string
		while (s_stream.good()) {
			std::string substr;
			std::getline(s_stream, substr, delimitter); //get first string delimited by comma
			result.push_back(substr);
		}
		return result;
	}
};