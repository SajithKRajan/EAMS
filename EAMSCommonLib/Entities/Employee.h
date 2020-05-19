//Set and get methods 
#include <string>

class Employee
{
//Member functions
public:
	void SetId(int id);
	int GetId();
	void SetUserName(std::string UserName);
	std::string GetUserName();
	void SetFirstName(std::string FirstName);
	std::string GetFirstName();
	void SetLastName(std::string LastName);
	std::string GetLastName();
	void SetRoleId(int RoleId);
	int GetRoleId();

//Member variables
private:
	int m_nId;
	std::string m_strUserName;
	std::string m_strFirstName;
	std::string m_strLastName;
	int m_nRoleId;
};
