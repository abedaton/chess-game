#include "matchMaking.hpp"

MatchMaking::MatchMaking(){
    pthread_t gameThread;
    pthread_create(&gameThread, NULL, &MatchMaking::run, static_cast<void*>(this));
}

void* MatchMaking::run(void* tmp){
    static_cast<MatchMaking*>(tmp)->startLoop();
    return NULL;
}

void MatchMaking::startLoop(){
    while(true){
        if (pool.size() > 1){
            User* player1 = pool.at(0);
            pool.erase(pool.begin());
            User* player2 = pool.at(0);
            pool.erase(pool.begin());
            AbstractGame* game = new AbstractGame(player1, player2);
            //player1->startGame(game);
            //player2->startGame(game);
        }
    }
}

void MatchMaking::waitForMatch(User* player,int gameMod){
    pool.push_back(player);
}