#pragma once

#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <regex>
#include <mutex>

#include "abstractInterface.hpp"

class Terminal: public AbstractInterface{
    public:
        Terminal(AbstractClient* client);
        ~Terminal();
        void connectionError() override;
		void gameStart(std::string opponent) override;
		void end(int) override;

		void recvMessage(std::string name, std::string mov) override;
        void movPossibleUpdate(std::vector<std::pair<int,int> >* listMov) override;

		void recvFriendRequestsList(std::vector<std::string> vec) override;
		void recvFriendList(std::vector<std::pair<std::string, bool> > frendList) override;
		void recvInfo(std::string username, int nbrGames, int win, int elo) override;

		void feedback(int info, std::string message) override;

    private:
        AbstractClient* _user;

		bool _gameStart;
		bool _end;
        std::mutex* _mut;

        void firstWindow();
		bool registerWindow();
		bool logInWindow();
		void friendsWindow();
		void chatWindow();
		void menuWindow();
		bool selectGameModeWindow();
		void gameWindow();
        void myFlush();

		std::string affichage_plateau();
};

#endif
