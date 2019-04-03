#pragma once
#ifndef ABSTRACTGAME_HPP
#define ABSTRACTGAME_HPP

#include "abstractUser.hpp"

class AbstractGame{
    public:
        AbstractGame(AbstractUser* player1, AbstractUser* player2);
        virtual void mov() = 0;

};

#endif
