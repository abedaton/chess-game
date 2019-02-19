
#include <iostream>
#include <sstream>

#include "../../ClassicChess/ClassicChess.cpp"

MyOstream mout("logfile.txt");

Dico* make_dico(){
	
	Dico* dico = new Dico();
	
	std::string csv_path = "../../csv";
	std::string csv_filename = get_first_file_of_dir(csv_path,".csv");
	
	if (csv_filename == ""){throw MyException(&mout, "PAS DE FICHIER CSV! POUR LE DICTIONNAIRE");}
	
	std::stringstream ss;
	ss << csv_path << '/'<< csv_filename;
	
	dico->load(ss.str());
	
	return dico;

}

Bot* make_bot(std::string name_bot,std::string tag_bot){
	
	Bot* bot = new Bot(name_bot);
	
	CsvReader* reader = new CsvReader();
	
	std::string csv_path = "../../bots_csv";
	
	std::string csv_filename = get_first_file_of_dir(csv_path,".csv");
	
	if (csv_filename == ""){throw MyException(&mout, "PAS DE FICHIER CSV! POUR LE BOT");}
	
	std::stringstream ss;
	ss << csv_path << '/'<< csv_filename;
	
	reader->load(ss.str());
	
	std::vector<std::string> vect = reader->search_col(tag_bot);
	
	vect.erase(vect.begin());
	
	bot->set_moves(vect);
	
	return bot;
	
	
}

void two_humans_main(std::string langue){
	
	Human* player_one = new Human("player1");
	
	Human* player_two = new Human("player2");
	
	mout<<(*player_one)<<std::endl;
	mout<<(*player_two)<<std::endl;
	
	Dico* dico = make_dico();

	ClassicChess* serv = new ClassicChess(player_one,player_two,dico,langue);
	
	serv->execute();
	
}

void human_and_bot_main(std::string langue){
	
	Human* player_one = new Human("player1");
	
	Bot* player_two = make_bot("player2","bot_un");
	
	mout<<(*player_one)<<std::endl;
	mout<<(*player_two)<<std::endl;
	
	Dico* dico = make_dico();
	
	ClassicChess* serv = new ClassicChess(player_one,player_two,dico,langue);
	
	serv->execute();
}

int main(){
	
	// "anglais" , "francais" , "neerlandais"
	
	//two_humans_main("anglais");
	//human_and_bot_main("anglais");
	two_humans_main("francais");
	
	return 0;
}
