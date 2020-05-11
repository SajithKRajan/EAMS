
#include "Database.h"

void Database::SetDatabase(std::string DBname) {
	try {
		this->con->setSchema(DBname);
	}
	catch (sql::SQLException& e) {
		std::cout << "# ERR: " << e.what();
	}
}

void Database::Connect(std::string ip, std::string port,
	std::string username, std::string password) {
	try {
		this->driver = sql::mysql::get_mysql_driver_instance();
		this->con = driver->connect("tcp://" + ip + ":" + port + "", username, password);
	}
	catch (sql::SQLException& e) {
		std::cout << "# ERR: " << e.what();
	}
}

void Database::Close() {
	try {
		delete this->prep_stmt;
		delete this->con;
		delete this->res;
	}
	catch (sql::SQLException& e) {
		std::cout << "# ERR: " << e.what();
	}
}

void Database::Execute(std::string query) {
	try {
		this->stmt = this->con->createStatement();
		this->stmt->execute(query);
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
		this->stmt = this->con->createStatement();
		this->res = this->stmt->executeQuery(query);
		while (res->next()) {
			for (int a = 1; a != RowSize + 1; a++)
				tmp.push_back(res->getString(a));
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
		prep_stmt = con->prepareStatement(query);

		int b = 1;
		for (int a = 0; a < params.size(); a++) {
			if (!params[a].find("D:")) {
				prep_stmt->setDateTime(b, params[a].substr(2, params[a].length()));
			}
			if (!params[a].find("S:"))
				prep_stmt->setString(b, params[a].substr(2, params[a].length()));
			else if (!params[a].find("I:"))
				prep_stmt->setInt(b, atoi(params[a].substr(2, params[a].length()).c_str()));
			b++;
		}

		prep_stmt->execute();
	}
	catch (sql::SQLException& e) {
		std::cout << "# ERR: " << e.what();
	}
}

void Database::InsertS(std::string query, std::vector<std::string> params) {

	int tmp = 0; std::string tmp1;
	for (int i = 0; i < query.size(); i++)
		if (query[i] == ',') tmp++; tmp++;
	for (int i = 0; i != tmp; i++)
		if (tmp - 1 == i)  tmp1 += "? "; else tmp1 += "? ,";

	this->Execute_Query("INSERT INTO " + query + "VALUES (" + tmp1 + ")", params);

}

void Database::Insert(std::string query, std::vector<std::string> params) {
	std::cout << params.size();
	this->Execute_Query(query, params);
}

void Database::Update(std::string query, std::vector<std::string> params) {
	this->Execute_Query(query, params);
}

void Database::Delete(std::string query, std::vector<std::string> params) {
	this->Execute_Query(query, params);
}

std::vector<std::map<std::string, std::string>>
Database::Get(std::string query, std::vector<std::string> params) {
	std::vector<std::map<std::string, std::string>> result;
	std::map<std::string, std::string> result_item;
	try {
		prep_stmt = con->prepareStatement(query);
		int b = 1;
		for (int a = 0; a < params.size(); a++) {
			if (!params[a].find("S:"))
				prep_stmt->setString(b, params[a].substr(2, params[a].length()));
			else if (!params[a].find("I:"))
				prep_stmt->setInt(b, atoi(params[a].substr(2, params[a].length()).c_str()));
			b++;
		}
		try {
			this->res = prep_stmt->executeQuery();
			while (res->next()) {
				sql::ResultSetMetaData* column_meta_data = res->getMetaData();
				for (int a = 1; a != column_meta_data->getColumnCount() + 1; a++) {
					std::string key = column_meta_data->getColumnName(a);
					result_item.insert(std::pair<std::string, std::string>(key, res->getString(a)));
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

std::vector<std::map<std::string, std::string>>
Database::Get(std::string query) {
	std::vector<std::map<std::string, std::string>> result;
	std::map<std::string, std::string> result_item;
	try {
		prep_stmt = con->prepareStatement(query);
		try {
			this->res = prep_stmt->executeQuery();
			while (res->next()) {
				sql::ResultSetMetaData* column_meta_data = res->getMetaData();
				for (int a = 1; a != column_meta_data->getColumnCount() + 1; a++) {
					std::string key = column_meta_data->getColumnName(a);
					result_item.insert(std::pair<std::string, std::string>(key, res->getString(a)));
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
		this->driver = sql::mysql::get_mysql_driver_instance();
		this->con = driver->connect("tcp://127.0.0.1:3306", "root", "root");
		this->con->setSchema("EAMS");
	}
	catch (sql::SQLException& e) {
		std::cout << "# ERR: " << e.what();
	}
}

//Database::Database(std::string ip, std::string port,
//	std::string username, std::string password, std::string DBname) {
//	try {
//		this->driver = get_driver_instance();
//		this->con = driver->connect("tcp://" + ip + ":" + port + "", username, password);
//		this->con->setSchema(DBname);
//	}
//	catch (sql::SQLException& e) {
//		std::cout << "# ERR: " << e.what();
//	}
//}