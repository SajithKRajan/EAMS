//Methods to connect,create,read,update,delete from database
#include <vector>
#include <string>
#include <jdbc/mysql_driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>

class Database {
//Member functions
public:
	static Database& Instance()
	{
		static Database database;
		return database;
	}

	void Execute_Query(std::string,
						std::vector<std::string>);

	void Execute(std::string);

	std::vector<std::vector<std::string>>
		Execute(std::string, int);

	void Close();

	void Connect(std::string, std::string,
				 std::string, std::string);

	void SetDatabase(std::string);

	void Insert(std::string, std::vector<std::string>);

	void InsertS(std::string, std::vector<std::string>);

	std::vector<std::vector<std::string>>
		Get(std::string, std::vector<std::string>);

	std::vector<std::vector<std::string>>
		Get(std::string);

	void Update(std::string, std::vector<std::string>);

	void Delete(std::string, std::vector<std::string>);

private:
	Database();

	Database(std::string, std::string,
		std::string, std::string, std::string);

//Member variables
protected:
	sql::mysql::MySQL_Driver* m_Driver;
	sql::Connection* m_Con;
	sql::Statement* m_Stmt;
	sql::ResultSet* m_Res;
	sql::PreparedStatement* m_Prep_stmt;



};
