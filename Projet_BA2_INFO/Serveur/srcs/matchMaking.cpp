#include "../includes/matchMaking.hpp"
#define TIME 10



MatchMaking::MatchMaking(){
    struct matchMod* mMod;
    for(int i = 1; i<5; ++i){
        pthread_t thread;
        mMod = static_cast<struct matchMod*>(malloc(sizeof(struct matchMod)));
        (*mMod).match = this;
        (*mMod).mod = i;
        pthread_create(&thread, NULL, &MatchMaking::run, static_cast<void*>(mMod));
    }
}

void* MatchMaking::run(void* tmp){
    struct matchMod* structMatch = static_cast<struct matchMod*>(tmp);
    structMatch->match->poolSort(structMatch->mod);
    return NULL;
}

void MatchMaking::poolSort(int gameMod){
    while(true){
        if (pools[gameMod-1].size() > 1){
            int first, second;
            //random en fonction de la size

            srand((unsigned int)time(NULL));

            first = rand() % pools[gameMod-1].size();
            AbstractUser* player1 = pools[gameMod-1].at(first);
            pools[gameMod-1].erase(pools[gameMod-1].begin());

            second = rand() % pools[gameMod-1].size();
            AbstractUser* player2 = pools[gameMod-1].at(second);
            pools[gameMod-1].erase(pools[gameMod-1].begin()+1);
            
            //AbstractGame* game = new AbstractGame(player1, player2);
            ///!\// Game* game = new Game(player1, player2, gameMod);
            //player1->startGame(game, true);
            //player2->startGame(game, false);
        }

    }
}

//initialisation des vecteur pour les différents modes de jeu
void MatchMaking::initPool(int size){
  for(int i = 0; i<size; ++i){
    std::vector<AbstractUser*> v;
    pools.push_back(v);
  }
}


//On ajoute le joueur en fonction de son mode de jeu
void MatchMaking::waitForMatch(AbstractUser* player,int gameMod){
  pools[gameMod-1].push_back(player);
}
