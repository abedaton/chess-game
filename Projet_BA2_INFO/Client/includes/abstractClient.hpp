#pragma GCC diagnostic ignored "-Wunused-variable"
#ifndef ABSTRACTCLIENTT_HPP
#define ABSTRACTCLIENTT_HPP

#include "../game/ClassicChess/ClassicChess.cpp"

class AbstractClient{
	public:
		virtual void connectionError() = 0;
		virtual void startingGame(bool playerTurn) = 0;
		virtual void opponentMov(std::string mov) = 0;
		virtual void printMessage(std::string) = 0;
};

#endif
