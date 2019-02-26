#pragma once
#ifndef ABSTRACTGAME_HPP
#define ABSTRACTGAME_HPP

#include "abstractUser.hpp"

class AbstractGame{
    public:
        AbstractGame(AbstractUser* player1, AbstractUser* player2); //méthode que les varientes du jeu doive implémenté 
        virtual void mov() = 0;

    //Vous pouvez ajouté les méthodes commune au 4 varientes
};

#endif