#pragma GCC diagnostic ignored "-Wunused-variable"
#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <errno.h>
#include <chrono>
#include <queue>

#include "abstractClient.hpp"

#define PORT 5555
#define IP "0.0.0.0"

struct FriendRequests
{
    std::string name;
};

class Request{
    public:
        Request(AbstractClient* client);
        ~Request();
        int letsRegister(std::string username,std::string password, std::string email);
        int login(std::string username,std::string password);
        void findMatch(int modDeJeu);
        void chat(std::string msg); //tmp just pour chat with opponent 
        //more fct for chat
		//more fct for friend
		//more fct for stat
        void surrend();
        void mov(std::string mov);
        //more fct for game

        bool listOnlineFriends();
        bool addFriend(std::string name);
        void removeFriend(std::string name);
        void recvFriendAddNotification();
        void proceedGameAndFriendRequests();

    private:
		std::mutex _mutex;
		pthread_t _listenerThread;
		
        std::string _ipServ;
        int _clientSock;
        struct sockaddr_in _servAddr;
		AbstractClient* _client;

        void setup();
		static void* run(void*);
		void listener();
        void startingGame();
        void opponentMov();
        void recvMessage();
		void error();
		inline void waitForProcess();
		inline void endProcess();
        void sendStr(std::string str);
        int recvInt();
		int recvInt(int flag);
        void sendInt(int num);
        std::string recvStr();

        std::queue<FriendRequests> friendRequests;
};

enum Protocol : int {
    EXIT = 0, REGISTER, LOGIN, PASS, WAITFORMATCH, GETMOV, MOV, 
    LISTONLINEFRIENDS, ADDFRIEND, REMOVEFRIEND, NEWFRIENDREQUEST, 
    FRIENDREQUESTANSWER, RECVMESSAGE, SENDMESSAGE
};


#endif
