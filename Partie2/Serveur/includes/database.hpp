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
#include <stdint.h>

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <thread>
#include <limits>
#include <vector>


class Database{
    public:
        Database();
        void addUser(std::string username, std::string password, std::string email);
        bool isUsernameFree(std::string username);
        bool isLoginOk(std::string username, std::string password);
        void update(std::string table, std::string colName, std::string username, std::string newValue);
        sqlite3* getdb();
    private:
        void createTable();
        long unsigned hashPass(std::string password);
        bool selectData(std::string sql);
        static int myCallback(void* pUser, int argc, char** argv, char** columns);
        static int callback(void* NotUsed, int argc, char** argv, char** columns);
        sqlite3* db;
};


#endif
