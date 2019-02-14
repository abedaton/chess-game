
#include "Player.hpp"


Player::Player(std::string s) : name(s){} //*< Constructor

std::ostream& operator <<(std::ostream &s,Player &c){
	/* affchage d'un Player */
    s<<c.get_type_prefix()<<"("<<c.get_name()<<")";
    return s;
}

std::ostream& operator <<(std::ostream &s,Player* c){
	/* affchage d'un Player */
    s<<(*c);
    return s;
}

Player::Player(const Player& play): name(play.get_name()) {}

std::string Player::get_name() const {return this->name;}

bool Player::operator==( const Player& p ) const {
	return (p.get_name() == this->get_name());
}

bool Player::operator!=( const Player& p ) const {
	return not(*this == p);
}

bool Player::operator==( const Player* p ) const {
	return (*p == *this);
}

bool Player::operator!=( const Player* p ) const {
	return (*p != *this);
}

std::string Player::get_type_prefix() const{
	return "Player";
}
