#pragma once
#ifndef ABSTRACTUSER_HPP
#define ABSTRACTUSER_HPP

#include <string>
#include "../game/GameTypes/TourParTour/TourParTour.cpp"
#include "../game/GameTypes/Pendule/Pendule.cpp"
#include "../game/GameTypes/TempsReel/TempsReel.cpp"

class AbstractGame;

class AbstractUser{
    public:
        virtual ~AbstractUser() = default;
        virtual void startGame(TempsReel*, AbstractUser*, bool,bool,bool, std::string) = 0;
        virtual void mov(std::string) = 0;
        virtual std::string get_name() const = 0; 
        virtual void surrend() = 0;
        virtual void sendMsg(std::string) = 0;
        virtual void lose() = 0;
};

#endif
