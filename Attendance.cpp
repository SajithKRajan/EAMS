#include "pch.h"
#include "Attendance.h"

Attendance::Attendance()
{
}

int Attendance::getId()
{
	return this->id;
}

void Attendance::setId(int id)
{
	 this->id=id;
}

int Attendance::getAttId()
{
	return this->attid;
}

void Attendance::setAttId(int attId)
{
	this->attid = attId;
}

int Attendance::getLocationId()
{
	return this->locationid;
}

void Attendance::setLocationId(int locationId)
{
	this->locationid = locationId;
}

std::string Attendance::getCheckIN()
{
	return this->checkin;
}

void Attendance::setCheckIN(std::string checkin)
{
	this->checkin = checkin;
}

std::string Attendance::getCheckOUT()
{
	return this->checkout;
}

void Attendance::setCheckOUT(std::string checkout)
{
	this->checkout = checkout;
}

int Attendance::getTotalHrs()
{
	return this->totalhrs;
}

void Attendance::setTotalHrs(int totalhrs)
{
	this->totalhrs = totalhrs;
}
