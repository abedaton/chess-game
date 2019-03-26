#ifndef ABSTRACTINTERFACE_HPP
#define ABSTRACTINTERFACE_HPP

#include "abstractClient.hpp"
#include <QtWidgets>

class AbstractInterface { 
    public:
        void myShow(){}//for gui interface
        void gameStart(std::string opponent) = 0;//+bord
        void connectionError() = 0;
        void win() = 0;
        void lose() = 0;
		void recvMessage(std::string name, std::string mov) = 0; 
        void pingForUpdate() = 0;

        virtual void myShow(){}//for gui interface
        virtual void gameStart(std::string opponent) = 0;//+bord
        virtual void connectionError() = 0;
        virtual void win() = 0;
        virtual void lose() = 0;
		virtual void recvMessage(std::string name, std::string mov) = 0; 
        virtual void pingForUpdate() = 0;

};

#endif
