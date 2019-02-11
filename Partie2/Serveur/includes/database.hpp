#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sqlite3.h>

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <string>
#include <thread>
#include <limits>
#include <mutex>

sqlite3* initSql();
void addUser(sqlite3* db, std::string username, std::string password, std::string email);
void createTable(sqlite3* db);
bool isUsernameFree(std::string username);
bool isLoginOk(sqlite3* db, std::string username, std::string password);
long unsigned hashPass(std::string password);
bool selectData(sqlite3* db, std::string sql);


#endif
