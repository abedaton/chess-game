/*
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
		
		bool get_inverted() const override;
		void set_inverted(bool) override;
		
		bool get_ennemy_inverted() const override;
		void set_ennemy_inverted(bool) override;
		
		std::string get_ennemy_name() const override;
		void set_ennemy_name(std::string) override;
		
	private:
		Request* _request;
		TempsReel* _game;
		std::string _username;
		bool _gameStart;
		bool _myTurn;
		bool _end;
		int _gameMod;
		bool _isInverted;
		bool _isEnnemyInverted;
		std::string _ennemyName;

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
*/
//////////////////////////////////////////////////////////////////////////////////////////
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "../srcs/request.cpp"
#include "../srcs/interface.cpp"
#include "../srcs/terminal.cpp"
#include "../game/Gestion/Pendule/Pendule.cpp"
#include "../game/Gestion/TempsReel/TempsReel.cpp"
#include "../game/Gestion/TourParTour/TourParTour.cpp"

#include "abstractPlayer.hpp" //tmp



class Client: public AbstractPlayer, public AbstractClient{
	private:
		AbstractInterface* _interface;
		Request* _server;
		TempsReel* _game;

		int _gameMod;
	public:
		Client(const char* ip, bool interface);
		~Client();
		
		//call by interface
		bool letsRegister(std::string username,std::string password, std::string email) override;
		bool login(std::string username,std::string password) override;
		void waitForMatch(int gameMod) override;

		void sendMessage(std::string name,std::string msg) override;
		void addFriend(std::string name) override;
		void removeFriend(std::string name) override;
		void getFriendList() override;
		void getOnlineFriendList() override;
		void getUserInfo() override;

		void click(std::string square) override;
		void exit() override;
		//call by server
		void startingGame(bool playerTurn, std::string opponentName) override;
		void opponentMov(std::string mov) override;
		void recvMessage(std::string name,std::string msg) override;
		void connectionError() override;
		//call by game
		void mov(std::string mov) override;
		void win() override;
		void lose() override;
};

#endif
