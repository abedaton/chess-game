#include "Posi.hpp"


Posi::Posi(int x,int y) : x(x), y(y){} //*< Constructor

Posi::Posi(std::pair<int,int> paire) : x(paire.first), y(paire.second){} //*< Constructor

std::ostream& operator <<(std::ostream &s,Posi &c){
	/* affchage d'un Posi */
    s<<"Posi("<<"x:"<<c.get_x()<<" ,y:"<<c.get_y()<<")";
    return s;
}

std::ostream& operator <<(std::ostream &s,Posi* c){
	/* affchage d'un Posi */
    s<<(*c);
    return s;
}

int Posi::get_x() const{
	return this->x;
}

int Posi::get_y() const{
	return this->y;
}

void Posi::set_x(int x){
	this->x = x;
}

void Posi::set_y(int y){
	this->y = y;
}

bool Posi::operator==( const Posi& p ) const {
	return (p.get_x() == this->get_x()) and (p.get_y() == this->get_y());
}

bool Posi::operator!=( const Posi& p ) const {
	return not(*this == p);
}

bool Posi::operator==( const Posi* p ) const {
	return (*p == *this);
}

bool Posi::operator!=( const Posi* p ) const {
	return (*this != *p);
}
