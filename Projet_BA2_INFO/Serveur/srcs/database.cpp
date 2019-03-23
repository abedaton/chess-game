#include "../includes/database.hpp"


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

	std::string sql = "CREATE TABLE IF NOT EXISTS users (username TEXT NOT NULL UNIQUE, password BIGINT, email TEXT NOT NULL, socket INT, loggedIn BOOLEAN)";

	if (sqlite3_exec(this->db, sql.c_str(), callback, 0, &zErrMsg) == SQLITE_OK){
		//std::cout << "New table created\n";
	} else {
		std::cout << "This table already exists !\n";
	}
	zErrMsg = 0;
	sql = "CREATE TABLE IF NOT EXISTS friendList(user1 TEXT, user2 TEXT, relation TEXT);";
	if (sqlite3_exec(this->db, sql.c_str(), callback, 0, &zErrMsg) == SQLITE_OK){
		//std::cout << "New table created\n";
	} else {
		std::cout << "This table already exists !\n";
	}
}


// Register
void Database::addUser(std::string username, std::string password, std::string email, int socket){
	sqlite3_stmt* stmt;
	const char* pzTest;

	// Insert data item into users
	std::string sql = "INSERT INTO users (username, password, email, socket, loggedIn) VALUES (?,?,?,?,1)";

	if (sqlite3_prepare(this->db, sql.c_str(), static_cast<int>(sql.size()), &stmt, &pzTest) == SQLITE_OK){
		// Hash password
		long unsigned int addpassword = hashPass(password);
		// Bind the value
		sqlite3_bind_text(stmt, 1, username.c_str(), static_cast<int>(username.size()), 0);
		sqlite3_bind_int64(stmt, 2, static_cast<long long int>(addpassword));
        sqlite3_bind_text(stmt, 3, email.c_str(), static_cast<int>(email.size()), 0);
		sqlite3_bind_int(stmt, 4, static_cast<int>(socket));
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
	char* zErrMsg = 0;
	int hasResult = 0;
	std::string sql = "SELECT loggedIn, socket FROM users WHERE username = '" + username + "';";
	int rc = sqlite3_exec(this->db, sql.c_str(), this->callbackDisc, &hasResult, &zErrMsg);
	if (rc != SQLITE_OK) {
		std::cout << "Error isLoginOk: " << sqlite3_errmsg(this->db) << std::endl;
		sqlite3_free(zErrMsg);
	}
	sql = "SELECT * FROM users WHERE username = '" + username + "' AND password = '" + std::to_string(tpassword) + "';";
	return selectData(sql);
}

bool Database::selectData(std::string sql){
	char* zErrMsg = 0;
	int hasResult = 0;
	int rc = sqlite3_exec(this->db, sql.c_str(), this->myCallback, &hasResult, &zErrMsg);

	if (rc != SQLITE_OK) {
		std::cout << "Error selectData: " << sqlite3_errmsg(this->db) << std::endl;
		sqlite3_free(zErrMsg);
		return false;
	} else {
		if(!hasResult) {
			return false;
		} else{
			return true;
		}
	}
}

void Database::updateInfo(std::string table, std::string colName, std::string username, std::string newValue){
	char* zErrMsg = 0;
	std::string sql = "UPDATE '" + table + "' SET '" + colName + "' = '" + newValue + "' WHERE username = '" + username + "';";
	std::cout << sql << std::endl;
	int rc = sqlite3_exec(this->db, sql.c_str(), this->callback, 0, &zErrMsg);
	if (rc != SQLITE_OK){
		std::cout << "Error on Update: " << sqlite3_errmsg(this->db) << std::endl;
		sqlite3_free(zErrMsg);
	}
}



void Database::createInfoTable(std::string username){
	const char* pzTest;
	sqlite3_stmt* stmt;
	std::string sql = "CREATE TABLE IF NOT EXISTS '" + username + "' (nbrGames UNSIGNED BIG INT, win UNSIGNED INT, elo UNSIGNED INT);";

	char* zErrMsg = 0;
	if (sqlite3_exec(this->db, sql.c_str(), callback, 0, &zErrMsg) == SQLITE_OK){
		std::cout << "New table " + username + " created\n";
	}

	sql = "INSERT INTO '" + username + "' (nbrGames, win, elo) VALUES (0, 0, 1000);";
	if (sqlite3_prepare(this->db, sql.c_str(), static_cast<int>(sql.size()), &stmt, &pzTest) == SQLITE_OK){
		sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	} else {
        std::cout << "Error: " << sqlite3_errmsg(this->db) << std::endl;
    }
}

void Database::updateUserLog(std::string username, int value){
	char* zErrMsg = 0;
	std::string sql = "UPDATE users SET  socket= '" + std::to_string(value) + "', loggedIn = '1' WHERE username = '" + username + "';";
	int rc = sqlite3_exec(this->db, sql.c_str(), this->callback, 0, &zErrMsg);
	if (rc != SQLITE_OK){
		std::cout << "Error on Update: " << sqlite3_errmsg(this->db) << std::endl;
		sqlite3_free(zErrMsg);
	}
}

void Database::updateUserDisc(std::string username){
	char* zErrMsg = 0;
	std::string sql = "UPDATE users SET loggedIn = '0', socket = '-1' WHERE username = '" + username + "';";
	int rc = sqlite3_exec(this->db, sql.c_str(), this->callback, 0, &zErrMsg);
	if (rc != SQLITE_OK){
		std::cout << "Error on Update: " << sqlite3_errmsg(this->db) << std::endl;
		sqlite3_free(zErrMsg);
	}
}

void Database::updateWin(std::string username, std::string rival, bool win){
	// Systeme d'Elo par Arpad Elo 
	std::cout << std::fixed;
	std::cout << std::setprecision(5);
	int elo1 = getInt(username, "elo");
	int elo2 = getInt(rival, "elo");
	int nbrGames = getInt(username, "nbrGames"); 
	std::cout << "Elo1 = " << elo1 << " and Elo2 = " << elo2 << std::endl;
	int D = elo2 - elo1;
	if (D > 400){
		D = 400;
	}

	double winProb = (-D)/400;
	winProb = std::pow(10, winProb);
	winProb = 1/(winProb++);
	
	std::cout << "winProb = " << winProb << " D = " << D << std::endl;
	int K;
	if (nbrGames <= 30){
		K = 40;
	} else if (elo1 < 2400){
		K = 20;
	} else {
		K = 10;
	}

	int W = static_cast<int>(win);
	std::cout << "W = " << W << " and K = " << K << std::endl;
	int newElo = std::round(elo1 + K * (W - winProb));
	std::cout << "newELo for " << username << " = " << newElo << std::endl << std::endl;
	char* zErrMsg = 0;
	std::string sql = "UPDATE '" + username + "'SET nbrGames = 'nbrGames+1', elo = '" + std::to_string(newElo) + "'";
	if (win)
		sql += ", win = win+1";
	sql += ";";
	int rc = sqlite3_exec(this->db, sql.c_str(), this->callback, 0, &zErrMsg);
	if (rc != SQLITE_OK){
		std::cout << "Error on UpdateWin: " << sqlite3_errmsg(this->db) << std::endl;
		sqlite3_free(zErrMsg);
	}
}


char* Database::getValue(std::string table, std::string column){
	char* zErrMsg = 0;
	std::string sql = "SELECT " + column + " FROM '" + table + "';";
	std::cout << sql << std::endl;
	char** var;
	int rc = sqlite3_exec(this->db, sql.c_str(), callbackGetter, var, &zErrMsg);;
	if (rc != SQLITE_OK){
		std::cout << "Error on getValue: " << sqlite3_errmsg(this->db) << std::endl;
		sqlite3_free(zErrMsg);
	}
	return *var;
}


int Database::getInt(std::string table, std::string column){
	char* val = getValue(table, column);
	int tmp = atoi(val);
	return atoi(val);
}

void Database::deleteUser(std::string username){
	char* zErrMsg = 0;
	std::string sql = "DROP TABLE " + username + ";";
	int rc = sqlite3_exec(this->db, sql.c_str(), callback, 0, &zErrMsg);
	if (rc != SQLITE_OK){
		std::cout << "Error on drop table: " << sqlite3_errmsg(this->db) << std::endl;
		sqlite3_free(zErrMsg);
	}

	sql = "DELETE FROM users WHERE username = '" + username + "';";
	rc = sqlite3_exec(this->db, sql.c_str(), callback, 0, &zErrMsg);
	if (rc != SQLITE_OK){
		std::cout << "Error on drop table: " << sqlite3_errmsg(this->db) << std::endl;
		sqlite3_free(zErrMsg);
	}
}


void Database::updateAllSockets(){
	char* zErrMsg = 0;
	std::string sql = "UPDATE users SET socket = '-1', loggedIn = '0';";
	int rc = sqlite3_exec(this->db, sql.c_str(), callback, 0, &zErrMsg);
	if (rc != SQLITE_OK){
		std::cout << "Error on updateAllSockets: " << sqlite3_errmsg(this->db) << std::endl;
		sqlite3_free(zErrMsg);
	}
}

Database::~Database(){
	this->updateAllSockets();
	std::cout << "All sockets set to -1" << std::endl;
}

void Database::sendFriendRequest(std::string friend1, std::string friend2){
	char* zErrMsg = 0;
	std::string sql = "INSER INTO friendList(user1, user2, relation) VALUES ('" + friend1 + "', '" + friend2 + "', waiting);";
	int rc = sqlite3_exec(this->db, sql.c_str(), callback, 0, &zErrMsg);
	if (rc != SQLITE_OK){
		std::cout << "Error on sendFriendRequest: " << sqlite3_errmsg(this->db) << std::endl;
		sqlite3_free(zErrMsg);
	}
}

void Database::acceptFriend(std::string friend1, std::string friend2, bool accept){
	char* zErrMsg = 0;
	std::string sql;
	if (accept){
		sql = "UPDATE friendList SET relation = 'ami' WHERE user1 = '" + friend1 + "' AND user2 = '" + friend2 + "' AND relation = 'attente';";
	} else {
		sql = "DELETE FROM friendList WHERE (user1 = '" + friend1 + "' AND user2 = '" + friend2 + "') OR (user1 = '" + friend2 + "' AND user2 = '" + friend1 + "') AND relation = 'attente';";
	}
	int rc = sqlite3_exec(this->db, sql.c_str(), callback, 0, &zErrMsg);
	if (rc != SQLITE_OK){
		std::cout << "Error on acceptRequest: " << sqlite3_errmsg(this->db) << std::endl;
		sqlite3_free(zErrMsg);
	}
}

void Database::deleteFriend(std::string friend1, std::string friend2){
	char* zErrMsg = 0;
	std::string sql = "DELETE FROM friendList WHERE (user1 = '" + friend1 + "' AND user2 = '" + friend2 + "') OR (user1 = '" + friend1 + "' user2 = '" + friend2 + "') AND relation = 'ami';";
	int rc = sqlite3_exec(this->db, sql.c_str(), callback, 0, &zErrMsg);
	if (rc != SQLITE_OK){
		std::cout << "Error on deleteFriend: " << sqlite3_errmsg(this->db) << std::endl;
		sqlite3_free(zErrMsg);
	}
}

std::vector<std::string> Database::seeFriends(std::string username){
	char* zErrMsg = 0;
	std::vector<std::string> friendList;
	std::string sql =  "SELECT user1, user2 FROM friendList WHERE (user1 = '" + username + "' OR user2 = '" + username + "' AND relation = 'ami';";
	int rc = sqlite3_exec(this->db, sql.c_str(), callbackSee, &friendList, &zErrMsg);
	if (rc != SQLITE_OK){
		std::cout << "Error on seeFriends: " << sqlite3_errmsg(this->db) << std::endl;
		sqlite3_free(zErrMsg);
	}
}

std::vector<std::string> Database::seeFriendRequests(std::string username){
	char* zErrMsg = 0;
	std::vector<std::string> listRequests;
	std::string sql =  "SELECT user1, user2 FROM friendList WHERE (user1 = '" + username + "' OR user2 = '" + username + "' AND relation = 'relation';";
	int rc = sqlite3_exec(this->db, sql.c_str(), callbackSee, &listRequests, &zErrMsg);
	if (rc != SQLITE_OK){
		std::cout << "Error on seeFriends: " << sqlite3_errmsg(this->db) << std::endl;
		sqlite3_free(zErrMsg);
	}
}


int Database::callbackSee(void* var, int argc, char** argv, char** column){
	std::vector<std::string>* friendList = static_cast<std::vector<std::string>* >(var);
	for (int i = 0; i < argc; i++){
		friendList->push_back(argv[i]);
	}
	return 0;
}

int Database::myCallback(void* pUser, int argc, char** argv, char** columns){
	int *flag = static_cast<int*>(pUser);
    *flag = 1;
    return 0;
}

int Database::callback(void* NotUsed, int argc, char** argv, char** columns){
	for (int i = 0; i < argc; i++){
		printf("%s = %s\n", columns[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}


// Pour kick un client si il est deja connecter et ce reconnecte
int Database::callbackDisc(void* NotUsed, int argc, char** argv, char** columns){
	if (*argv[0] == '1'){
		std::cout << "closing old client..." << std::endl;
		close(atoi(argv[1]));
	}
	return 0;
}
int Database::callbackGetter(void* var, int argc, char** argv, char** columns){
	char** output = static_cast<char**>(var);
	*output = argv[0];
	return 0;
}
