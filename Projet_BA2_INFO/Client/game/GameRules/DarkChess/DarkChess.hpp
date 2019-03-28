
#pragma once
#ifndef DarkChess_HPP
#define DarkChess_HPP
//#include <iostream>
//#include <vector>
//#include <string>
//#include <utility>
//#include <sstream>      // std::stringstream
//#include <cmath>
#include "../../GameAffichages/AffichageDarkChess/AffichageDarkChess.cpp"
#include "../BaseChess/BaseChess.hpp"

class DarkChess : public BaseChess{
	
    private:
		std::vector<std::vector<int>> fog;
		Player* locked_player;

	public:
<<<<<<< HEAD:Projet_BA2_INFO/Client/game/Games/DarkChess/DarkChess.hpp
		DarkChess(Player *, Player *, Player*,Player*, Dico *); //*< Constructor
=======
		DarkChess(Player *, Player *, Player*,Player*, Dico *,AbstractAffichage*); //*< Constructor
>>>>>>> Partie_Serveur:Projet_BA2_INFO/Client/game/GameRules/DarkChess/DarkChess.hpp
		DarkChess() noexcept = default;        //*< Constructor
		~DarkChess() noexcept = default;       // Destructor
		DarkChess(const DarkChess &) noexcept = default;
		DarkChess &operator=(const DarkChess &) noexcept = default;

    protected:
		
		Player* get_real_locked_player() const;
		Player* get_locked_player() const;
		void set_locked_player(Player*);
		
		std::vector<std::vector<int>> get_fog() const;
		void set_fog(std::vector<std::vector<int>>);
    
		void initialise_board() override;
		void initialise_high_pieces() override;
		void initialise_low_pieces() override;
		
		void affichage(Player*);
		void affichage() override;

		void make_fog(Player*);
<<<<<<< HEAD:Projet_BA2_INFO/Client/game/Games/DarkChess/DarkChess.hpp
		std::vector<std::pair<int, int>> *check_all_mov(Chesspiece *);

		std::vector<std::pair<int, int>>* loop_moves(Chesspiece*, std::string);
=======
		
>>>>>>> Partie_Serveur:Projet_BA2_INFO/Client/game/GameRules/DarkChess/DarkChess.hpp

		bool check_non_active_player_king(Chesspiece*) override;
		
		std::vector<Chesspiece*>* evolution_possibilities() override;
		
		bool roc_check_king_position_and_path_danger(MatPosi*,MatPosi*,bool,int,std::vector<MatPosi>*) override;
		
		std::pair<bool, std::string> execute_step(Player*) override;
		
		std::pair<bool, bool> execute_forced_step(BitypeVar<Trinome<std::string,std::string,bool>*>*,Player*) override;
		
		using BaseChess::execute_forced_step;
		using BaseChess::execute_step;
<<<<<<< HEAD:Projet_BA2_INFO/Client/game/Games/DarkChess/DarkChess.hpp
=======
		
		std::vector<std::pair<int, int>>* check_all_mov(Chesspiece *pe);
		std::vector<std::pair<int, int>>* loop_moves(Chesspiece *pe, std::string mode);
>>>>>>> Partie_Serveur:Projet_BA2_INFO/Client/game/GameRules/DarkChess/DarkChess.hpp
};
#endif
