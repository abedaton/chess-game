#pragma once
#ifndef ABSTRACTUSER_HPP
#define ABSTRACTUSER_HPP

#include <string>

class AbstractGame;

class AbstractUser{
    public:
        virtual std::string in() = 0; // méthode avec les quelle le jeu peux interagire avec le joueur
        virtual void out(std::string) = 0;

        virtual void startGame(AbstractGame*, bool) = 0; //for matchMaking
};

#endif
