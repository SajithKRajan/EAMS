#include <vector>
#include <string>
#include <jdbc/mysql_driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>

class Database {

private:
	Database();

	Database(std::string, std::string,
		std::string, std::string, std::string);

protected:
	sql::mysql::MySQL_Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::ResultSet* res;
	sql::PreparedStatement* prep_stmt;

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

};
