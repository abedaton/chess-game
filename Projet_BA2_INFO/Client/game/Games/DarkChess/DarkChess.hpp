
#pragma once
#ifndef DarkChess_HPP
#define DarkChess_HPP
//#include <iostream>
//#include <vector>
//#include <string>
//#include <utility>
//#include <sstream>      // std::stringstream
//#include <cmath>
#include "../../AffichageDarkChess/AffichageDarkChess.cpp"
#include "../BaseChess/BaseChess.hpp"

class DarkChess : public BaseChess{
	
    private:
		std::vector<std::vector<int>> fog;

	public:
		DarkChess(Player *, Player *, Player*, Dico *); //*< Constructor
		DarkChess() noexcept = default;        //*< Constructor
		~DarkChess() noexcept = default;       // Destructor
		DarkChess(const DarkChess &) noexcept = default;
		DarkChess &operator=(const DarkChess &) noexcept = default;

    protected:
		
		std::vector<std::vector<int>> get_fog() const;
		void set_fog(std::vector<std::vector<int>>);
    
		void initialise_board() override;
		void initialise_high_pieces() override;
		void initialise_low_pieces() override;

		void affichage() override;

		void make_fog();
		std::vector<std::pair<int, int>> *check_all_mov(Chesspiece *);

		std::vector<std::pair<int, int>>* loop_moves(Chesspiece*, std::string);

		bool check_non_active_player_king(Chesspiece*) override;
		
		std::vector<Chesspiece*>* evolution_possibilities() override;
		
		bool roc_check_king_position_and_path_danger(MatPosi*,MatPosi*,bool,int,std::vector<MatPosi>*) override;
		
		std::pair<bool, std::string> execute_step(Player*) override;
		
		std::pair<bool, bool> execute_forced_step(BitypeVar<Trinome<std::string,std::string,bool>*>*,Player*) override;
		
		using BaseChess::execute_forced_step;
		using BaseChess::execute_step;
};
#endif
