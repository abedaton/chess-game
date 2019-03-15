#pragma GCC diagnostic ignored "-Wunused-variable"
#ifndef ABSTRACTCLIENTT_HPP
#define ABSTRACTCLIENTT_HPP

#include "../game/Gestion/TourParTour/TourParTour.cpp"
#include "../game/Gestion/Pendule/Pendule.cpp"

class AbstractClient{
	public:
		virtual void connectionError() = 0;
		virtual void startingGame(bool playerTurn) = 0;
		virtual void opponentMov(std::string mov) = 0;
		virtual void printMessage(std::string) = 0;

		virtual bool get_inverted() const = 0;
		virtual void set_inverted(bool) = 0;
		
		virtual bool get_ennemy_inverted() const = 0;
		virtual void set_ennemy_inverted(bool) = 0;
		
		virtual std::string get_ennemy_name() const = 0;
		virtual void set_ennemy_name(std::string) = 0;
};

#endif
