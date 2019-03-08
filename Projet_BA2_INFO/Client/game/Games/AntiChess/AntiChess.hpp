
#pragma once
#ifndef ANTICHESS_HPP
#define ANTICHESS_HPP
//#include <iostream>
//#include <vector>
//#include <string>
//#include <utility>
//#include <sstream>      // std::stringstream
//#include <cmath>

#include "../BaseChess/BaseChess.cpp"

class AntiChess: public BaseChess{
	public:
        AntiChess(Player*,Player*,Player*,Dico*); //*< Constructor
        AntiChess() noexcept = default; //*< Constructor
        ~AntiChess() noexcept = default; //Destructor
        AntiChess(const AntiChess&) noexcept = default;
        AntiChess& operator= (const AntiChess&) noexcept = default;
        
        std::pair<bool,std::string> execute_step() override;
        std::pair<bool,bool> execute_step(BitypeVar<Trinome<std::string,std::string,bool>*>*) override;
        using BaseChess::execute_step;
        
	protected:
		
		void initialise_board() override;
		void initialise_high_pieces() override;
		void initialise_low_pieces() override;
		
		void affichage() override;
		
		std::pair<bool,BitypeVar<Chesspiece*>> normal_output_check(std::string,std::string) override;
		Trinome<std::string,BitypeVar<Chesspiece*>,Trinome<bool,bool,bool>*>* out_input(std::string,BitypeVar<Chesspiece*>) override;
		
		bool exec_step(std::string, std::string, BitypeVar<Chesspiece*>, bool, bool);
		
		bool check_pat();
		
		virtual bool verify_kings() override;
		bool check_non_active_player_king(Chesspiece*) override;
		
		std::vector<Chesspiece*>* evolution_possibilities() override;
		
};
#endif
