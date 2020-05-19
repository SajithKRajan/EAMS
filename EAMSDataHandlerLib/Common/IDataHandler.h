#pragma once
#include "Entities/ResultSet.h";
#include "boost/any.hpp"
#include <Entities/Command.h>


class IDataHandler
{
//Member functions
public:
	virtual ResultSet* Execute(Command Cmd) const = 0;
	virtual ~IDataHandler() {};
};

