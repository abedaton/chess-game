
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
        std::pair<bool,bool> execute_step(std::string) override;
        using BaseChess::execute_step;
        
	protected:
		
		void initialise_board() override;
		void initialise_high_pieces() override;
		void initialise_low_pieces() override;
		
		void affichage() override;
		
		std::pair<bool,BitypeVar<Chesspiece*>> normal_output_check(std::string,std::string) override;
		Trinome<std::string,BitypeVar<Chesspiece*>,Trinome<bool,bool,bool>*>* out_input(std::string,BitypeVar<Chesspiece*>) override;
		
		Trinome<std::string,std::string,bool>* decode_merged_string(std::string);
		bool exec_step(std::string, std::string, BitypeVar<Chesspiece*>, bool, bool);
		bool check_pat();
};
#endif
