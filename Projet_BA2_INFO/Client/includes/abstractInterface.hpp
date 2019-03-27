#ifndef ABSTRACTINTERFACE_HPP
#define ABSTRACTINTERFACE_HPP

#include "abstractClient.hpp"
#include <pthread.h>

class AbstractInterface { 
    public:
        virtual void myShow(){}//for gui interface
        virtual void gameStart(std::string opponent) = 0;//+bord
        virtual void connectionError() = 0;
        virtual void win() = 0;
        virtual void lose() = 0;
		virtual void recvMessage(std::string name, std::string mov) = 0; 
        virtual void pingForUpdate() = 0;

        virtual void recvFriendRequestsList(std::vector<std::string> vec){this->_friendRequest = vec;}
        virtual void recvFriendList(std::vector<std::pair<std::string, bool> > frendList){this->_friendList = frendList;}
        struct info {
            int nbGame;
            int nbWin;
            int elo;
        };
    protected:
        bool _darkChessMod = false;
        bool _chronoMod = false;
        std::string _ennemyName;
        std::string  _username;
        struct info _info;
        std::vector<std::string> _friendRequest;
        std::vector<std::pair<std::string, bool> > _friendList;
};

#endif
