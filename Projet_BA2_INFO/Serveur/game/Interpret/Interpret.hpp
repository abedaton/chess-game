/*
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
*/

#pragma once
#ifndef INTERPRET_HPP
#define INTERPRET_HPP

#include "Dico/Dico.cpp"

class Interpret{
	/* classe crée dans le but d'instantanément pouvoir changer la langue du texte,
	 * cette classe stocke des commandes qu'elle peut executer lorsqu'on lui demande,
	 * puisque le texte n'est pas préposs et lors de chaque demande les commandes sont a nouveau lue
	 * des changements peuvent avoir eu lieu */
	private:
		Dico* dico;
		std::vector<Trinome<std::string,bool,bool>*>* text_list;
		
	public:
        Interpret(Dico*); //*< Constructor
        ~Interpret() noexcept = default; //Destructor
        Interpret(const Interpret&) noexcept = default;
        Interpret& operator= (const Interpret&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,Interpret &c);
        friend std::ostream& operator<< (std::ostream &s,Interpret* c);
        
        Dico* get_dico();
        
        void add_text(std::string,bool,bool);
        std::string get_text(std::string);

};
#endif
