#pragma once
#ifndef MATCHMAKING_HPP
#define MATCHMAKING_HPP

#include <vector>
#include <pthread.h>
#include <random>
#include <time.h>

#include "abstractGame.hpp"
#include "abstractUser.hpp"

#include "../game/ClassicChess/ClassicChess.cpp"


class MatchMaking{
	public:
		MatchMaking();
		~MatchMaking() = default;
        void waitForMatch(AbstractUser* player,int gameMod);
    private:
        static void* run(void*);
				//classic  = 0, trapist 1, dark 2, anti 3
        std::vector<std::vector<AbstractUser*>> pools;
				void initPool(int size = 4);
        void poolSort(int mod);
};

struct matchMod{
  MatchMaking* match;
  int mod;
};

#endif
