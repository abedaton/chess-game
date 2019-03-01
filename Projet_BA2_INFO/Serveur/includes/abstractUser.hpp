#pragma once
#ifndef ABSTRACTUSER_HPP
#define ABSTRACTUSER_HPP

#include <string>
#include "../game/ClassicChess/ClassicChess.cpp"

class AbstractGame;

class AbstractUser : public Human{
    public:
        virtual void startGame(BaseChess*, AbstractUser*, bool) = 0;
};

#endif
