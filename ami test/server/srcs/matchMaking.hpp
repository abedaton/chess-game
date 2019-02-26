#pragma once
#ifndef MATCHMAKING_HPP
#define MATCHMAKING_HPP

#include <vector>
#include <pthread.h>
#include "abstractGame.hpp"
//#include "../game/ClassicChess/ClassicChess.hpp"

class MatchMaking{
	public:
		MatchMaking();
		~MatchMaking() = default;
        void waitForMatch(AbstractUser* player,int gameMod);
    private:
        static void* run(void*);
        std::vector<AbstractUser*> pool;

        void startLoop();
};
#endif