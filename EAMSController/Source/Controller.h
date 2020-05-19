#pragma once
//Controls all command executions and result handling tasks

#include "Common/EAMSFactory.h"
#include "Entities/Command.h"
#include "InputReader.h"
#include "Entities/ResultSet.h"
#include "stdlib.h"
#include "PrintResults.h" 

class Controller
{
//Member function
public:
	void Start();

private:
	Employee* emp;

};

