#pragma once

#ifndef AFFICHAGE_CPP
#define AFFICHAGE_CPP

#include "Affichage.hpp"


//

std::string make_ligne(std::string s,int taille_voulue,int taille){
	/* fonction créant une ligne des taille voulu rempli d'un type de caractère s
	 * entrecoupés a des intervalle taille de barres vericales (|) */
	 
	std::string res;
	
	for(int i=0;i<taille;i++){
		res += "|";
		for(int j=0;j<taille_voulue;j++){res += s;}
	}
	
	res += "|";
	
	return res;
}

std::string crea_ligne_lettres(int limite,int taille_voulue){
	/* fonction créant une legende de lettres sur une ligne*/
	 
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

std::string get_decallage_de_bord_gauche(int a_decal){
	std::stringstream ss;
	
	for(int p=0;p<a_decal;p++){ss<<" ";}
	
	return ss.str();
}

//------------------------------------------------------------------------------------

//Affichage::Affichage(Plateau* plat, Dico* dict,std::string pre,std::string suf ,std::string lang ,Player* play_low, Player* play_high,Player* play_active, std::string symb_low, std::string symb_high) : plateau(plat), dico(dict), dico_prefix(pre), dico_suffix(suf), dico_language(lang), low_player(play_low), high_player(play_high),active_player(play_active),low_player_symbol(symb_low),high_player_symbol(symb_high), taille_case_hor(8), taille_case_ver(3){} //*< Constructor
//Affichage::Affichage(Plateau* plat, Dico* dict,std::string pre,std::string suf ,std::string lang ,Player* play_low, Player* play_high,Player* play_active, std::string symb_low, std::string symb_high, int t_c_hor, int t_c_ver) : plateau(plat), dico(dict), dico_prefix(pre), dico_suffix(suf), dico_language(lang), low_player(play_low), high_player(play_high),active_player(play_active),low_player_symbol(symb_low),high_player_symbol(symb_high), taille_case_hor(t_c_hor), taille_case_ver(t_c_ver){} //*< Constructor

Affichage::Affichage() : AbstractAffichage() {} //*< Constructor


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


std::string Affichage::affichage_player(Player* play){
	/* fonction affichant le joueur et son symbole sur une ligne */
	
	std::string symb = this->get_player_symbol(play);
	
	std::stringstream ss;
	
	ss<<std::endl;
	ss<<"["<<play<<"] ("<<symb<<")"<<std::endl;
	ss<<std::endl;
	
	return ss.str();
	
}

std::string Affichage::make_big_ligne(){
	/* fonction creant une ligne sur base de "-" et de "|" */
	
	std::stringstream ss;
	
	ss<<"-";
	ss<<make_ligne("-",this->get_taille_case_hor(),int(this->get_plateau()->get_taille()));
	ss<<"-"<<std::endl;
	
	return ss.str();
	
}

std::string Affichage::make_big_ligne_vide(){
	/* fonction creant une ligne sur base de " " (espaces vide) et de "|" */
	
	std::stringstream ss;
	
	ss<<make_ligne(" ",this->get_taille_case_hor(),int(this->get_plateau()->get_taille()));
	ss<<std::endl;
	
	return ss.str();
	
}

std::string Affichage::get_affichage_line(int i,int new_i){
	/* fonction creant une ligne avec au centre de chaque case le symbole de la pice s'y trouvant */
	
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
	/* fonction assemblant toutes les parties du plateau ensemble affin de pouvoir renvoyer un plateau complet */
		
	std::stringstream s;
	
	int taille_voulue_hor = this->get_taille_case_hor(); //8;
	int taille_voulue_ver = this->get_taille_case_ver(); //2;
		
	std::string big_l = this->make_big_ligne();
	std::string big_l_vide = make_big_ligne_vide();
	std::string letter_line = crea_ligne_lettres(int(this->get_plateau()->get_taille()),taille_voulue_hor);
	
	
	int ver_av = (taille_voulue_ver-1)/2; // le 1 vient de la taille de la piece qui sera tjs sur 1 seul ligne!
	int ver_ap = (taille_voulue_ver-1) - ver_av; // le 1 vient de la taille de la piece qui sera tjs sur 1 seul ligne!
	
	int max_decal = int(std::to_string(this->get_plateau()->get_taille()-1).size());
	int max_reste = taille_voulue_hor-max_decal;
	
	s << get_decallage_de_bord_gauche(max_reste/2);
	for(int p=0;p<(max_decal+(max_reste/2)) ;p++){s<<" ";}
	s << letter_line << std::endl;
	
	s << get_decallage_de_bord_gauche(max_reste/2);
	for(int p=0;p<(max_decal+(max_reste/2)) ;p++){s<<" ";}
	s << big_l_vide;

	for(int i=0;i<this->get_plateau()->get_taille();i++){
		
		int new_i = this->get_plateau()->get_taille()-1-i;
		
		// calcul chiffre ligne
		std::string str_numb = std::to_string(new_i+1);
		int numb_size = int(str_numb.size());
		int numb_reste = taille_voulue_hor-numb_size + (max_decal-numb_size);
        int numb_av = (numb_reste/2);
		//
		
		s << get_decallage_de_bord_gauche(max_reste/2);
		for(int p=0;p<(numb_av + numb_size -1) ;p++){s<<" ";} // -1 car -|
		s<<big_l;
		
		
		s << get_decallage_de_bord_gauche(max_reste/2);
		for(int p=0;p<(numb_av + numb_size) ;p++){s<<" ";}
		for(int k=0;k<ver_av;k++){s<<big_l_vide;}
		
		s << get_decallage_de_bord_gauche(max_reste/2);
		s<<str_numb;
		for(int p=0;p<numb_av;p++){s<<" ";}
		s<<"|";
		
		//s << get_decallage_de_bord_gauche(numb_av);
		s<<this->get_affichage_line(i,new_i);
		
        for(int p=0;p<numb_av;p++){s<<" ";}
		s<<str_numb;

		s<<std::endl;
		s << get_decallage_de_bord_gauche(max_reste/2);
		for(int p=0;p<(numb_av + numb_size) ;p++){s<<" ";}
		for(int o=0;o<ver_ap;o++){s<<big_l_vide;}
	}
	
	s << get_decallage_de_bord_gauche(max_reste/2);
	for(int p=0;p<(max_decal+(max_reste/2) -1) ;p++){s<<" ";} // -1 car -|
	s<<big_l;
	
	s << get_decallage_de_bord_gauche(max_reste/2);
	for(int p=0;p<(max_decal+(max_reste/2)) ;p++){s<<" ";}
	s << big_l_vide;
	
	s << get_decallage_de_bord_gauche(max_reste/2);
	for(int p=0;p<(max_decal+(max_reste/2)) ;p++){s<<" ";}
	s << letter_line << std::endl;
    
    return s.str();
}

std::string Affichage::get_affichage(){
	/* fonction d'affichage principal, affiche le plateau et les 2 joeurs a leur coté respectif */
	
	std::stringstream ss;
	
	ss<<this->affichage_player(this->get_high_player());
	
	ss<<this->affichage_plateau();
	
	ss<<this->affichage_player(this->get_low_player());
	
	return ss.str();
	
	
}

void Affichage::show(){
	/* fonction d'affichage principal, affiche le plateau et les 2 joeurs a leur coté respectif */
	
	this->get_active_player()->send_msg(this->get_affichage(),true);
	
}
#endif
