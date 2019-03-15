#pragma once
#ifndef MATCHMAKING_HPP
#define MATCHMAKING_HPP

#include <vector>
#include <pthread.h>
#include <random>
#include <time.h>

#include "abstractGame.hpp"
#include "abstractUser.hpp"


class MatchMaking{
	public:
		MatchMaking();
		~MatchMaking() = default;
    void waitForMatch(AbstractUser* player,int gameMod);
  private:
      static void* run(void*);
      
      std::vector<std::vector<AbstractUser*> > pools;
			void initPool(int size = 4);
      void poolSort(int mod);
};

struct matchMod{
  MatchMaking* match;
  int mod;
};

#endif
