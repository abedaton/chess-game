#pragma once
#ifndef ABSTRACTUSER_HPP
#define ABSTRACTUSER_HPP

#include <string>
<<<<<<< HEAD
#include "../game/Gestion/TourParTour/TourParTour.cpp"
#include "../game/Gestion/Pendule/Pendule.cpp"
=======
#include "../game/GameTypes/SuperGame/SuperGame.cpp"
>>>>>>> Partie_Serveur

class AbstractGame;

class AbstractUser: public AbstractPlayer{
    public:
<<<<<<< HEAD
        virtual void startGame(TempsReel*, AbstractUser*, bool,bool,bool, std::string) = 0;
        virtual void opponentMov(std::string) = 0;
=======
        virtual ~AbstractUser() = default;
        virtual void startGame(SuperGame*, AbstractUser*, bool) = 0;
        virtual void sendMov(std::string) = 0;
>>>>>>> Partie_Serveur
        virtual std::string get_name() const = 0; 
        virtual void surrend() = 0;
        virtual void sendMsg(std::string) = 0;
        virtual void lose() = 0;
};

#endif
