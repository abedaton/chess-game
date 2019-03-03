
#pragma once
#ifndef CLASSICCHESS_HPP
#define CLASSICCHESS_HPP
//#include <iostream>
//#include <vector>
//#include <string>
//#include <utility>
//#include <sstream>      // std::stringstream
//#include <cmath>

#include "BaseChess/BaseChess.cpp"

class ClassicChess: public BaseChess{
	public:
        ClassicChess(Player*,Player*,Player*,Dico*); //*< Constructor
        ClassicChess() noexcept = default; //*< Constructor
        ~ClassicChess() noexcept = default; //Destructor
        ClassicChess(const ClassicChess&) noexcept = default;
        ClassicChess& operator= (const ClassicChess&) noexcept = default;
        
        std::pair<bool,std::string> execute_step() override;
        std::pair<bool,bool> execute_step(std::string) override;
        std::pair<bool,bool> execute_step(std::string, std::string) override;
		bool check_pat();
        
	protected:
		
		void initialise_board() override;
		void initialise_low_pieces() override;
		void initialise_high_pieces() override;
		
		void affichage() override;
		
		std::pair<bool,BitypeVar<Chesspiece*>> normal_output_check(std::string,std::string) override;
		Trinome<std::string,BitypeVar<Chesspiece*>,Trinome<bool,bool,bool>*>* out_input(std::string,BitypeVar<Chesspiece*>) override;
		
		Trinome<std::string,std::string,bool>* decode_merged_string(std::string);
		bool exec_step(std::string, std::string, BitypeVar<Chesspiece*>, bool, bool);
};
#endif
