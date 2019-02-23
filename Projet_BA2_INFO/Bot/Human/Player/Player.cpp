
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

void Player::set_name(std::string nom){
	this->name = nom;
}

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

void Player::send_msg(std::string msg,bool endline){
	
	
	std::string nom_play = this->get_name();
	(void)nom_play;
	
	std::string res_msg = msg_compaction(msg,endline);
	
	mout<<res_msg;
		
}

void Player::send_msg(std::string msg){
	this->send_msg(msg,false);	
}

std::string Player::recieve_msg(){
	
	std::string msg = this->next_input();
	mout.log_only(msg,true);
	
	return msg;

}

void Player::send_confirm_msg(std::string msg,bool endline){
	
	std::string res_msg = this->msg_compaction(msg,endline);
	(void)res_msg;
	
}

void Player::send_confirm_msg(std::string msg){
	this->send_confirm_msg(msg,false);	
}

void Player::send_error_msg(){ // a redefinir plustard
	
	bool nothing = true;
	(void)nothing;
	
}

std::string Player::msg_compaction(std::string msg,bool endline){
	
	std::stringstream ss;
	
	ss<<msg;
	if (endline == true){ss<<std::endl;}
	
	return ss.str();
}
