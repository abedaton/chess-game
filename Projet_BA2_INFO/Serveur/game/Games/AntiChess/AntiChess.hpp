
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
	private:

		unsigned int cnt_low = 0;
		unsigned int cnt_high = 0;

	public:
        AntiChess(Player*,Player*,Player*,Dico*); //*< Constructor
        AntiChess() noexcept = default; //*< Constructor
        ~AntiChess() noexcept = default; //Destructor
        AntiChess(const AntiChess&) noexcept = default;
        AntiChess& operator= (const AntiChess&) noexcept = default;
        
	protected:
		
		void initialise_board() override;
		void initialise_high_pieces() override;
		void initialise_low_pieces() override;
		
		void affichage() override;
		
		bool verify_kings() override;
		bool check_non_active_player_king(Chesspiece*) override;
		
		std::vector<Chesspiece*>* evolution_possibilities() override;
		
		std::string get_affichage_pat() const override;
		
		bool check_roc_accept(BitypeVar<Chesspiece*>) const override;
		
		// detection de fin de partie
		bool verify_all_eaten() override;
		
		
		// verif de capture obligatoire
		bool is_forced_to_cap();
		std::string get_move_mode(std::string);
		bool check_illegal_move(std::string,std::string) override;
		
		std::pair<bool,std::string> execute_step(Player*) override;
		
		std::pair<bool,bool> execute_forced_step(BitypeVar<Trinome<std::string,std::string,bool>*>*,Player*) override;
		
		using BaseChess::execute_forced_step;
		using BaseChess::execute_step;
};
#endif
