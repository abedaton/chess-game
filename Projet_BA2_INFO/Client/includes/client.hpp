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

#define PORT 5555


class Client: AbstractClient {
    public:
        Client(const char* ip);
        ~Client();
        void connectionError() override;
		void startingGame(bool playerTurn) override;
		void opponentMov(std::string mov) override;
		void printMessage(std::string) override;
	private:
		Request* _request;
		TempsReel* _game; // TempsReel est une classe commune entre TempsReel, TourParTour et Pendule -quentin
		std::string _username;
		bool _gameStart;
		bool _myTurn;
		int _gameMod;

		void firstWindow();
		bool registerWindow();
		bool logInWindow();
		void friendsWindow();
		void chatWindow();
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
