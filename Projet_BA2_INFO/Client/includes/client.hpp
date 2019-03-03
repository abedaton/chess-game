#pragma GCC diagnostic ignored "-Wunused-variable"
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <regex>

#include "../srcs/request.cpp"
//#include "../../Serveur/game/ClassicChess/ClassicChess.cpp"

#define PORT 5555


class Client: AbstractClient {
    public:
        Client();
        ~Client();
        void connectionError() override;
		void startingGame(bool playerTurn) override;
		void opponentMov(std::string mov) override;
		void recvMessage() override;
	private:
		Request* _request;
		BaseChess* _game;
		std::string _username;
		bool _gameStart;
		bool _myTurn;
		int _gameMod;

		void firstWindow();
		bool registerWindow();
		bool logInWindow();
		void menuWindow();
		bool selectGameModeWindow();
		void gameWindow();
		
		static void myFlush();

        void setup(std::string ip);
        void handleClient();
		void sShutdown();

        void sendStr(std::string str);
        int recvInt();
        void sendInt(int num);
		std::string recvStr();
        int _clientSock;
};

#endif
