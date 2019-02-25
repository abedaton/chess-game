#include "Affichage.hpp"


//

std::string make_ligne(std::string s,int taille_voulue,int taille){
	std::string res;
	
	for(int i=0;i<taille;i++){
		res += "|";
		for(int j=0;j<taille_voulue;j++){res += s;}
	}
	
	res += "|";
	
	return res;
}

std::string crea_ligne_lettres(int limite,int taille_voulue){
	std::string alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string res;
		
	res = "";
	for(int i=0;i<limite;i++){
		
		int taille_reste = taille_voulue-1; // 1 = taille alph[i]
		int av = taille_reste/2;
		int ap = taille_reste - av;
		
		res += " ";
		for(int j=0;j<av;j++){res += " ";}
		res += alph[i];
		for(int m=0;m<ap;m++){res += " ";}
		}
	res += " ";
	
	return res;
}

//------------------------------------------------------------------------------------

Affichage::Affichage(Plateau* plat, Dico* dict,std::string pre,std::string suf ,std::string lang ,Player* play_low, Player* play_high, std::string symb_low, std::string symb_high) : plateau(plat), dico(dict), dico_prefix(pre), dico_suffix(suf), dico_language(lang), low_player(play_low), high_player(play_high),low_player_symbol(symb_low),high_player_symbol(symb_high), taille_case_hor(8), taille_case_ver(2){} //*< Constructor

std::ostream& operator <<(std::ostream &s,Affichage &c){
	/* affchage d'un Affichage */
	(void)c;
    s<<"Affichage()";
    return s;
}

std::ostream& operator <<(std::ostream &s,Affichage* c){
	/* affchage d'un Affichage */
    s<<(*c);
    return s;
}

Plateau* Affichage::get_plateau(){return this->plateau;} 
Dico* Affichage::get_dico(){return this->dico;}
std::string Affichage::get_dico_prefix(){return this->dico_prefix;}
std::string Affichage::get_dico_suffix(){return this->dico_suffix;}
std::string Affichage::get_dico_language(){return this->dico_language;}
Player* Affichage::get_low_player(){return this->low_player;}
Player* Affichage::get_high_player(){return this->high_player;}
std::string Affichage::get_low_player_symbol(){return this->low_player_symbol;}
std::string Affichage::get_high_player_symbol(){return this->high_player_symbol;}
int Affichage::get_taille_case_hor(){return this->taille_case_hor;}
int Affichage::get_taille_case_ver(){return this->taille_case_ver;}

std::string Affichage::get_player_symbol(Player* play){
	
	if (play == this->get_high_player()){return this->get_high_player_symbol();}
	else if (play == this->get_low_player()){return this->get_low_player_symbol();}
	else {throw MyException(&mout, "player inconnu pour obtention de son symbole!");}
	
}

std::string Affichage::affichage_player(Player* play){
	
	std::string symb = this->get_player_symbol(play);
	
	std::stringstream ss;
	
	ss<<std::endl;
	ss<<"["<<play<<"] ("<<symb<<")"<<std::endl;
	ss<<std::endl;
	
	return ss.str();
	
}

std::string Affichage::make_big_ligne(){
	
	std::stringstream ss;
	
	ss<<make_ligne("-",this->get_taille_case_hor(),int(this->get_plateau()->get_taille()));
	ss<<"-"<<std::endl;
	
	return ss.str();
	
}

std::string Affichage::make_big_ligne_vide(){
	
	std::stringstream ss;
	
	ss<<make_ligne(" ",this->get_taille_case_hor(),int(this->get_plateau()->get_taille()));
	ss<<std::endl;
	
	return ss.str();
	
}

std::string Affichage::get_affichage_line(int i,int new_i){
	
	std::stringstream s;
	
	for(long long unsigned int j=0;j<(this->get_plateau()->get_row(i)).size();j++){
		
		std::stringstream ss;
		
		//ss.clear();//clear any bits set
		//ss.str(std::string());
		
		BitypeVar<Chesspiece*> elem = (this->get_plateau()->get_row(new_i))[j];
		Chesspiece* piece = elem.get_var();
		if (elem.get_state() == true){
			
			std::stringstream temp_ss;
			temp_ss<<this->get_dico_prefix()<<*(piece)<<this->get_dico_suffix();
			
			if (this->get_dico() != nullptr){
				ss<<this->get_dico()->search(this->get_dico_language(),temp_ss.str());
			}
			else{ss<<temp_ss.str();}
			
			ss<<this->get_player_symbol(piece->get_owner());
		}
		
		else {ss<<" ";}
		
		std::string str_elem;
		str_elem = ss.str();
		int elem_size = int(str_elem.length());
		int taille_reste = this->get_taille_case_hor() - elem_size;
		int hor_av = taille_reste/2;
		int hor_ap = taille_reste - hor_av;
		
		for(int m=0;m<hor_av;m++){s<<" ";}
		
		if (elem.get_state() == true){
			
			std::stringstream temp_s;
			temp_s<<this->get_dico_prefix()<<*(piece)<<this->get_dico_suffix();
			
			if (this->get_dico() != nullptr){
				s<<this->get_dico()->search(this->get_dico_language(),temp_s.str());
			}
			else{s<<temp_s.str();}
			
			s<<this->get_player_symbol(piece->get_owner());
		}
		else {s<<" ";}
		
		for(int n=0;n<hor_ap;n++){s<<" ";}
		
		s<<"|";
			
	}
	
	return s.str();
	
}

std::string Affichage::affichage_plateau(){
	
	//std::string pre ,std::string suf ,Dico* dico, std::string lang
		
	std::stringstream s;
	
	//std::vector<std::vector<BitypeVar<Chesspiece*>>>* plat = this->board;
	
	int taille_voulue_hor = this->get_taille_case_hor(); //8;
	int taille_voulue_ver = this->get_taille_case_ver(); //2;
		
	std::string big_l = this->make_big_ligne();
	std::string big_l_vide = make_big_ligne_vide();
	std::string letter_line = crea_ligne_lettres(int(this->get_plateau()->get_taille()),taille_voulue_hor);
	
	int ver_av = taille_voulue_ver/2;
	int ver_ap = taille_voulue_ver - ver_av;
	
	s << letter_line << std::endl << big_l_vide;

	for(int i=0;i<this->get_plateau()->get_taille();i++){
		
		s<<big_l;
		for(int k=0;k<ver_av;k++){s<<big_l_vide;}
		s<<"|";
		
		int new_i = this->get_plateau()->get_taille()-1-i;
		s<<this->get_affichage_line(i,new_i);
		
		std::string str_numb = std::to_string(new_i+1);
		int numb_size = int(str_numb.size());
		int numb_reste = taille_voulue_hor-numb_size;
        int numb_av = numb_reste/2;
        for(int p=0;p<numb_av;p++){s<<" ";}
		s<<str_numb;

		s<<std::endl;
		for(int o=0;o<ver_ap;o++){s<<big_l_vide;}
	}
	s<<big_l;
    
    return s.str();
}

std::string Affichage::get_affichage(){
	
	std::stringstream ss;
	
	ss<<this->affichage_player(this->get_high_player());
	
	ss<<this->affichage_plateau();
	
	ss<<this->affichage_player(this->get_low_player());
	
	return ss.str();
	
	
}
