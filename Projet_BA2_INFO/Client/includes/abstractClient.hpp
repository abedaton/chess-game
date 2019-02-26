#pragma GCC diagnostic ignored "-Wunused-variable"
#ifndef ABSTRACTCLIENTT_HPP
#define ABSTRACTCLIENTT_HPP

class AbstractClient{
	public:
		virtual void connectionError() = 0;
		virtual void startingGame(bool playerTurn) = 0;
		virtual void opponentMov(int coord1, int coord2, bool lose) = 0;
		virtual void recvMessage() = 0;
};

#endif
