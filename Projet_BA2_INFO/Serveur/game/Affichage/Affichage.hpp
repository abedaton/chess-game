
#pragma once
#ifndef AFFICHAGE_HPP
#define AFFICHAGE_HPP
#include <iostream>
#include <string>
#include <sstream>      // std::stringstream

#include "../Plateau/Plateau.cpp"

std::string make_ligne(std::string, int, int);
std::string crea_ligne_lettres(int,int);

class Affichage{
    private:
		
		Plateau* plateau;
		Dico* dico;
		std::string dico_prefix;
		std::string dico_suffix;
		std::string dico_language;
		Player* low_player;
		Player* high_player;
		std::string low_player_symbol;
		std::string high_player_symbol;
		int taille_case_hor;
		int taille_case_ver;
	
	public:
        Affichage(Plateau*, Dico*,std::string,std::string,std::string,Player*,Player*,std::string,std::string); //*< Constructor
        Affichage() noexcept = default; //*< Constructor
        virtual ~Affichage() noexcept = default; //Destructor
        Affichage(const Affichage&) noexcept = default;
        Affichage& operator= (const Affichage&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,Affichage &c);
        friend std::ostream& operator<< (std::ostream &s,Affichage* c);
        
        std::string get_affichage();
        
    protected:
		Plateau* get_plateau();
        Dico* get_dico();
		std::string get_dico_prefix();
		std::string get_dico_suffix();
		std::string get_dico_language();
		Player* get_low_player();
		Player* get_high_player();
		std::string get_low_player_symbol();
		std::string get_high_player_symbol();
		int get_taille_case_hor();
		int get_taille_case_ver();
    
		std::string get_player_symbol(Player*);
        std::string affichage_player(Player*);
        std::string make_big_ligne();
        std::string make_big_ligne_vide();
        
        virtual std::string get_affichage_line(int, int);
        
        std::string affichage_plateau();
        
};
#endif
