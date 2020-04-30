#include "pch.h"
#include "Absence.h"

int Absence::getAbsenceId()
{
	return this->absenceId;
}

void Absence::setAbsenceId(int absenceId)
{
	this->absenceId = absenceId;
}

int Absence::getId()
{
	return this->id;
}

void Absence::setId(int id)
{
	this->id = id;
}

std::string Absence::getDate()
{
	return this->date;
}

void Absence::setDate(std::string date)
{
	this->date = date;
}
