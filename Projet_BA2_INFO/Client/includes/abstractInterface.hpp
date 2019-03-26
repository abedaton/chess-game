#ifndef ABSTRACTINTERFACE_HPP
#define ABSTRACTINTERFACE_HPP

#include "abstractClient.hpp"
#include <QtWidgets>

class AbstractInterface { 
    public:
        virtual void myShow(){}//for gui interface
        virtual void gameStart(std::string opponent) = 0;//+bord
        virtual void connectionError() = 0;
        virtual void win() = 0;
        virtual void lose() = 0;
		virtual void recvMessage(std::string name, std::string mov) = 0; 
        virtual void pingForUpdate() = 0;

};

#endif
