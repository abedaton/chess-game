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

#include "abstractInterface.hpp"

class Terminal: public AbstractInterface{
    public:
        Terminal(AbstractClient* client);
        ~Terminal();
        void connectionError() override;
		void gameStart(std::string opponent, AbstractPlateau* board) override;
		void win() override;
		void lose() override;

		void recvMessage(std::string name, std::string mov) override;
        void movPossibleUpdate(std::vector<std::string> listMov) override;

		void recvFriendRequestsList(std::vector<std::string> vec) override;
		void recvFriendList(std::vector<std::pair<std::string, bool> > frendList) override;
		void recvInfo(std::string username, int nbrGames, int win, int elo) override;


    private:
        AbstractClient* _user;

		bool _gameStart;
		bool _end;
        //bord

        void firstWindow();
		bool registerWindow();
		bool logInWindow();
		void friendsWindow();
		void chatWindow();
		void menuWindow();
		bool selectGameModeWindow();
		void gameWindow();
        void myFlush();

		void updateBoardClassic();
		void updateBoardDark();
		std::string affichage_plateau();
};

#endif
