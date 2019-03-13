#pragma once
#ifndef GAME_INTEL_HPP
#define GAME_INTEL_HPP
#include <iostream>
#include <utility>

#include "../Gestion/TourParTour/TourParTour.cpp"
#include "../Gestion/Pendule/Pendule.cpp"

class GameIntelligence{
	
	private:
		TourParTour* game;
	
	private:
		void make_game(std::string,Player*, Player*);
		TourParTour* get_game() const;
        void set_game(TourParTour*);
	
	public:
        GameIntelligence() noexcept = default; //*< Constructor
        ~GameIntelligence() noexcept = default; //Destructor
        GameIntelligence(const GameIntelligence&) noexcept = default;
        GameIntelligence& operator= (const GameIntelligence&) noexcept = default;
        
        void make_game_human_and_bot(std::string,std::string,std::string);
        void make_game_two_bots(std::string,std::string,std::string);
        void make_game_two_humans(std::string,std::string);
        void make_game_two_silenced_humans(std::string,std::string);
        
        
        void execute_game();
};
#endif
