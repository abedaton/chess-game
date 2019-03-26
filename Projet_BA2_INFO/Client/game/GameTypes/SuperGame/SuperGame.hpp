#ifndef A_HPP
#define A_HPP

#include "AbstractPlayer.hpp"
#include "../TourParTour/TourParTour.cpp"
#include "../Pendule/Pendule.cpp"
#include "../TempsReel/TempsReel.cpp"
#include "../../GamePieces/Pieces/Pieces.cpp"


class SuperGame{
	private:
		AbstractPlayer* _client;
		BaseGameType* _game;
		std::string _lastClick = nullptr;
		std::vector<std::string> _ListMov;
		std::vector<std::string> _bufferMov;
		bool _inverted; 

		bool turn(std::string first);

		std::vector<std::string> split(std::string strToSplit);
		

	public:
		
		SuperGame(int gameMod, AbstractPlayer* client, bool myTurn); // constructor
		bool opponentMov(std::string mov);
		bool click(std::string square);
		std::vector<std::string> getListMov();
		Plateau* getBoard();
		std::pair<bool,bool> serverMov(std::string, std::string, bool);
};

#endif
