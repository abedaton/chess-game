#include "database.hpp"

static int myCallback(void* pUser, int argc, char** argv, char** columns);
static int callback(void* NotUsed, int argc, char** argv, char** columns);

Database::Database(){
	int rc = sqlite3_open("test.db", &this->db);
	if(rc != SQLITE_OK){
		std::cout << "Can't open database: %s\n", sqlite3_errmsg(this->db);
	} else {
		std::cout << "Open database successfully\n";
	}

	createTable();
}

void Database::createTable(){
	// create users
	char* zErrMsg = 0;

	std::string sql = "CREATE TABLE IF NOT EXISTS users (username TEXT NOT NULL UNIQUE,\
                                                    	password BIGINT,\
                                                    	email TEXT NOT NULL)";

	if (sqlite3_exec(this->db, sql.c_str(), callback, 0, &zErrMsg) == SQLITE_OK){
		std::cout << "New table created\n";
	} else {
		std::cout << "This table already exists !\n";
	}
}


void Database::addUser(std::string username, std::string password, std::string email){
	sqlite3_stmt* stmt;
	const char* pzTest;

	// Insert data item into users
	std::string sql = "INSERT INTO users (username, password, email) VALUES (?,?,?)";

	if (sqlite3_prepare(this->db, sql.c_str(), static_cast<int>(sql.size()), &stmt, &pzTest) == SQLITE_OK){
		// Hash password
		long unsigned int addpassword = hashPass(password);
		// Bind the value
		sqlite3_bind_text(stmt, 1, username.c_str(), static_cast<int>(username.size()), 0);
		sqlite3_bind_int64(stmt, 2, static_cast<long long int>(addpassword));
        sqlite3_bind_text(stmt, 3, email.c_str(), static_cast<int>(email.size()), 0);
		// Commit
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	} else {
        std::cout << "Error: " << sqlite3_errmsg(this->db) << std::endl;
    }
}

long unsigned Database::hashPass(std::string password){
	std::hash<std::string>hashFct;
	return hashFct(password);
}

bool Database::isUsernameFree(std::string username){
	std::string sql = "SELECT * FROM users WHERE username = '" + username + "'";
	return ! selectData(sql);
}

bool Database::isLoginOk(std::string username, std::string password){
	long long int tpassword = static_cast<long long int>(hashPass(password));
	
	std::string sql = "SELECT * FROM users WHERE username = '" + username + "' AND password = " + std::to_string(tpassword);
	return selectData(sql);
}

bool Database::selectData(std::string sql){
	char* zErrMsg = 0;
	int hasResult = 0;
	int rc = sqlite3_exec(this->db, sql.c_str(), this->myCallback, &hasResult, &zErrMsg);

	if (rc != SQLITE_OK) {
		std::cout << "Error on isLoginOk: " << sqlite3_errmsg(this->db) << std::endl;
		sqlite3_free(zErrMsg);
		return false;
	} else {
		if(!hasResult) {
			std::cout << "Wrong username or password\n";
			return false;
		} else{
			std::cout << __LINE__ << " Login is OK\n";
			return true;
		}
	}
}

void Database::update(std::string table, std::string colName, std::string username, std::string newValue){
	char* zErrMsg = 0;
	std::string sql = "UPDATE " + table + " SET " + colName + " = '" + newValue + "' WHERE username = '" + username + "';";
	std::cout << sql << std::endl;
	int rc = sqlite3_exec(this->db, sql.c_str(), this->callback, 0, &zErrMsg);
	if (rc != SQLITE_OK){
		std::cout << "Error on Update: " << sqlite3_errmsg(this->db) << std::endl;
		sqlite3_free(zErrMsg);
	}
}


int Database::myCallback(void* pUser, int argc, char** argv, char** columns){
	int *flag = static_cast<int*>(pUser);
    *flag = 1;
    return 0;
}

int Database::callback(void* NotUsed, int argc, char** argv, char** columns){
	int i;
	for (i = 0; i < argc; i++){
		printf("%s = %s\n", columns[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

sqlite3* Database::getdb (){
	return this->db;
}