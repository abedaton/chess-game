//#include <iostream>
//#include <utility>
//#include <sstream>
#include <algorithm>

#include "MatPosi.hpp"

MatPosi::MatPosi(int x,int y) : Posi(x,y) {} //*< Constructor

MatPosi::MatPosi(Paire<int,int> paire) : Posi(paire) {} //*< Constructor

MatPosi::MatPosi(std::string s) : Posi(0,0) {
	
	if (s.length() < 2){throw MyException(&mout,"coordonee string incohérente pour MatPosi!");}
		
	std::string alph = this->get_alphabet();
	
	std::string letter = this->get_letter_part_of_string(s);
	std::size_t colonne = this->get_col_from_string(letter);
	this->set_col(int(colonne));
	
	std::string reste = this->get_number_part_of_string(s);
	int ligne = this->get_lig_from_string(reste);
	
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

Paire<int,int> MatPosi::to_pair(){
	
	Paire<int,int>* res = new Paire<int,int>(this->get_col(),this->get_lig());
	return *res;
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

std::string MatPosi::get_alphabet() const {return "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";}

std::string MatPosi::get_letter_part_of_string(std::string s) const {
	std::string letter = std::string(1, s[0]);
	return letter;
}

std::string MatPosi::get_number_part_of_string(std::string s) const {
	std::string reste = s.substr(1);
	return reste;
}

std::size_t MatPosi::get_col_from_string(std::string letter) const {
	std::size_t colonne = this->get_alphabet().find(letter)%26;
	return colonne;
}

int MatPosi::get_lig_from_string(std::string reste) const {

	if(not(std::all_of(reste.begin(), reste.end(), isdigit))){throw std::invalid_argument("");}
	int ligne = std::stoi(reste) - 1;

	return ligne;
}

bool MatPosi::isvalid_coord(std::string s) const {
	/* fonction calculant si un string s est est une coordonée matricielle valide */
	
	//mout<<"is_valide_coord MatPosi entree: "<<s<<std::endl;

	bool res = false;
	
	if (s.size() >= 2) {
		
		std::string letter = this->get_letter_part_of_string(s);
		std::size_t colonne = this->get_col_from_string(letter);
		
		if (colonne != std::string::npos){
			std::string reste = this->get_number_part_of_string(s);

			//mout<<"is_valide_coord MatPosi reste: "<<reste<<std::endl;

			try {
				int ligne = this->get_lig_from_string(reste);

				//mout<<"is_valide_coord MatPosi conv reste: "<<ligne<<std::endl;

				(void)ligne;
				res = true;
			}
			catch (const std::invalid_argument& ia) {
				(void)ia;
				res = false;
			}
		}
	}
	
	//mout<<"is_valide_coord MatPosi rep: "<<res<<std::endl;

	return res;
}
