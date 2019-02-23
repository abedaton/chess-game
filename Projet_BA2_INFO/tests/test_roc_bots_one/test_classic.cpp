
#include <iostream>
#include <sstream>

#include "../../ClassicChess/ClassicChess.cpp"

MyOstream mout("logfile.txt");

void two_humans_main(std::string langue){
	
	Human* player_one = new Human("player1");
	
	Human* player_two = new Human("player2");
	
	mout<<(*player_one)<<std::endl;
	mout<<(*player_two)<<std::endl;
	
	Dico* dico = make_dico("../../csv");

	ClassicChess* serv = new ClassicChess(player_one,player_two,dico,langue);
	
	serv->execute();
	
}

void human_and_bot_main(std::string langue){
	
	Human* player_one = new Human("player1");
	
	Bot* player_two = make_bot("player2","bot_un","../../bots_csv");
	
	mout<<(*player_one)<<std::endl;
	mout<<(*player_two)<<std::endl;
	
	Dico* dico = make_dico("../../csv");
	
	ClassicChess* serv = new ClassicChess(player_one,player_two,dico,langue);
	
	serv->execute();
}

void two_bots(std::string langue){
	
	Bot* player_one = make_bot("player1","bot_two","../../bots_csv");
	
	Bot* player_two = make_bot("player2","bot_un","../../bots_csv");
	
	mout<<(*player_one)<<std::endl;
	mout<<(*player_two)<<std::endl;
	
	Dico* dico = make_dico("../../csv");
		
	ClassicChess* serv = new ClassicChess(player_one,player_two,dico,langue);
	
	serv->execute();
}

int main(){
	
	// "anglais" , "francais" , "neerlandais"
	
	//two_humans_main("anglais");
	//human_and_bot_main("francais");
	//two_humans_main("francais");
	two_bots("francais");
	
	return 0;
}
