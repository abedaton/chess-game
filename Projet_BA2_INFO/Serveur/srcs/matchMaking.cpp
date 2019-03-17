#include "../includes/matchMaking.hpp"
#define TIME 10

MatchMaking::MatchMaking(): pools(12){
    for (auto &vect : pools){
        vect.resize(3);
    }
}

void* MatchMaking::run(void* tmp){
    struct matchMod* structMatch = static_cast<struct matchMod*>(tmp);
    structMatch->match->poolSort(structMatch->mod, structMatch->rank);
    return NULL;
}

void MatchMaking::poolSort(int gameMod, int rank){
    std::vector<std::pair<AbstractUser*, int> >* vect = &pools[gameMod][rank];

    if (pools[gameMod][rank].size() > 1){
        AbstractUser* player1 = vect->at(0).first;
        vect->erase(vect->begin());
        AbstractUser* player2 = vect->at(0).first;
        vect->erase(vect->begin());
        startMatch(player1, player2, gameMod);
    } else if (vect->size() == 1){
        //si plus de 60s TO DO
        for (int i=0; i == pools[gameMod].size() ;i++){
            if (i != rank && ! pools[gameMod][i].empty()){
                AbstractUser* player1 = vect->at(0).first;
                vect->erase(vect->begin());
                AbstractUser* player2 = pools[gameMod][i].at(0).first;
                pools[gameMod-1][i].erase(pools[gameMod][i].begin());
                startMatch(player1, player2, gameMod);
                break;
            }
        }
    }
}

void MatchMaking::startMatch(AbstractUser* player1, AbstractUser* player2, int gameMod){
    SilencedHuman* play_one = new SilencedHuman(player1->get_name(),"francais");
	SilencedHuman* play_two = new SilencedHuman(player2->get_name(),"francais");
    Dico* dico = make_dico("Serveur/game/csv");
    BaseChess* game;
    switch(gameMod){
        case 1:
            game = new ClassicChess(play_one, play_two, play_one, dico);
            break;
        case 2:
            game = new DarkChess(play_one, play_two, play_one, nullptr, dico);
            break;
        case 3:
            game = new TrappistChess(play_one, play_two, play_one, dico);
            break;
        case 4:
            game = new AntiChess(play_one, play_two, play_one, dico);
            break;
        default:
            game = new ClassicChess(play_one, play_two, play_one, dico);
            break;
    }
    std::cout << "Launching Game" << std::endl;
    
    TourParTour* tt_game = new TourParTour(game);
    
    bool p_one_inv = false;
    bool p_two_inv = true;
    
    player1->startGame(tt_game, player2, true, p_one_inv,p_two_inv, player2->get_name());
    player2->startGame(tt_game, player1, false,p_two_inv, p_one_inv, player1->get_name());
}

//On ajoute le joueur en fonction de son mode de jeu
void MatchMaking::waitForMatch(AbstractUser* player, int gameMod, int elo){
    int rank;
    if (elo < 1000) {
        rank = 0;
    } else if (elo < 1500) {
        rank = 1;
    } else {
        rank = 2;
    }
    pools[gameMod-1][rank].push_back(std::make_pair(player, 0));
    poolSort(gameMod-1, rank);
}

