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

//#include "../game/ClassicChess/ClassicChess.cpp"
//#include "../game/ClassicChess/ClassicChess.hpp"
//#include  "../game/Bot/Human/Human.hpp"
//  #include  "../game/Bot/Human/Human.cpp"
//#include "../game/main/main_code_classic_chess/test_classic.cpp"
//MyOstream mout("logfile.txt");

#include "database.hpp"
#include "matchMaking.hpp"



class User: public AbstractUser{
	public:
		User(int client_sock);
		virtual ~User() = default;		
        User(const User&);
        User& operator= (const User&) noexcept = default;

		void startGame(AbstractGame*, bool) override;
		std::string in();
		void out(std::string str);
		void exit();
		std::string getName();
		void setName(const char *new_name) { name = new_name;}

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
		//void waitForMatch();
		//void getMov(); //OLD
		void mov(); //tmp
		
		void sendInt(int num);
        int recvInt();
		void sendStr(std::string);
        std::string recvStr();

		static void* run(void* tmp);


		//tout ce qui est par rapport aux amis vient ci-dessous:
		public:
		void addFriendToList(User *new_friend);
		void addFriendsToList(std::vector <User*> friends);

   		private:
        std::vector<User*> friends; //todo: meilleure data structure
        User *findUserByID(int id);
        void listOnlineFriends();
        void deleteFriend(int id_of_user_to_delete);
        void addFriend(int id_of_user_to_add);

        //notifications to send dans bdd ou seulement en ligne
        //comment contacter clients en ligne comment contacter client 



	private:
		
		
};

enum Protocol : int {
	EXIT = 0, REGISTER, LOGIN, PASS,WAITFORMATCH, GETMOV, MOV, 
	LISTONLINEFRIENDS, ADDFRIEND, REMOVEFRIEND
};

#endif
