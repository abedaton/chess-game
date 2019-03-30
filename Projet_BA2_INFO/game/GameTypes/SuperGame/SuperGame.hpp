#pragma once
#ifndef SUPERGAME_HPP
#define SUPERGAME_HPP

#include "AbstractPlayer.hpp"
#include "../TourParTour/TourParTour.cpp"
#include "../Pendule/Pendule.cpp"
#include "../TempsReel/TempsReel.cpp"
#include "../../GamePieces/Pieces/Pieces.cpp"


class SuperGame{ 
	private:
		AbstractPlayer* _client;
		BaseGameType* _game;
		std::string _lastClick = " ";
		std::vector<std::string> _ListMov;
		std::vector<std::string> _bufferMov;
		bool _inverted;
		std::string _player1;
		std::string _player2;

		bool turn(std::string first);

		//std::vector<std::string> split(std::string strToSplit);
		

	public:
		
		SuperGame(int gameMod, AbstractPlayer* client, bool myTurn, Player* player1, Player* player2); // constructor
		bool click(std::string square);
		int opponentMov(std::string mov);
		std::pair<bool,bool> serverMov(std::string, std::string, bool);
		//std::vector<std::string> getListMov();
		//Plateau* getBoard();
};

#endif
