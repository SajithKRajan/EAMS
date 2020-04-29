#include "pch.h"
#include <string>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
using namespace boost::gregorian;

class Utility
{
public:
	static int parse_int(std::string value) {
		int int_val=0;
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

	static boost::posix_time::ptime parse_date_time(std::string value) {
		boost::posix_time::ptime t1;
		try
		{
			boost::posix_time::ptime t1(boost::posix_time::time_from_string(value));
		}
		catch (std::exception* ex) {
			std::cout << "Bad input: Utility::parseDateTime thrown" << ex->what() << '\n';
		}
		return t1;
	}

	static date parse_date(std::string value) {
		return from_simple_string(value);
	}

	static boost::posix_time::time_duration get_time_diff(std::string value_1, std::string value_2) {
		boost::posix_time::ptime t1(boost::posix_time::time_from_string(value_1));
		boost::posix_time::ptime t2(boost::posix_time::time_from_string(value_2));
		return t2 - t1;
	}

	static std::string get_now_date_time() {
		boost::posix_time::ptime time_local = boost::posix_time::second_clock::local_time();
		return to_simple_string(time_local);
	}

	static std::string get_day_before(int days_before) {
		boost::posix_time::ptime time_local = boost::posix_time::second_clock::local_time();
		date d= time_local.date();
		d -= days(days_before);
		return to_simple_string(d);
	}

};