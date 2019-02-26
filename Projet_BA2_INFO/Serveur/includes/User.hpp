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

#include "../game/ClassicChess/ClassicChess.cpp"
//#include "../game/ClassicChess/ClassicChess.hpp"
//#include  "../game/Bot/Human/Human.hpp"
//  #include  "../game/Bot/Human/Human.cpp"
//#include "../game/main/main_code_classic_chess/test_classic.cpp"
//MyOstream mout("logfile.txt");

#include "../srcs/database.cpp"
#include "../srcs/matchMaking.cpp"



class User: public AbstractUser{
	public:
		User(int client_sock);
		virtual ~User() = default;		
        User(const User&);
        User& operator= (const User&) noexcept = default;

		//void startGame(AbstractGame*, bool) override;
		std::string in();
		void out(std::string str);
		void exit();
	
	private:
		int _clientSock;
		Database* _db;
		MatchMaking* _match;

		std::string name;
		bool isLog;
		bool inGame;
		bool UserTurn;
		
		void handleClient();
		void checkLogin();
		void letsRegister();
		void chat();
		void waitForMatch();
		//void getMov(); //OLD
		void mov(); //tmp
		
		void sendInt(int num);
        int recvInt();
		void sendStr(std::string);
        std::string recvStr();

		static void* run(void* tmp);
	
};

enum Protocol : int {
	EXIT = 0, REGISTER, LOGIN, PASS,WAITFORMATCH, GETMOV, MOV
};

#endif
