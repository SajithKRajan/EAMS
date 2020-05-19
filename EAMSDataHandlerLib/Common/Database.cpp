
#include "Database.h"

//Setting a database
void Database::SetDatabase(std::string DBname) {
	try {
		this->m_Con->setSchema(DBname);
	}
	catch (sql::SQLException& e) {
		std::cout << "# ERR: " << e.what();
	}
}


//establish a connection with the database
void Database::Connect(std::string ip, std::string port,
	std::string username, std::string password) {
	try {
		this->m_Driver = sql::mysql::get_mysql_driver_instance();
		this->m_Con = m_Driver->connect("tcp://" + ip + ":" + port + "", username, password);
	}
	catch (sql::SQLException& e) {
		std::cout << "# ERR: " << e.what();
	}
}


//Close a connection
void Database::Close() {
	try {
		delete this->m_Prep_stmt;
		delete this->m_Con;
		delete this->m_Res;
	}
	catch (sql::SQLException& e) {
		std::cout << "# ERR: " << e.what();
	}
}


//Execute query
void Database::Execute(std::string query) {
	try {
		this->m_Stmt = this->m_Con->createStatement();
		this->m_Stmt->execute(query);
	}
	catch (sql::SQLException& e) {
		std::cout << "# ERR: " << e.what();
	}
}


std::vector <std::vector<std::string>>
Database::Execute(std::string query, int RowSize) {
	std::vector <std::string> tmp;
	std::vector <std::vector<std::string>> tmp2;
	try {
		this->m_Stmt = this->m_Con->createStatement();
		this->m_Res = this->m_Stmt->executeQuery(query);
		while (m_Res->next()) {
			for (int a = 1; a != RowSize + 1; a++)
				tmp.push_back(m_Res->getString(a));
			tmp2.push_back(tmp);
			tmp.clear();
		}
	}
	catch (sql::SQLException& e) {
		std::cout << "# ERR: " << e.what();
	}
	return tmp2;
}

void Database::Execute_Query(std::string query, std::vector<std::string> params) {
	try {
		m_Prep_stmt = m_Con->prepareStatement(query);

		int b = 1;
		for (int a = 0; a < params.size(); a++) {
			if (!params[a].find("D:")) {
				m_Prep_stmt->setDateTime(b, params[a].substr(2, params[a].length()));
			}
			if (!params[a].find("S:"))
				m_Prep_stmt->setString(b, params[a].substr(2, params[a].length()));
			else if (!params[a].find("I:"))
				m_Prep_stmt->setInt(b, atoi(params[a].substr(2, params[a].length()).c_str()));
			b++;
		}

		m_Prep_stmt->execute();
	}
	catch (sql::SQLException& e) {
		std::cout << "# ERR: " << e.what();
	}
}


//Insert record into database
void Database::InsertS(std::string query, std::vector<std::string> params) {

	int tmp = 0; std::string tmp1;
	for (int i = 0; i < query.size(); i++)
		if (query[i] == ',') tmp++; tmp++;
	for (int i = 0; i != tmp; i++)
		if (tmp - 1 == i)  tmp1 += "? "; else tmp1 += "? ,";

	this->Execute_Query("INSERT INTO " + query + "VALUES (" + tmp1 + ")", params);

}


void Database::Insert(std::string query, std::vector<std::string> params) {
	this->Execute_Query(query, params);
}


//Update record into database
void Database::Update(std::string query, std::vector<std::string> params) {
	this->Execute_Query(query, params);
}


//Delete record from database
void Database::Delete(std::string query, std::vector<std::string> params) {
	this->Execute_Query(query, params);
}


//Read record from database
std::vector<std::vector<std::string>>
Database::Get(std::string query, std::vector<std::string> params) {
	std::vector < std::vector<std::string>> result;
	std::vector<std::string> result_item;
	try {
		m_Prep_stmt = m_Con->prepareStatement(query);
		int b = 1;
		for (int a = 0; a < params.size(); a++) {
			if (!params[a].find("S:"))
				m_Prep_stmt->setString(b, params[a].substr(2, params[a].length()));
			else if (!params[a].find("I:"))
				m_Prep_stmt->setInt(b, atoi(params[a].substr(2, params[a].length()).c_str()));
			b++;
		}
		try {
			this->m_Res = m_Prep_stmt->executeQuery();
			while (m_Res->next()) {
				sql::ResultSetMetaData* column_meta_data = m_Res->getMetaData();
				for (int a = 1; a != column_meta_data->getColumnCount() + 1; a++) {
					std::string key = column_meta_data->getColumnName(a);
					result_item.push_back(m_Res->getString(a));
				}
				result.push_back(result_item);
				result_item.clear();
			}
		}
		catch (sql::SQLException& e) {
			std::cout << "# ERR: " << e.what();
		}
	}
	catch (sql::SQLException& e) {
		std::cout << "# ERR: " << e.what();
	}
	return result;
}

std::vector<std::vector<std::string>>
Database::Get(std::string query) {
	std::vector<std::vector<std::string>> result;
	std::vector<std::string> result_item;
	try {
		m_Prep_stmt = m_Con->prepareStatement(query);
		try {
			this->m_Res = m_Prep_stmt->executeQuery();
			while (m_Res->next()) {
				sql::ResultSetMetaData* column_meta_data = m_Res->getMetaData();
				for (int a = 1; a != column_meta_data->getColumnCount() + 1; a++) {
					std::string key = column_meta_data->getColumnName(a);
					result_item.push_back(m_Res->getString(a));
				}
				result.push_back(result_item);
				result_item.clear();
			}
		}
		catch (sql::SQLException& e) {
			std::cout << "# ERR: " << e.what();
		}
	}
	catch (sql::SQLException& e) {
		std::cout << "# ERR: " << e.what();
	}
	return result;
}

Database::Database() {
	try {
		this->m_Driver = sql::mysql::get_mysql_driver_instance();
		this->m_Con = m_Driver->connect("tcp://127.0.0.1:3306", "root", "root");
		this->m_Con->setSchema("eams2");
	}
	catch (sql::SQLException& e) {
		std::cout << "# ERR: " << e.what();
	}
}
