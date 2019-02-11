#ifndef MATCHMAKING_HPP
#define MATCHMAKING_HPP

#include <vector>
#include <pthread.h>
#include "game.hpp"


class MatchMaking{
	public:
		MatchMaking();
		~MatchMaking() = default;
        void waitForMatch(User* player,int gameMod);
    private:
        static void* run(void*);
        std::vector<User*> pool;

        void startLoop();
};

#endif