#pragma once
#include <string>
#include <vector>
class Role
{
private:
	int roleId;
	std::string roleName;
	std::vector<std::string> privileges;
	
public:
	Role();
	std::string getRoleName();
	void setRoleName(std::string roleName);
	std::vector<std::string> getPrivileges();
	void setPrivileges(const std::vector<std::string> &privilege);
	int getRoleId();
	void setRoleId(int roleId);
};

