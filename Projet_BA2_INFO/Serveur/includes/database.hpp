#pragma once
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
#include <cmath>

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <thread>
#include <limits>
#include <vector>
#include <chrono>
#include <iomanip>


class Database{
    public:
        Database();
        ~Database();
        int getInt(std::string table, std::string column);
        int getUserInt(std::string column, std::string username);
        bool isUsernameFree(std::string username);
        bool isLoginOk(std::string username, std::string password);
        void addUser(std::string username, std::string password, std::string email, int socket);
        void updateInfo(std::string table, std::string colName, std::string username, std::string newValue);
        void updateUserLog(std::string table, int logged);
        void updateUserDisc(std::string table);
        void resetStuff();
        void updateWin(std::string username, std::string rival, bool win);
        void createInfoTable(std::string username);
        void deleteUser(std::string username);

        bool sendFriendRequest(std::string friend1, std::string friend2);
        
        std::vector<std::string> seeFriendRequests(std::string username);
        std::vector<std::string> seeFriends(std::string username);

        void acceptFriend(std::string friend1, std::string friend2, bool accept);
        void deleteFriend(std::string friend1, std::string friend2);
    private:
        void createTable();
        void updateAllSockets();
        long unsigned hashPass(std::string password);
        bool selectData(std::string sql);
        static int myCallback(void* pUser, int argc, char** argv, char** columns);
        static int callback(void* NotUsed, int argc, char** argv, char** columns);
        static int callbackDisc(void* NotUsed, int argc, char** argv, char** columns);
        static int callbackGetter(void* var, int argc, char** argv, char** column);
        static int callbackSee(void* friendList, int argc, char** argv, char** column);
        char* getValue(std::string table, std::string column);
        char* getUserValue(std::string column, std::string username);
        std::vector<std::string> getFrendList(std::string table);

    

        sqlite3* db;
};


#endif
