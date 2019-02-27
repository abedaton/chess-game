#include "GameIntelligence.hpp"

BaseChess* GameIntelligence::get_game() const{
	return this->game;
}

void GameIntelligence::set_game(BaseChess* jeu){
	this->game = jeu;
}

void GameIntelligence::make_classic_game(Player* player_one, Player* player_two, std::string langue){
	
	mout<<player_one<<std::endl;
	mout<<player_two<<std::endl;
	
	Dico* dico = make_dico("../../csv");
	
	ClassicChess* serv = new ClassicChess(player_one,player_two,dico,langue);
	
	this->set_game(serv);

}

void GameIntelligence::make_classic_game_human_and_bot(std::string langue,std::string tag_bot){
	/* fonction peremttant de lancer une partie classique avec 1 joueurs humains et un bot de test */
	
	Human* player_one = new Human("player1",langue);
	
	Bot* player_two = make_bot("player2",tag_bot,"../../bots_csv");
	
	this->make_classic_game(player_one,player_two,langue);
	
}

void GameIntelligence::make_classic_game_two_bots(std::string langue, std::string tag_bot_one, std::string tag_bot_two){
	/* fonction peremttant de lancer une partie classique avec 2 bots de test */
	
	Bot* player_one = make_bot("player1",tag_bot_one,"../../bots_csv");
	
	Bot* player_two = make_bot("player2",tag_bot_two,"../../bots_csv");
	
	this->make_classic_game(player_one,player_two,langue);
}

void GameIntelligence::make_classic_game_two_humans(std::string langue){
	/* fonction peremttant de lancer une partie classique avec 2 joueurs humains */
	
	Human* player_one = new Human("player1",langue);
	
	Human* player_two = new Human("player2",langue);
	
	this->make_classic_game(player_one,player_two,langue);
}

void GameIntelligence::make_classic_game_two_silenced_humans(std::string langue){
	/* fonction peremttant de lancer une partie classique avec 2 joueurs humains */
	
	SilencedHuman* player_one = new SilencedHuman("player1",langue);
	
	SilencedHuman* player_two = new SilencedHuman("player2",langue);
	
	this->make_classic_game(player_one,player_two,langue);
}

void GameIntelligence::execute_game(){
	bool end = false;
	while (not end){
		end = this->get_game()->execute_step();
	}
	
}


