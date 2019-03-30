//#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma once
#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include "pthread.h"
#include <mutex>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <errno.h>
#include <chrono>
#include <queue>
#include "math.h"

#include "abstractClient.hpp"

#define PORT 5555

class Request{
    public:
        Request(AbstractClient* client, const char* ip);
        ~Request();
        int letsRegister(std::string username,std::string password, std::string email);
        int login(std::string username,std::string password);
        void findMatch(int modDeJeu);
        void chat(std::string msg); //tmp just pour chat with opponent 

        void surrend();
        void mov(std::string mov);

        void sendMessage(std::string name, std::string msg);
        void addFriend(std::string name);
        void removeFriend(std::string name);
        void acceptFriend(std::string name, bool accept);
        void getFriendList();
        void getFriendRequests();
        void getOnlineFriendList();
        void getMyInfo();
        void getUserInfo(std::string username);
        void exitQueue();

    private:
		std::mutex _mutex;
		pthread_t _listenerThread;
		
        std::string _ipServ;
        int _clientSock;
        struct sockaddr_in _servAddr;
		AbstractClient* _client;

        void setup(const char* ip);
		static void* run(void*);
		void listener();
        void startingGame();
        void opponentMov();
        void recvMessageInGame();
		void error();
		inline void waitForProcess();
		inline void endProcess();
        void sendStr(std::string str);
        int recvInt();
		int recvInt(int flag);
        void sendInt(int num);
        std::string recvStr();

        void recvMessage();
        void recvFriendRequestsList();
        void recvFriendList();
        void recvInfo();
        void gameWithFriends(std::string username, int gameMod);
        void putGRequest();
        std::vector<std::string> recvVector();

        void feedback();

};

enum Protocol : int {
    STARTGAME = 25, OPPONENTMOV, RECVMESSAGEINGAME, RECVMESSAGE, SEEREQUESTS, RECVFRIENDLIST, RECVINFO, RECVDUEL, FEEDBACK
};


#endif
