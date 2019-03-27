#ifndef ABSTRACTINTERFACE_HPP
#define ABSTRACTINTERFACE_HPP

#include "abstractClient.hpp"
#include <pthread.h>

class AbstractInterface { 
    public:
        std::vector<std::string> _friendRequest;
        virtual void myShow(){}//for gui interface
        virtual void gameStart(std::string opponent) = 0;//+bord
        virtual void connectionError() = 0;
        virtual void win() = 0;
        virtual void lose() = 0;
		virtual void recvMessage(std::string name, std::string mov) = 0; 
        virtual void pingForUpdate() = 0;

        virtual void recvFriendRequestsList(std::vector<std::string> vec){this->_friendRequest = vec;}
        struct info {
            int nbGame;
            int nbWin;
            int elo;

        };
    private:
        bool _darkChessMod = false;
        bool _chronoMod = false;
        std::string _opponentName = "";
        struct info _info;
};

#endif
