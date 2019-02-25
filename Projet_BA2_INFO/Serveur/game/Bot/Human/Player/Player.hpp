
#pragma once
#ifndef PLAYER_HPP
#define PLAYER_HPP
//#include <iostream>
//#include <string>
//#include <sstream>      // std::stringstream

#include "../../../AdvTuple/AdvTuple.cpp"

class Player{
    private:
		std::string name;
	
	public:
        Player(std::string); //*< Constructor
        Player() noexcept = default; //*< Constructor
        virtual ~Player() noexcept = default; //Destructor
        Player(const Player&);
        Player& operator= (const Player&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,Player &c);
        friend std::ostream& operator<< (std::ostream &s,Player* c);
        
        std::string get_name() const;
        void set_name(std::string);
        
        virtual std::string next_input() = 0;
        
        bool operator==( const Player&) const;
        bool operator!=( const Player&) const;
        
        bool operator==(const Player*) const;
        bool operator!=(const Player*) const;
        
        virtual void send_msg(std::string,bool);
        virtual void send_msg(std::string);
        virtual std::string recieve_msg();
        
        virtual void send_confirm_msg(std::string,bool);
        virtual void send_confirm_msg(std::string);
        
        virtual void send_error_msg();
        
    private:
		virtual std::string get_type_prefix() const;
		
	protected:
		std::string msg_compaction(std::string,bool);
};
#endif
