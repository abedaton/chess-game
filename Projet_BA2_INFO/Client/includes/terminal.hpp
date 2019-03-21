#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
//#include <sys/socket.h>
#include <stdio.h>
#include <regex>

#include "abstractInterface.hpp"

class Terminal: public AbstractInterface{
    public:
        Terminal(AbstractClient* client);
        ~Terminal();
        void connectionError() override;
		void gameStart(std::string opponent) override; //+bord
//void opponentMov(std::string mov) override;
		void win() override;
		void lose() override;

		void recvMessage(std::string name, std::string mov) override;
        void pingForUpdate() override;

    private:
        AbstractClient* _user;
        std::string _username;
		bool _gameStart;
		bool _end;
        //bord
		std::string _ennemyName;

        void firstWindow();
		bool registerWindow();
		bool logInWindow();
		void friendsWindow();
		void chatWindow();
		void menuWindow();
		bool selectGameModeWindow();
		void gameWindow();
        void myFlush();

};

#endif
