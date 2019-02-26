#pragma once
#ifndef ABSTRACTUSER_HPP
#define ABSTRACTUSER_HPP

#include <string>

class AbstractGame;

class AbstractUser{
    public:
        virtual void startGame(AbstractGame*, bool) = 0;
};

#endif
