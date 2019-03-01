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

#include "request.hpp"

#define PORT 5555

class Client: AbstractClient {
    public:
        Client();
        ~Client();
        void connectionError() override;
		void startingGame(bool playerTurn) override;
		void opponentMov(int coord1, int coord2, bool lose) override;
	private:
		Request* _request;
		bool _gameStart;
		//bool _myTurn;
		//std::vector<int> _listMov;

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
        struct sockaddr_in _servAddr;
};


#endif