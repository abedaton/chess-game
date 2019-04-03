#pragma once
#ifndef MATCHMAKING_HPP
#define MATCHMAKING_HPP

#include <vector>
#include <pthread.h>
#include <random>
#include <time.h>
#include <chrono>
#include <cmath>
#include <map>

#include "abstractGame.hpp"
#include "abstractUser.hpp"


class MatchMaking{
  	public:
		MatchMaking();
		~MatchMaking() = default;
        void waitForMatch(AbstractUser* player,int gameMod, int elo);
        bool exitQueue(AbstractUser* player, int gameMod, int elo);
        void waitForFriendMatch(AbstractUser* player);
        void startFrendlyGame(AbstractUser* player,std::string Friend, int gameMod);
    private:
        static void* run(void*);
        void poolSort(int mod, int rank, AbstractUser* player);

        void startMatch(AbstractUser* player1, AbstractUser* player2, int gameMod);
        int getRank(int elo);

        std::vector< std::vector< std::vector< AbstractUser* > > > pools;
        std::map<std::string,AbstractUser*> poolsFriend;
    
    struct matchMod{
       MatchMaking* match;
       int mod;
       int elo;
       AbstractUser* player;
    };
};

#endif
