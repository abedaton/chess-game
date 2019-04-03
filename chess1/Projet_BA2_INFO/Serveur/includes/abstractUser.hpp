#pragma once
#ifndef ABSTRACTUSER_HPP
#define ABSTRACTUSER_HPP

#include <string>
#include "../../game/GameTypes/SuperGame/SuperGame.cpp"

class AbstractGame;

class AbstractUser: public AbstractPlayer{
    public:
        virtual ~AbstractUser() = default;
        virtual void startGame(SuperGame*, AbstractUser*, bool) = 0;
        virtual void sendMov(std::string) = 0;
        virtual std::string get_name() = 0; 
        virtual void sendMsg(std::string) = 0;
        virtual void lose() = 0;
        virtual void opponentSurrend() = 0;
};

#endif
