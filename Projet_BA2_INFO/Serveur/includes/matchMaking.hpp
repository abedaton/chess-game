#pragma once
#ifndef MATCHMAKING_HPP
#define MATCHMAKING_HPP

#include <vector>
#include <pthread.h>
#include <random>
#include <time.h>
#include <chrono>
#include <cmath>

#include "abstractGame.hpp"
#include "abstractUser.hpp"
//#include "../../game/GameTypes/SuperGame/SuperGame.cpp"


class MatchMaking{
  	public:
		MatchMaking();
		~MatchMaking() = default;
        void waitForMatch(AbstractUser* player,int gameMod, int elo);
        bool exitQueue(AbstractUser* player, int gameMod, int elo);
    private:
        static void* run(void*);
        void poolSort(int mod, int rank, AbstractUser* player);

        void startMatch(AbstractUser* player1, AbstractUser* player2, int gameMod);
        int getRank(int elo);

        std::vector< std::vector< std::vector< AbstractUser* > > > pools;
    
    struct matchMod{
       MatchMaking* match;
       int mod;
       int elo;
       AbstractUser* player;
    };
};

#endif
