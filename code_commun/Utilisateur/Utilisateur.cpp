
#include <iostream>
#include "Utilisateur.hpp"

Utilisateur::Utilisateur() : login(""), nickname(""), amis(nullptr), victoires(0), match(0), historique(nullptr){
	
	std::vector<Utilisateur*>* friend_list = new std::vector<Utilisateur*>();
	this->amis = friend_list;
	
	std::vector<bool>* vect = new std::vector<bool>();
	this->historique = vect;

}

std::ostream& operator <<(std::ostream &s,Utilisateur &c){
	/* affchage d'un Utilisateur */
    s<<"Utilisateur("<<c.get_login()<<"["<<c.get_nickname()<<"]"<<")";
    return s;
}

std::string Utilisateur::get_login() const{
	return this->login;
}

std::string Utilisateur::get_nickname() const{
	return this->nickname;
}

std::vector<Utilisateur*>* Utilisateur::get_amis() const{
	return this->amis;
}

int Utilisateur::get_nb_victoires() const{
	return this->victoires;
}

int Utilisateur::get_nb_match() const{
	return this->match;
}

double Utilisateur::get_score() const{
	return (double(this->victoires)/double(this->match));
}

std::vector<bool>* Utilisateur::get_historique() const{
	return this->historique;
}

void Utilisateur::add_match(bool m){
	this->inc_match();
	if (m){this->inc_victory();}
	this->add_to_hist(m);
}

void Utilisateur::add_amis(Utilisateur* util){
	this->amis->push_back(util);
}

void Utilisateur::remove_amis(Utilisateur* util){
	int i = 0;
	int taille = int(this->amis->size());
	int found = -1;
	while ((i<taille) and (found == -1)){
		if (*((*(this->amis))[i]) == *util){
			found = i;
		}
		i+=1;
	}
	
	if (found != -1){
		this->amis->erase(this->amis->begin()+i-1);
	}
}

void Utilisateur::set_login(std::string s){
	this->login = s;
}
void Utilisateur::set_nickname(std::string s){
	this->nickname = s;
}

bool Utilisateur::operator==( const Utilisateur& util ) const {
	return (util.get_login() == this->get_login());
}

bool Utilisateur::operator!=( const Utilisateur& util ) const {
	return not(*this == util);
}

void Utilisateur::inc_match(){
	this->match += 1;
}
	
void Utilisateur::inc_victory(){
	this->victoires += 1;
}
	
void Utilisateur::add_to_hist(bool b){
	this->historique->push_back(b);
}
