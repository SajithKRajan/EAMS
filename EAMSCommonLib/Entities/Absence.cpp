#include "pch.h"
#include "Absence.h"


void Absence::SetAbsenceId(int absenceId)
{
	this->m_nAbsenceId = absenceId;
}


int Absence::GetAbsenceId()
{
	return this->m_nAbsenceId;
}


void Absence::SetId(int id)
{
	this->m_nId = id;
}


int Absence::GetId()
{
	return this->m_nId;
}


void Absence::SetDate(std::string date)
{
	this->m_strDate = date;
}


std::string Absence::GetDate()
{
	return this->m_strDate;
}

