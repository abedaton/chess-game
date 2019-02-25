#include "../includes/matchMaking.hpp"

MatchMaking::MatchMaking(){
    pthread_t gameThread;
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
    pthread_create(&gameThread, NULL, &MatchMaking::run, static_cast<void*>(this));
    #pragma GCC diagnostic pop
}

void* MatchMaking::run(void* tmp){
    static_cast<MatchMaking*>(tmp)->startLoop();
    return NULL;
}

void MatchMaking::startLoop(){
    while(true){
        if (pool.size() > 1){
            AbstractUser* player1 = pool.at(0);
            pool.erase(pool.begin());
            AbstractUser* player2 = pool.at(0);
            pool.erase(pool.begin());
            //AbstractGame* game = new Game(player1, player2);
            //player1->startGame(game, true);
            //player2->startGame(game, false);
        }
    }
}

void MatchMaking::waitForMatch(AbstractUser* player,int gameMod){
    if (gameMod == 1){
        pool.push_back(player);
    }
}
