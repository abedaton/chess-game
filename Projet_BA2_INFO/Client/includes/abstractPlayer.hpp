#ifndef ABSTRACTPLAYER_HPP
#define ABSTRACTPLAYER_HPP

#include <string>

class AbstractPlayer{
	public:
		virtual void mov(std::string mov) = 0;
		virtual void win() = 0;
		virtual void lose() = 0;
	
};

#endif
