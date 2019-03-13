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
    int first, second;
    while(true){
        if (pools[gameMod-1].size() > 1){
            std::cout << pools[gameMod-1].size() << std::endl;
            //random en fonction de la size
            srand((unsigned int)time(NULL));
            //first = rand() % pools[gameMod-1].size(); ///////////////////////////////////
            first = 0;
            AbstractUser* player1 = pools[gameMod-1].at(first);
            pools[gameMod-1].erase(pools[gameMod-1].begin() + first);
            
            //second = rand() % pools[gameMod-1].size(); ////////////////////////////////// nombre entre 0 et pools[gameMod-1].size()
            second = 0;
            AbstractUser* player2 = pools[gameMod-1].at(second);
            pools[gameMod-1].erase(pools[gameMod-1].begin() + second);

			SilencedHuman* play_one = new SilencedHuman(player1->get_name(),"francais");
			SilencedHuman* play_two = new SilencedHuman(player2->get_name(),"francais");
            Dico* dico = make_dico("Serveur/game/csv");
            BaseChess* game;
            switch(gameMod){
                case 1:
                    game = new ClassicChess(play_one, play_two, play_one, dico);
                    break;
                case 2:
                    game = new DarkChess(play_one, play_two, play_one, dico);
                    break;
                case 3:
                    game = new TrappistChess(play_one, play_two, play_one, dico);
                    break;
                case 4:
                    game = new AntiChess(play_one, play_two, play_one, dico);
                    std::cout << "Anti : ";
                    std::cout<< game << std::endl;
                    break;
                default:
                    game = new ClassicChess(play_one, play_two, play_one, dico);
                    break;
            }
            std::cout << "Launching Game" << std::endl;
            
            TourParTour* tt_game = new TourParTour(game);
            
            player1->startGame(tt_game, player2, true);
            player2->startGame(tt_game, player1, false);
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
  pools[gameMod-1].push_back(player);
}
