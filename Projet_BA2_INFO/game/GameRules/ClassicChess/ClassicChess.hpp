
#pragma once
#ifndef CLASSICCHESS_HPP
#define CLASSICCHESS_HPP
//#include <iostream>
//#include <vector>
//#include <string>
//#include <utility>
//#include <sstream>      // std::stringstream
//#include <cmath>

#include "../BaseChess/BaseChess.cpp"

class ClassicChess: public BaseChess{
	public:
        ClassicChess(Player*,Player*,Player*,Dico*,AbstractAffichage*); //*< Constructor
        ClassicChess() noexcept = default; //*< Constructor
        ~ClassicChess() noexcept = default; //Destructor
        ClassicChess(const ClassicChess&) noexcept = default;
        ClassicChess& operator= (const ClassicChess&) noexcept = default;
        
	protected:
		
		void initialise_board() override;
		void initialise_high_pieces() override;
		void initialise_low_pieces() override;
		
		void affichage() override;
		
		std::vector<Chesspiece*>* evolution_possibilities() override;
		std::pair<bool,std::string> execute_step(Player*) override;
		
		std::pair<bool,bool> execute_forced_step(BitypeVar<Trinome<std::string,std::string,bool>*>*,Player*) override;
		
		using BaseChess::execute_forced_step;
		using BaseChess::execute_step;
};
#endif
