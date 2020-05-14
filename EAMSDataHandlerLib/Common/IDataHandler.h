#pragma once
#include "Entities/ResultSet.h";
#include "boost/any.hpp"
#include <Entities/Command.h>


class IDataHandler
{
public:
	virtual ResultSet* execute(Command cmd) const = 0;
	virtual ~IDataHandler() {};
};

