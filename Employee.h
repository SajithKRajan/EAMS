#include <string>
class Employee
{
private:
	int id;
	std::string userName;
	std::string firstName;
	std::string lastName;
	int roleId;
public:
	Employee();
	int getId();
	void setId(int id);
	std::string getUserName();
	void setUserName(std::string userName);
	std::string getFirstName();
	void setFirstName(std::string firstName);
	std::string getLastName();
	void setLastName(std::string lastName);
	int getRoleId();
	void setRoleId(int roleId);
};
