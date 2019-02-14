#ifndef GAME_HPP
#define GAME_HPP

class User;

#include <string>
class AbstractGame{
	public:
		AbstractGame(User* player1, User* player2){};
		~AbstractGame() = default;
        std::string getMov(std::string str){return "coucou";};
        void mov(std::string str){};
};


#endif