#include "../includes/matchMaking.hpp"
#define TIME 10

MatchMaking::MatchMaking(): pools(12){
    for (auto &vect : pools){
        vect.resize(3);
    }
}

void* MatchMaking::run(void* tmp){
    struct matchMod* structMatch = static_cast<struct matchMod*>(tmp);
    structMatch->match->poolSort(structMatch->mod, structMatch->elo, structMatch->player);
    return NULL;
}

<<<<<<< HEAD
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
=======
void MatchMaking::poolSort(int gameMod, int elo, AbstractUser* player){
    int rank;
    if (elo < 1000) {
        rank = 0;
    } else if (elo < 1700) {
        rank = 1;
    } else {
        rank = 2;
    }
    std::cout << "gameMod: " << gameMod << ", rank: " << rank << std::endl;
    std::vector<AbstractUser*>* vect = &(pools[gameMod][rank]);
    vect->push_back(player);
    if (vect->size() > 1){
        std::cout << "ok" << std::endl;
        AbstractUser* player1 = vect->at(0);
        vect->erase(vect->begin());
        AbstractUser* player2 = vect->at(0);
        vect->erase(vect->begin());
        startMatch(player1, player2, gameMod);
    } else {
        int range = 0;
        while(! vect->empty() && pools[gameMod][rank][0] == player){
            int begin = rank-range;
            if (begin < 0)
                begin = 0;
            int end = rank+range;
            if (end > vect->size())
                end =vect->size();
            for (int i=begin; i == end; i++){
                if (i != rank && ! pools[gameMod][i].empty()){
                    AbstractUser* player1 = vect->at(0);
                    vect->erase(vect->begin());
                    AbstractUser* player2 = pools[gameMod][i].at(0);
                    pools[gameMod-1][i].erase(pools[gameMod][i].begin());
                    startMatch(player1, player2, gameMod);
>>>>>>> Partie_Serveur
                    break;
                }
            }
<<<<<<< HEAD
            std::cout << "Launching Game" << std::endl;
            
            TourParTour* tt_game = new TourParTour(game);
            
            bool p_one_inv = false;
            bool p_two_inv = true;
            
            player1->startGame(tt_game, player2, true, p_one_inv,p_two_inv, player2->get_name());
            player2->startGame(tt_game, player1, false,p_two_inv, p_one_inv, player1->get_name());
=======
            std::this_thread::sleep_for(std::chrono::milliseconds(30000)); //sleep 30 sec
            if (range < pools[gameMod].size())
                range++;
            else
                std::this_thread::sleep_for(std::chrono::milliseconds(60000)); //sleep 1 min 
>>>>>>> Partie_Serveur
        }
    }
}

void MatchMaking::startMatch(AbstractUser* player1, AbstractUser* player2, int gameMod){
    std::cout << "Launching Game" << std::endl;
    
    SuperGame* game = new SuperGame(gameMod, player1, true);

    player1->startGame(game, player2, true);
    player2->startGame(game, player1, false);
}

//On ajoute le joueur en fonction de son mode de jeu

void MatchMaking::waitForMatch(AbstractUser* player, int gameMod, int elo){
    struct matchMod* structMatch;
    structMatch = static_cast<struct matchMod*>(malloc(sizeof(struct matchMod)));
    structMatch->match = this;
    structMatch->player = player;
    structMatch->mod = gameMod-1;
    structMatch->elo = elo;

    pthread_t thread;
    pthread_create(&thread, NULL, &MatchMaking::run, static_cast<void*>(structMatch));
}

//bool MatchMaking::tryStopWait(AbstractUser* player){
//  for (auto &vect1 : pools){
//      for (auto &vect2 : vect1){
//          if (vect2[0] == player){
//              vect->erase(vect->begin());
//              return true;
//          }
//      }
//  }
//  return false;
//}