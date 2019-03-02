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
		virtual ~User() = default;		
        User(const User&) = delete;
        User& operator= (const User&) noexcept = delete;

		void startGame(BaseChess*, AbstractUser*, bool) override;
		std::string in();
		void out(std::string str);
		void exit();
		//std::string get_name() const; // plustard apres du merge
		
		//std::string next_input() override;
        //void send_confirm_msg(std::string,bool) override;
        //using Human::send_confirm_msg;
	
	private:
		int _clientSock;
		Database* _db;
		MatchMaking* _match;
		BaseChess* _game;
		AbstractUser* _opponent;
		bool _myTurn;

		std::mutex _mutex;
		std::string name;
		
		void handleClient();
		void checkLogin();
		void letsRegister();
		void chat();
		void waitForMatch();
		void mov();
		void surrend();
		
		inline void waitForProcess();
		inline void endProcess();
		void sendInt(int num);
        int recvInt();
		int recvInt(int flag);
		void sendStr(std::string);
        std::string recvStr();

		static void* run(void* tmp);
		
		//virtual std::string get_type_prefix() const override;

		void updateInfo(); // update le nom et socket dans la database
		void updateInfoDisc(); // quand le client se deconnecte
		void updateInfoMatch(); 
		
};

enum Protocol : int {
	PASS = 0, REGISTER, LOGIN, TODO, WAITFORMATCH, MOV, SURREND
};

#endif
