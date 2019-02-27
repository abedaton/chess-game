#pragma once
#ifndef GAME_INTEL_HPP
#define GAME_INTEL_HPP
#include <iostream>
#include <utility>

#include "../ClassicChess/ClassicChess.cpp"

class GameIntelligence{
	
	private:
		BaseChess* game;
	
	private:
		void make_classic_game(Player*, Player*, std::string);
		BaseChess* get_game() const;
        void set_game(BaseChess*);
	
	public:
        GameIntelligence() noexcept = default; //*< Constructor
        ~GameIntelligence() noexcept = default; //Destructor
        GameIntelligence(const GameIntelligence&) noexcept = default;
        GameIntelligence& operator= (const GameIntelligence&) noexcept = default;
        
        void make_classic_game_human_and_bot(std::string,std::string);
        void make_classic_game_two_bots(std::string,std::string,std::string);
        void make_classic_game_two_humans(std::string);
        void make_classic_game_two_humanservs(std::string);
        
        void execute_game();
};
#endif
