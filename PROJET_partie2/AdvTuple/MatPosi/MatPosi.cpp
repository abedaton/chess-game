#include <iostream>
#include <utility>
#include <sstream>
#include "MatPosi.hpp"


MatPosi::MatPosi(int x,int y) : Posi(x,y) {} //*< Constructor

MatPosi::MatPosi(std::pair<int,int> paire) : Posi(paire) {} //*< Constructor

MatPosi::MatPosi(std::string s) : Posi(0,0) {
		
	std::string alph = this->get_alphabet();
	
	std::string letter = std::string(1, s[0]); //zero
	
	std::size_t colonne = alph.find(letter);
	this->set_col(int(colonne));
	
	std::string reste = s.substr(1);
	int ligne = std::stoi(reste) - 1;
	this->set_lig(ligne);
	
} //*< Constructor

MatPosi::MatPosi(const Posi& p) : Posi(p) {}

std::ostream& operator <<(std::ostream &s,MatPosi &c){
	/* affchage d'un MatPosi */
    s<<"MatPosi("<<"col:"<<c.get_col()<<" ,lig:"<<c.get_lig()<<")";
    return s;
}

std::ostream& operator <<(std::ostream &s,MatPosi* c){
	/* affchage d'un MatPosi */
    s<<(*c);
    return s;
}

int MatPosi::get_col() const{
	return this->get_x();
}

int MatPosi::get_lig() const{
	return this->get_y();
}

void MatPosi::set_col(int x){
	this->set_x(x);
}

void MatPosi::set_lig(int y){
	this->set_y(y);
}

std::string MatPosi::to_string(){
	
	std::string alph = this->get_alphabet();
	
	int colonne = this->get_col();
	int ligne = this->get_lig();
	
	std::string str_col = std::string(1, alph[colonne]); 
	std::string str_lig = std::to_string(ligne+1);
	
	std::stringstream ss;
	ss << str_col << str_lig;
	
	std::string res = ss.str();
	
	return res;
}

std::pair<int,int> MatPosi::to_pair(){
	
	std::pair<int,int> res = std::make_pair(this->get_col(),this->get_lig());
	return res;
}

bool MatPosi::operator<( const MatPosi& mp ) const {
	bool res = false;
	if (this->get_lig() < mp.get_lig()){res = true;}
	else if (this->get_lig() == mp.get_lig()){
		if (this->get_col() < mp.get_col()){res = true;}
	}
	
	return res;
}

bool MatPosi::operator<=( const MatPosi& mp ) const {	
	return (*this < mp or *this == mp);
}

bool MatPosi::operator>( const MatPosi& mp ) const {
	return (*this != mp and not(*this < mp));
}

bool MatPosi::operator>=( const MatPosi& mp ) const {
	return (*this > mp or *this == mp);
}


bool MatPosi::operator<( const MatPosi* mp ) const {
	return (*this < *mp);
}

bool MatPosi::operator<=( const MatPosi* mp ) const {	
	return (*this <= *mp);
}

bool MatPosi::operator>( const MatPosi* mp ) const {
	return (*this > *mp);
}

bool MatPosi::operator>=( const MatPosi* mp ) const {
	return (*this >= *mp);
}

std::string MatPosi::get_alphabet(){return "ABCDEFGHIJKLMNPQRSTUVWXYZ";}
