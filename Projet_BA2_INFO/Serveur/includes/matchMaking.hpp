#pragma once
#ifndef MATCHMAKING_HPP
#define MATCHMAKING_HPP

#include <vector>
#include <pthread.h>
#include <random>
#include <time.h>
#include <cmath>

#include "abstractGame.hpp"
#include "abstractUser.hpp"


class MatchMaking{
  	public:
		MatchMaking();
		~MatchMaking() = default;
        void waitForMatch(AbstractUser* player,int gameMod, int elo);
    private:
        static void* run(void*);
        std::vector<std::vector<std::vector<std::pair<AbstractUser*, int> > > > pools;
        void poolSort(int mod, int rank);

        void startMatch(AbstractUser* player1, AbstractUser* player2, int gameMod);
    
    struct matchMod{
       MatchMaking* match;
       int mod;
       int rank;
    };
};

#endif
