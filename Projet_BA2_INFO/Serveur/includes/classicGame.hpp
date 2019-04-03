// a changé par le code de quantain
#pragma once
#ifndef CLASSICGAME_HPP
#define CLASSICGAME_HPP

#include "abstractGame.hpp"

class ClassicGame: AbstractGame{
    ClassicGame(AbstractUser* player1, AbstractUser* player2);
    void mov() override;
};

#endif
