#ifndef USER_HPP
#define USER_HPP

#include "database.hpp"
#include "matchMaking.hpp"

class Serveur;

class User{
	public:
		User(int* client_sock, Database* db,MatchMaking* match,Serveur*);
		~User() = default;
		void startGame(AbstractGame* game);
	private:
		int* _clientSock;
		Database* _db;
		MatchMaking* _match;
		AbstractGame* _game;
		Serveur* serveur;
		
		std::string name;
		bool isLog;
		bool inGame;

		void handleClient();
		void exit();
		void checkLogin();
		void letsRegister();
		void chat();
		void waitForMatch();
		void getMov(); //tmp
		void mov(); //tmp

		void sendInt(int num);
        int recvInt();
		void sendStr(std::string);
        std::string recvStr();

		static void* run(void* tmp);
		
};


#endif
