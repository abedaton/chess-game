#pragma once
#ifndef ABSTRACTUSER_HPP
#define ABSTRACTUSER_HPP

#include <string>
#include "../game/Games/ClassicChess/ClassicChess.cpp"
#include "../game/Games/DarkChess/DarkChess.cpp"
#include "../game/Games/TrappistChess/TrappistChess.cpp"

class AbstractGame;

class AbstractUser{
    public:
        virtual void startGame(BaseChess*, AbstractUser*, bool) = 0;
        virtual void opponentMov(std::string) = 0;
        virtual std::string get_name() const = 0; 
        virtual void surrend() = 0;
        virtual void sendMsg(std::string) = 0;
};

#endif
