#include "pch.h"
#include "Attendance.h"

int Attendance::GetId()
{
	return this->m_nId;
}


void Attendance::SetId(int id)
{
	 this->m_nId=id;
}


int Attendance::GetAttId()
{
	return this->m_nAttId;
}


void Attendance::SetAttId(int attId)
{
	this->m_nAttId = attId;
}


int Attendance::GetLocationId()
{
	return this->m_nLocationId;
}


void Attendance::SetLocationId(int locationId)
{
	this->m_nLocationId = locationId;
}


std::string Attendance::GetCheckIn()
{
	return this->m_strCheckIn;
}


void Attendance::SetCheckIn(std::string checkin)
{
	this->m_strCheckIn = checkin;
}


std::string Attendance::GetCheckOut()
{
	return this->m_strCheckOut;
}


void Attendance::SetCheckOut(std::string checkout)
{
	this->m_strCheckOut = checkout;
}


int Attendance::GetTotalHrs()
{
	return this->m_nTotalHrs;
}


void Attendance::SetTotalHrs(int totalhrs)
{
	this->m_nTotalHrs = totalhrs;
}
