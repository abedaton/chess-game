#pragma once
#ifndef MATCHMAKING_CPP
#define MATCHHMAKING_CPP
#include "../includes/matchMaking.hpp"
#define TIME 10

/*
 * Constructeur matchmaking
 */
MatchMaking::MatchMaking(): pools(12){
    for (auto &vect : pools){
        vect.resize(3);
    }
}

/*
 * Lance le matchmaking
 */
void* MatchMaking::run(void* tmp){
    struct matchMod* structMatch = static_cast<struct matchMod*>(tmp);
    structMatch->match->poolSort(structMatch->mod, structMatch->elo, structMatch->player);
    return NULL;
}

/*
 * Fait le tri des pools de matchmaking
 */
void MatchMaking::poolSort(int gameMod, int elo, AbstractUser* player){
    int rank = getRank(elo);
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
                    pools[gameMod][i].erase(pools[gameMod][i].begin());
                    startMatch(player1, player2, gameMod);
                    break;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(30000)); //sleep 30 sec
            if (range < pools[gameMod].size())
                range++;
            else
                std::this_thread::sleep_for(std::chrono::milliseconds(60000)); //sleep 1 min 
        }
    }
}

/*
 * Lance une partie entre deux joueurs d'un certain mode de jeu
 */
void MatchMaking::startMatch(AbstractUser* player1, AbstractUser* player2, int gameMod){
    std::cout << "Launching Game" << std::endl;
    SilencedHuman* play_one = new SilencedHuman(player1->get_name(), "francais");
    SilencedHuman* play_two = new SilencedHuman(player2->get_name(), "francais");

    SuperGame* game = new SuperGame(gameMod, player1, true, play_one, play_two);

    player1->startGame(game, player2, true);
    player2->startGame(game, player1, false);
}

//On ajoute le joueur en fonction de son mode de jeu

/*
 * On associe le joueur à la pool correspondante et on le met dans le matchmaking
 */
void MatchMaking::waitForMatch(AbstractUser* player, int gameMod, int elo){
    struct matchMod* structMatch;
    structMatch = static_cast<struct matchMod*>(malloc(sizeof(struct matchMod)));
    structMatch->match = this;
    structMatch->player = player;
    structMatch->mod = gameMod;
    structMatch->elo = elo;

    pthread_t thread;
    
    pthread_create(&thread, NULL, &MatchMaking::run, static_cast<void*>(structMatch));
}

bool MatchMaking::exitQueue(AbstractUser* player, int gameMod, int elo){
    int rank = getRank(elo);
    std::vector<AbstractUser*>* vect =  &(pools[gameMod][rank]);
    if ( (!vect->empty()) && vect->at(0) == player){
        vect->erase(vect->begin());
        return true;
    } else {
        return false;
    } 
} 

int MatchMaking::getRank(int elo){
    int rank;
    if (elo < 1000) {
        rank = 0;
    } else if (elo < 1700) {
        rank = 1;
    } else {
        rank = 2;
    }
    return rank;
}

void MatchMaking::waitForFriendMatch(AbstractUser* player){
    this->poolsFriend[player->get_name()] = player;
}

void MatchMaking::startFrendlyGame(AbstractUser* player,std::string Friend, int gameMod){
    AbstractUser* userFriend = this->poolsFriend[Friend];
    this->poolsFriend.erase(this->poolsFriend.find(Friend));   
    startMatch(userFriend, player, gameMod);
}

#endif