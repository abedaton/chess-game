#pragma once

#include "AbstractAffichage.hpp"

//AbstractAffichage::AbstractAffichage(Plateau* plat, Dico* dict,std::string pre,std::string suf ,std::string lang ,Player* play_low, Player* play_high,Player* play_active, std::string symb_low, std::string symb_high) : plateau(plat), dico(dict), dico_prefix(pre), dico_suffix(suf), dico_language(lang), low_player(play_low), high_player(play_high),active_player(play_active),low_player_symbol(symb_low),high_player_symbol(symb_high), taille_case_hor(8), taille_case_ver(3){} //*< Constructor
//AbstractAffichage::AbstractAffichage(Plateau* plat, Dico* dict,std::string pre,std::string suf ,std::string lang ,Player* play_low, Player* play_high,Player* play_active, std::string symb_low, std::string symb_high, int t_c_hor, int t_c_ver) : plateau(plat), dico(dict), dico_prefix(pre), dico_suffix(suf), dico_language(lang), low_player(play_low), high_player(play_high),active_player(play_active),low_player_symbol(symb_low),high_player_symbol(symb_high), taille_case_hor(t_c_hor), taille_case_ver(t_c_ver){} //*< Constructor

AbstractAffichage::AbstractAffichage() : plateau(nullptr), dico(nullptr), dico_prefix(""), dico_suffix(""), dico_language(""), low_player(nullptr), high_player(nullptr),active_player(nullptr),low_player_symbol(""),high_player_symbol(""), taille_case_hor(0), taille_case_ver(0){} //*< Constructor

std::ostream& operator <<(std::ostream &s,AbstractAffichage &c){
	/* affchage d'un AbstractAffichage */
	(void)c;
    s<<"AbstractAffichage()";
    return s;
}

std::ostream& operator <<(std::ostream &s,AbstractAffichage* c){
	/* affchage d'un AbstractAffichage */
    s<<(*c);
    return s;
}

Plateau* AbstractAffichage::get_plateau() const {return this->plateau;} 
Dico* AbstractAffichage::get_dico() const {return this->dico;}
std::string AbstractAffichage::get_dico_prefix() const {return this->dico_prefix;}
std::string AbstractAffichage::get_dico_suffix() const {return this->dico_suffix;}
std::string AbstractAffichage::get_dico_language() const {return this->dico_language;}
Player* AbstractAffichage::get_low_player() const {return this->low_player;}
Player* AbstractAffichage::get_high_player() const {return this->high_player;}
Player* AbstractAffichage::get_active_player() const {return this->active_player;}
std::string AbstractAffichage::get_low_player_symbol() const {return this->low_player_symbol;}
std::string AbstractAffichage::get_high_player_symbol() const {return this->high_player_symbol;}
int AbstractAffichage::get_taille_case_hor() const {return this->taille_case_hor;}
int AbstractAffichage::get_taille_case_ver() const {return this->taille_case_ver;}

std::string AbstractAffichage::get_player_symbol(Player* play){
	/* fonction récuperant le symbole associé au joeur pour distinguer ces piece de celle de l'adversaire
	 * ex : "*" */
	
	if (play == this->get_high_player()){return this->get_high_player_symbol();}
	else if (play == this->get_low_player()){return this->get_low_player_symbol();}
	else {throw MyException(&mout, "player inconnu pour obtention de son symbole!");}
	
}

void AbstractAffichage::set_plateau(Plateau* plat){this->plateau = plat;}
void AbstractAffichage::set_dico(Dico* dict){this->dico = dict;}
void AbstractAffichage::set_dico_prefix(std::string pre){this->dico_prefix = pre;}
void AbstractAffichage::set_dico_suffix(std::string suf){this->dico_suffix = suf;}
void AbstractAffichage::set_dico_language(std::string lang){this->dico_language = lang;}
void AbstractAffichage::set_low_player(Player* low_play){this->low_player = low_play;}
void AbstractAffichage::set_high_player(Player* high_play){this->high_player = high_play;}
void AbstractAffichage::set_active_player(Player* active_play){this->active_player = active_play;}
void AbstractAffichage::set_low_player_symbol(std::string lp_symbol){this->low_player_symbol = lp_symbol;}
void AbstractAffichage::set_high_player_symbol(std::string hp_symbol){this->high_player_symbol = hp_symbol;}
void AbstractAffichage::set_taille_case_hor(int size_hor){this->taille_case_hor = size_hor;}
void AbstractAffichage::set_taille_case_ver(int size_ver){this->taille_case_ver = size_ver;}
