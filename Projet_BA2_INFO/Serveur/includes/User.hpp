#pragma once
#ifndef USER_HPP
#define USER_HPP

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <vector>
#include <string>
#include <pthread.h>
#include <iostream>
#include <mutex>

#include "../srcs/database.cpp"
#include "../srcs/matchMaking.cpp"

class User: public AbstractUser{
	public:
		User(int client_sock, Database* db, MatchMaking* match);
		virtual ~User();		
        User(const User&) = delete;
        User& operator= (const User&) noexcept = delete;

		void startGame(SuperGame*, AbstractUser*, bool) override;
		void mov(std::string mov) override;
		void sendMov(std::string mov) override;
		void surrend() override;
		void sendMsg(std::string msg) override;
		void lose() override;
		void exit();
		std::string get_name() const override;
		
	private:
		int _clientSock;
		Database* _db;
		MatchMaking* _match;
		SuperGame* _game;
		AbstractUser* _opponent;
		bool _myTurn;
		bool _inverted;

		std::mutex _mutex;
		std::string _name;
		
		void handleClient();
		void checkLogin();
		void letsRegister();
		void chat();
		void waitForMatch();
		void recvMov();
		
		inline void waitForProcess();
		inline void endProcess();


		void sendInt(int num);
		void sendStr(std::string);

        int recvInt();
		int recvInt(int flag);

        std::string recvStr();

		void sendStrToSocket(int socket, std::string str);
		void sendIntToSocket(int socket, int number);
		void sendVector(std::vector<std::string>);

		static void* run(void* tmp);

		void sendMessage(); 
		void recvMessage();
		void addFriend();
		void removeFriend();
		void acceptFriend();
		void getFriendList();
		void getFriendRequests();
		void getOnlineFriendList();
		void getMyInfo();
		void GetUserInfo();
		
};

enum Protocol : int {
    PASS = 0, REGISTER, LOGIN, CHAT, WAITFORMATCH, MOV, SURREND, 
    SENDMESSAGE, ADDFRIEND, REMOVEFRIEND,
	ACCEPTFRIEND, GETFRIENDLIST, GETFRIENDREQUESTS,
	GETONLINEFRIENDLIST, GETMYINFO, GETUSERINFO
};


#endif
