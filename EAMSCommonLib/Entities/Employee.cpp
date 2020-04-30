#include "pch.h"
#include "Employee.h"

int Employee::getId() {
	return this->id;
}
void Employee::setId(int id) {
	this->id = id;
}

std::string Employee::getUserName() {
	return this->userName;
}
void Employee::setUserName(std::string userName) {
	this->userName = userName;
}

std::string Employee::getFirstName() {
	return this->firstName;
}
void Employee::setFirstName(std::string firstName) {
	this->firstName = firstName;
}

std::string Employee::getLastName() {
	return this->lastName;
}
void Employee::setLastName(std::string lastName) {
	this->lastName = lastName;
}

int Employee::getRoleId() {
	return this->roleId;
}
void Employee::setRoleId(int roleId) {
	this->roleId = roleId;
}