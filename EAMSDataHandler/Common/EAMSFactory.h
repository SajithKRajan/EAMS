#pragma once
#include "HandlerTypes.h"
#include "EmployeeDataHandler.h"
#include "AbsenceDataHandler.h"
#include "RoleDataHandler.h"
#include "AttendanceDataHandler.h"
#include "LocationDataHandler.h"
#include "HolidayDataHandler.h"
#include <IDataHandler.h>

class EAMSFactory
{
public:
	static EAMSFactory& Instance()
	{
		static EAMSFactory factory;
		return factory;
	}

	IDataHandler* getIDataHandler(HandlerTypes type ) {
		switch (type) {
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
		}
		return NULL;
	}
};

