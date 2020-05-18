#pragma once
#include <string>
#include <vector>
class Role
{
// Member functions
public:
	std::string getRoleName();
	void setRoleName(std::string roleName);
	std::vector<std::string> getPrivileges();
	void setPrivileges(const std::vector<std::string> &privilege);
	int getRoleId();
	void setRoleId(int roleId);

// Member variables
private:
	int m_nRoleId;
	std::string m_strRoleName;
	std::vector<std::string> m_Privileges;
};

