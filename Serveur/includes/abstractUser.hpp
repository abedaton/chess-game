#pragma once
#ifndef ABSTRACTUSER_HPP
#define ABSTRACTUSER_HPP

#include <string>
#include "../game/Gestion/TourParTour/TourParTour.cpp"
#include "../game/Gestion/Pendule/Pendule.cpp"

class AbstractGame;

class AbstractUser{
    public:
        virtual void startGame(TempsReel*, AbstractUser*, bool,bool,bool, std::string) = 0;
        virtual void opponentMov(std::string) = 0;
        virtual std::string get_name() const = 0; 
        virtual void surrend() = 0;
        virtual void sendMsg(std::string) = 0;
};

#endif
