#include "pch.h"
#include "Employee.h"

int Employee::GetId() {
	return this->m_nId;
}
void Employee::SetId(int Id) {
	this->m_nId = Id;
}

std::string Employee::GetUserName() {
	return this->m_strUserName;
}
void Employee::SetUserName(std::string UserName) {
	this->m_strUserName = UserName;
}

std::string Employee::GetFirstName() {
	return this->m_strFirstName;
}
void Employee::SetFirstName(std::string FirstName) {
	this->m_strFirstName = FirstName;
}

std::string Employee::GetLastName() {
	return this->m_strLastName;
}
void Employee::SetLastName(std::string LastName) {
	this->m_strLastName = LastName;
}

int Employee::GetRoleId() {
	return this->m_nRoleId;
}
void Employee::SetRoleId(int RoleId) {
	this->m_nRoleId = RoleId;
}