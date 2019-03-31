#pragma once
#ifndef ABSTRACTPLAYER_HPP
#define ABSTRACTPLAYER_HPP

#include <string>

class AbstractPlayer{
	public:
		virtual ~AbstractPlayer() = default;
		virtual void mov(std::string mov){(void)mov;}
		virtual void movPossibleUpdate(std::vector<std::pair<int,int> >* listMov){(void*)listMov;}
	
};

#endif
