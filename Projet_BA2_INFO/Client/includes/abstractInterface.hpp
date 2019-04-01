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
        virtual void updateMov(std::string str){(void)str;}//for gui interface
        virtual void gameStart(std::string) = 0;
        virtual void connectionError() = 0;
        virtual void end(int){}
		virtual void recvMessage(std::string, std::string) = 0; 
        virtual void movPossibleUpdate(std::vector<std::pair<int,int> >*){};

        virtual void recvFriendRequestsList(std::vector<std::string>){}
        virtual void recvFriendList(std::vector<std::pair<std::string, bool> >){}
        virtual void recvInfo(std::string, int, int, int){}

        virtual void feedback(int, std::string){}



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
