#include "../includes/matchMaking.hpp"
#define TIME 10



MatchMaking::MatchMaking() : pools(5){
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
    std::cout << "Before tree : "  <<  gameMod << std::endl;
    int first, second;
    while(true){
        if (pools[gameMod-1].size() > 1){
            std::cout << "A" << std::endl;
            std::cout << pools[gameMod-1].size() << std::endl;
            //random en fonction de la size
            std::cout << "B" << std::endl;
            srand((unsigned int)time(NULL));
            first = rand() % pools[gameMod-1].size();
            AbstractUser* player1 = pools[gameMod-1].at(first);
            pools[gameMod-1].erase(pools[gameMod-1].begin() + first);
            std::cout << "FIRST PLAYER SELECTED" << std::endl;
            
            second = rand() % pools[gameMod-1].size();
            AbstractUser* player2 = pools[gameMod-1].at(second);
            pools[gameMod-1].erase(pools[gameMod-1].begin() + second);
            std::cout << "SECOND PLAYER SELECTED" << std::endl;


            //AbstractGame* game = new AbstractGame(player1, player2);
            BaseChess* game;
            switch(gameMod){
                case 1:
                    game = new ClassicChess(player1, player2, new Dico(), "francais");
                    break;
                default:
                    game = new ClassicChess(player1, player2, new Dico(), "francais"); // tmp
                    break;
            }
            std::cout << "Launching Game" << std::endl;
            player1->startGame(game, player2, true);
            player2->startGame(game, player1, false);
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
void MatchMaking::waitForMatch(AbstractUser* player, int gameMod){
  std::cout << "gameMod : "  << gameMod << std::endl;
  pools[gameMod-1].push_back(player);
  std::cout << "waitForMatch : " << pools[gameMod-1].size() << std::endl;
}
