
#pragma once
#ifndef BASEGAMETYPE_HPP
#define BASEGAMETYPE_HPP

#include "../../GameRules/AntiChess/AntiChess.cpp"
#include "../../GameRules/ClassicChess/ClassicChess.cpp"
#include "../../GameRules/DarkChess/DarkChess.cpp"
#include "../../GameRules/TrappistChess/TrappistChess.cpp"
#include "../../GamePieces/Pieces/Pieces.hpp"

class BaseGameType {
	
	private:
		BaseChess* game;
	
	public:
        BaseGameType(BaseChess*); //*< Constructor
        BaseGameType() noexcept = default; //*< Constructor
        virtual ~BaseGameType() noexcept = default; //Destructor
        BaseGameType(const BaseGameType&) noexcept = default;
        BaseGameType& operator= (const BaseGameType&) noexcept = default;
        
        virtual std::pair<bool,std::string> execute_step();
        virtual std::pair<bool,bool> execute_step(std::string,std::string,bool);
        virtual std::pair<bool,bool> execute_step(std::string,std::string);
        BaseChess* get_game() const;
        Plateau* get_plateau() const;
        bool is_high_active() const;

        std::pair<int,int> str_mov_to_int(std::string);
        
	protected:
        void set_game(BaseChess*);
        void change_active_player();

};
#endif
