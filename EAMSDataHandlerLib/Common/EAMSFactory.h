#pragma once
#include "HandlerTypes.h"
#include "EAMSMysqlDataHandler/EmployeeDataHandler.h"
#include "EAMSMysqlDataHandler/AbsenceDataHandler.h"
#include "EAMSMysqlDataHandler/RoleDataHandler.h"
#include "EAMSMysqlDataHandler/AttendanceDataHandler.h"
#include "EAMSMysqlDataHandler/LocationDataHandler.h"
#include "EAMSMysqlDataHandler/HolidayDataHandler.h"
#include "Common/IDataHandler.h"

class EAMSFactory
{
//Member functions
public:
	static EAMSFactory& Instance()
	{
		static EAMSFactory factory;
		return factory;
	}

	IDataHandler* getIDataHandler(HandlerTypes::Handler type ) 
	{
		switch (type) 
		{
			case HandlerTypes::EMPLOYEE:
				return new EmployeeDataHandler();
			case HandlerTypes::ABSENCE:
				return new AbsenceDataHandler();
			case HandlerTypes::ROLE:
				return new RoleDataHandler();
			case HandlerTypes::ATTENDANCE:
				return new AttendanceDataHandler();
			case HandlerTypes::LOCATION:
				return new LocationDataHandler();
			case HandlerTypes::HOLIDAY:
				return new HolidayDataHandler();
			default:
				break;
		}
		return NULL;
	}
};

