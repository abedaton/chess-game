
#pragma once
#ifndef AFFICHAGE_HPP
#define AFFICHAGE_HPP

#include "AbstractAffichage/AbstractAffichage.cpp"

std::string make_ligne(std::string, int, int);
std::string crea_ligne_lettres(int,int);

class Affichage: public AbstractAffichage{	
	public:
        //Affichage(Plateau*, Dico*,std::string,std::string,std::string,Player*,Player*,Player*,std::string,std::string); //*< Constructor
        //Affichage(Plateau*, Dico*,std::string,std::string,std::string,Player*,Player*,Player*,std::string,std::string,int,int); //*< Constructor
        Affichage(); //*< Constructor //  noexcept = default
        virtual ~Affichage() noexcept = default; //Destructor
        Affichage(const Affichage&) noexcept = default;
        Affichage& operator= (const Affichage&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,Affichage &c);
        friend std::ostream& operator<< (std::ostream &s,Affichage* c);
        
        std::string get_affichage();
        
        void show() override;
        
    protected:
        std::string affichage_player(Player*);
        std::string make_big_ligne();
        std::string make_big_ligne_vide();
        
        virtual std::string get_affichage_line(int, int);
        
        std::string affichage_plateau();
        
};
#endif
