
#pragma once
#ifndef INTERPRET_CPP
#define INTERPRET_CPP
#include "Interpret.hpp"

// ------------Interpret--------------------------------------------------------------------------------------------

Interpret::Interpret(Dico* dict) : dico(dict), text_list(nullptr) {
	
	std::vector<Trinome<std::string,bool,bool>*>* vect = new std::vector<Trinome<std::string,bool,bool>*>();
	
	this->text_list = vect;
	
} //*< Constructor

std::ostream& operator <<(std::ostream &s,Interpret &c){
	/* affchage d'un Interpret */
	(void)c;
    s<<"Interpret()";
    return s;
}

std::ostream& operator <<(std::ostream &s,Interpret* c){
	/* affchage d'un Interpret */
    s<<(*c);
    return s;
}

Dico* Interpret::get_dico(){return this->dico;}

void Interpret::add_text(std::string text, bool endline, bool is_dict_tag){
	/* fonction qui permet d'ajouter une commande a cet Interpret qui sera lue lors de la demande de texte */
	
	Trinome<std::string,bool,bool>* trinome = new Trinome<std::string,bool,bool>(text,endline,is_dict_tag);
	this->text_list->push_back(trinome);
	
}

std::string Interpret::get_text(std::string langue){
	/* fonction qui récupère le texte de tout les commandes envoyer a cet Interpret */
	
	std::vector<Trinome<std::string,bool,bool>*>* vect = this->text_list;
	
	std::stringstream ss;
	
	for(long long unsigned int i=0;i<vect->size();i++){
		
		Trinome<std::string,bool,bool>* trinome = (*vect)[i];
		
		if (trinome->get_third() == true){ss<<this->get_dico()->search(langue,trinome->get_first());} // c'est un tag
		else{ss<<trinome->get_first();}
		if (trinome->get_second() == true){ss<<std::endl;}

	}
	return ss.str();
}

#endif