
#pragma once
#ifndef ABSTRACTAFFICHAGE_HPP
#define ABSTRACTAFFICHAGE_HPP
#include <iostream>
#include <string>
#include <sstream>      // std::stringstream

#include "../../../Plateau/Plateau.cpp"

class AbstractAffichage{
    private:
		
		Plateau* plateau;
		Dico* dico;
		std::string dico_prefix;
		std::string dico_suffix;
		std::string dico_language;
		Player* low_player;
		Player* high_player;
		Player* active_player;
		std::string low_player_symbol;
		std::string high_player_symbol;
		int taille_case_hor;
		int taille_case_ver;
	
	public:
        //AbstractAffichage(Plateau*, Dico*,std::string,std::string,std::string,Player*,Player*,Player*,std::string,std::string); //*< Constructor
        //AbstractAffichage(Plateau*, Dico*,std::string,std::string,std::string,Player*,Player*,Player*,std::string,std::string,int,int); //*< Constructor
        AbstractAffichage(); //*< Constructor //noexcept = default
        virtual ~AbstractAffichage() noexcept = default; //Destructor
        AbstractAffichage(const AbstractAffichage&) noexcept = default;
        AbstractAffichage& operator= (const AbstractAffichage&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,AbstractAffichage &c);
        friend std::ostream& operator<< (std::ostream &s,AbstractAffichage* c);
        
        virtual void show() = 0;
        
        void set_plateau(Plateau*);
        void set_dico(Dico*);
		void set_dico_prefix(std::string);
		void set_dico_suffix(std::string);
		void set_dico_language(std::string);
		void set_low_player(Player*);
		void set_high_player(Player*);
		void set_active_player(Player*);
		void set_low_player_symbol(std::string);
		void set_high_player_symbol(std::string);
		void set_taille_case_hor(int);
		void set_taille_case_ver(int);
        
    protected:
		Plateau* get_plateau() const;
        Dico* get_dico() const;
		std::string get_dico_prefix() const;
		std::string get_dico_suffix() const;
		std::string get_dico_language() const;
		Player* get_low_player() const;
		Player* get_high_player() const;
		Player* get_active_player() const;
		std::string get_low_player_symbol() const;
		std::string get_high_player_symbol() const;
		int get_taille_case_hor() const;
		int get_taille_case_ver() const;
    
		std::string get_player_symbol(Player*);
        
};
#endif
