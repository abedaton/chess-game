
#pragma once
#ifndef TRAPPISTCHESS_HPP
#define TRAPPISTCHESS_HPP
//#include <iostream>
//#include <vector>
//#include <string>
//#include <utility>
//#include <sstream>      // std::stringstream
//#include <cmath>

#include "../BaseChess/BaseChess.hpp"

class TrappistChess: public BaseChess{
	public:
        TrappistChess(Player*,Player*,Player*,Dico*); //*< Constructor
        TrappistChess() noexcept = default; //*< Constructor
        ~TrappistChess() noexcept = default; //Destructor
        TrappistChess(const TrappistChess&) noexcept = default;
        TrappistChess& operator= (const TrappistChess&) noexcept = default;
        
        std::pair<bool,std::string> execute_step() override;
        std::pair<bool,bool> execute_step(BitypeVar<Trinome<std::string,std::string,bool>*>*) override;
        using BaseChess::execute_step;
        
	protected:
		
		void initialise_board() override;
		void initialise_high_pieces() override;
		void initialise_low_pieces() override;
		
		void affichage() override;
		
		std::vector<Chesspiece*>* evolution_possibilities() override;
		
		int get_evolution_row(Player*) override;
		
		bool check_roc_accept(BitypeVar<Chesspiece*>) const override;
};
#endif
