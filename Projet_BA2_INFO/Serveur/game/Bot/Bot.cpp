
#include "Bot.hpp"
// ---------------------- HORS classe BOT ------------------------------

Bot* make_bot(std::string name_bot,std::string tag_bot,std::string csv_path){
	
	Bot* bot = new Bot(name_bot);
	
	CsvReader* reader = new CsvReader();
	
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

// ---------------------- classe BOT ------------------------------

Bot::Bot(std::string nom) : Player(nom), counter(0), move_list(std::vector<std::string>()) {} //*< Constructor

Bot::Bot(const Bot& bot): Player(bot), counter(bot.counter), move_list(bot.move_list) {}

std::string Bot::next_input(){
	
	std::string inp;
	
	std::vector<std::string> vect = this->move_list;
	
	if (counter < int(vect.size())){inp = vect[counter];}
	else{inp = "";}
	
	this->counter += 1;
	
	std::cout<<inp<<std::endl;
	
	return inp;
	
}

void Bot::set_moves(std::vector<std::string> vect){
	
	this->move_list = vect;
	
	}

std::string Bot::get_type_prefix() const{
	return "Bot";
}
