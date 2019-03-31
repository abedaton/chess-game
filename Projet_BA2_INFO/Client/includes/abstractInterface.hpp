#pragma once

#ifndef ABSTRACTINTERFACE_HPP
#define ABSTRACTINTERFACE_HPP

#include "abstractClient.hpp"
//#include "../../game/Plateau/AbstractPlateau.hpp"
#include <pthread.h>

class AbstractInterface { 
    public:
        virtual ~AbstractInterface() = default;
        virtual void myShow(){}//for gui interface
        virtual void gameStart(std::string opponent){this->_ennemyName = opponent;}
        virtual void connectionError() = 0;
        virtual void win() = 0;
        virtual void lose() = 0;
		virtual void recvMessage(std::string name, std::string mov) = 0; 
        virtual void movPossibleUpdate(std::vector<std::pair<int,int> >* listMov){}

        virtual void recvFriendRequestsList(std::vector<std::string> vec){this->_friendRequest = vec;}
        virtual void recvFriendList(std::vector<std::pair<std::string, bool> > frendList){this->_friendList = frendList;}
        virtual void recvInfo(std::string username, int nbrGames, int win, int elo){
			(void)username;
			(void)nbrGames;
			(void)win;
			(void)elo;
		}

        virtual void feedback(int info, std::string message){}



        struct info {
            int nbrGames;
            int win;
            int elo;
        };
    protected:
        int _chessMod;
        bool _chronoMod = false;
        std::string _ennemyName;
        std::string  _username;
        //AbstractPlateau* _board;
        struct info _info;
        std::vector<std::string> _friendRequest;
        std::vector<std::pair<std::string, bool> > _friendList;
};

#endif
