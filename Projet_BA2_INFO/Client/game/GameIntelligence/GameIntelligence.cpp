#pragma once
#include "GameIntelligence.hpp"

BaseGameType* GameIntelligence::get_game() const{
	return this->game;
}

void GameIntelligence::set_game(BaseGameType* jeu){
	this->game = jeu;
}

void GameIntelligence::make_game(std::string game_rule, std::string game_type, Player* player_one, Player* player_two){
	
	mout<<player_one<<std::endl;
	mout<<player_two<<std::endl;
	
	Dico* dico = make_dico("../../../csv");
	
	BaseChess* game_part;

	if (game_rule == "classic"){
		
		Affichage* aff = new Affichage();
		game_part = new ClassicChess(player_one,player_two,player_one,dico,aff);
		
	}
	else if (game_rule == "dark"){
		
		AffichageDarkChess* aff = new AffichageDarkChess();
		game_part = new DarkChess(player_one, player_two, player_one,nullptr, dico,aff);
		
	}
	else if (game_rule == "trappist"){
		
		Affichage* aff = new Affichage();
		game_part = new TrappistChess(player_one,player_two,player_one,dico,aff);
		
	}
	else if (game_rule == "anti"){
		
		Affichage* aff = new Affichage();
		game_part = new AntiChess(player_one,player_two,player_one,dico,aff);
		
	}
	else{throw MyException(&mout,"game_rule inconnu!");}
	
	
	BaseGameType* game;
	
	if (game_type == "tour_par_tour"){game = new TourParTour(game_part);}
	else if (game_type == "temps_reel"){game = new TempsReel(game_part);}
	else if (game_type == "pendule"){game = new Pendule(game_part);}
	else{throw MyException(&mout,"game_rule inconnu!");}
	
	this->set_game(game);
	
}

void GameIntelligence::make_game_human_and_bot(std::string game_rule, std::string game_type, std::string langue,std::string tag_bot){
	/* fonction peremttant de lancer une partie classique avec 1 joueurs humains et un bot de test */
	
	Human* player_one = new Human("player1",langue);
	
	Bot* player_two = make_bot("player2",tag_bot,"../../../bots_csv");
	
	this->make_game(game_rule,game_type,player_one,player_two);
	
}

void GameIntelligence::make_game_two_bots(std::string game_rule, std::string game_type, std::string tag_bot_one, std::string tag_bot_two){
	/* fonction peremttant de lancer une partie classique avec 2 bots de test */
	
	Bot* player_one = make_bot("player1",tag_bot_one,"../../../bots_csv");
	
	Bot* player_two = make_bot("player2",tag_bot_two,"../../../bots_csv");
	
	this->make_game(game_rule,game_type,player_one,player_two);
}

void GameIntelligence::make_game_two_humans(std::string game_rule, std::string game_type, std::string langue){
	/* fonction peremttant de lancer une partie classique avec 2 joueurs humains */
	
	Human* player_one = new Human("player1",langue);
	
	Human* player_two = new Human("player2",langue);
	
	this->make_game(game_rule,game_type,player_one,player_two);
}

void GameIntelligence::make_game_two_silenced_humans(std::string game_rule, std::string game_type, std::string langue){
	/* fonction peremttant de lancer une partie classique avec 2 joueurs humains */
	
	SilencedHuman* player_one = new SilencedHuman("player1",langue);
	
	SilencedHuman* player_two = new SilencedHuman("player2",langue);
	
	this->make_game(game_rule,game_type,player_one,player_two);
}

void GameIntelligence::execute_game(){
	
	try{
		bool end = false;
		while (not end){
			std::pair<bool,std::string> result = this->get_game()->execute_step();
			end = result.first;
			//std::cout<<"RESULTAT ENVOYE: "<<result.second<<std::endl;
		}
	}	
	catch(MyException& e){
		mout<<e.what()<<std::endl;
		mout<<"myexception catched"<<std::endl;
	}
	
}


