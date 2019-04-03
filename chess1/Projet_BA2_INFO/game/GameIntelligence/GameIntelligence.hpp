#pragma once
#ifndef GAME_INTEL_HPP
#define GAME_INTEL_HPP
#include <iostream>
#include <utility>

#include "../GameTypes/TourParTour/TourParTour.cpp"
#include "../GameTypes/Pendule/Pendule.cpp"
#include "../GameTypes/TempsReel/TempsReel.cpp"

class GameIntelligence{
	
	private:
		BaseGameType* game;
	
	private:
		void make_game(std::string,std::string,Player*, Player*);
		BaseGameType* get_game() const;
        void set_game(BaseGameType*);
	
	public:
        GameIntelligence() noexcept = default; //*< Constructor
        ~GameIntelligence() noexcept = default; //Destructor
        GameIntelligence(const GameIntelligence&) noexcept = default;
        GameIntelligence& operator= (const GameIntelligence&) noexcept = default;
        
        void make_game_human_and_bot(std::string,std::string,std::string,std::string);
        void make_game_two_bots(std::string,std::string,std::string,std::string);
        void make_game_two_humans(std::string,std::string,std::string);
        void make_game_two_silenced_humans(std::string,std::string,std::string);
        
        
        void execute_game();
};
#endif
