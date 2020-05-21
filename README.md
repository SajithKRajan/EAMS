# EAMS
Employee Attendance Management System CPP

## Motivation
The main motivation behind this project is to ease attendance management and to create a convenient and easy-to-use application for companies, to track the attendance of employee based on their work location. The system is based on a relational database with its management and reporting functions. We hope to provide a comfortable user experience for companies to manage the employee’s  attendance and employee’s details.

## Dependencies
1. Visual Studio 2019
2. Boost Library(Version 1_72_0)
2. MySQL Connector C++ 8.0
3. Database


## Build Setup
Make sure build it in Release x64.
Open EAMSController.sln and follow below steps to build

	Step 1: Right click on EAMSCommonLib->properties->C/C++->additional include directories.
		Include boost library in additional include directories.

	Step2: Right click on EAMSHandlerLib->Properties->C/C++->Additional Include Directories.
	       Include boost library in additional include directories.

	Step3: Right click on EAMSHandlerLib->Properties->Linker->Additional Libaries Directories
	       Include path of mysqlcppconn.lib in additional libaries directory.

	Step4: Right click on EAMSControllerLib->properties->C/C++->additional include directories.
	       Include boost library in additional include directories.

Build the Solution.


