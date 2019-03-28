#pragma once

#include "AffichageDarkChess.hpp"

//AffichageDarkChess::AffichageDarkChess(Plateau* plat, Dico* dict, std::string pre, std::string suf, std::string lang, Player* play_low, Player* play_high,std::string symb_low, std::string symb_high, std::vector<std::vector<int>> foggy) : Affichage(plat, dict, pre, suf, lang, play_low, play_high, symb_low, symb_high), fog(foggy){} //*< Constructor

AffichageDarkChess::AffichageDarkChess() : Affichage(), fog((*(new std::vector<std::vector<int>>()))), locked_player(nullptr) {} //*< Constructor


std::vector<std::vector<int>> AffichageDarkChess::get_fog() const {return this->fog;}

std::string AffichageDarkChess::get_affichage_line(int i, int new_i){

    std::stringstream s;
    
    std::string fog_symbol = "X";

    for (long long unsigned int j = 0; j < (this->get_plateau()->get_row(i)).size(); j++){

        std::stringstream ss;

        BitypeVar<Chesspiece*> elem = (this->get_plateau()->get_row(new_i))[j];
        Chesspiece *piece = elem.get_var();
      
        if (this->get_fog()[j][new_i] == 1){ss << fog_symbol;}
        else if (elem.get_state() == true){

            std::stringstream temp_ss;
            temp_ss << this->get_dico_prefix() << (*piece) << this->get_dico_suffix();

            if (this->get_dico() != nullptr){ss << this->get_dico()->search(this->get_dico_language(), temp_ss.str());}
            else{ss << temp_ss.str();}

            ss << this->get_player_symbol(piece->get_owner());
        }

        else{ss << " ";}

        std::string str_elem;
        str_elem = ss.str();
        int elem_size = int(str_elem.length());
        int taille_reste = this->get_taille_case_hor() - elem_size;
        int hor_av = taille_reste / 2;
        int hor_ap = taille_reste - hor_av;

        for (int m = 0; m < hor_av; m++){s << " ";}

        if (this->get_fog()[j][new_i] == 1){s << fog_symbol;}
        else if (elem.get_state() == true){

            std::stringstream temp_s;
            temp_s << this->get_dico_prefix() << (*piece) << this->get_dico_suffix();

            if (this->get_dico() != nullptr){s << this->get_dico()->search(this->get_dico_language(), temp_s.str());}
            else{s << temp_s.str();}

            s << this->get_player_symbol(piece->get_owner());
        }
        else{s << " ";}

        for (int n = 0; n < hor_ap; n++){s << " ";}

        s << "|";
    }

    return s.str();
}

Player* AffichageDarkChess::get_locked_player() const {return this->locked_player;}
void AffichageDarkChess::set_locked_player(Player* locked_play){this->locked_player = locked_play;}
void AffichageDarkChess::set_fog(std::vector<std::vector<int>> foggy){this->fog = foggy;}
