#pragma once
#include "Enities/ResultSet.h";
#include "boost/any.hpp"
#include <Enities/Command.h>


class IDataHandler
{
public:
	virtual ResultSet execute(Command* cmd) const = 0;
	virtual ~IDataHandler() {};
};

