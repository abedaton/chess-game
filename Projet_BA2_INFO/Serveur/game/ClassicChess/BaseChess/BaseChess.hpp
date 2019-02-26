
#pragma once
#ifndef BASECHESS_HPP
#define BASECHESS_HPP
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <sstream>      // std::stringstream
#include <cmath>

#include "../../Affichage/Affichage.cpp"

template <typename Type>
bool verifier_type_pe(BitypeVar<Chesspiece*> adv_pe){
	/* fonction permettant de définir si la piece (pouvant être None) donnée est du type donnée par le template */
	Chesspiece* pe;
	bool res = false;
	
	if (adv_pe.get_state() != false){
		pe = adv_pe.get_var();
		res = verifier_type_pe<Type>(pe);
		
	}
		
	return res;
}

template <typename Type>
bool verifier_type_pe(Chesspiece* pe){
	/* fonction permettant de définir si la piece donnée est du type donnée par le template */
	bool res;

	if(Type* v = dynamic_cast<Type*>(pe)){
		(void)v; // enlever warning
		res = true;
	}
		
	else{res = false;}
	
	return res;
}

bool check_end_game(BitypeVar<Chesspiece*>, bool);

BitypeVar<int>* detect_ennemy_pion_in_vect(std::vector<BitypeVar<Chesspiece*>>, Player*);

BitypeVar<Chesspiece*>* select_king(std::vector<Chesspiece*>*,Player*);

BitypeVar<std::pair<int,int>>* calculate_move_between_zones(MatPosi*, MatPosi*);

std::pair<int,int> calc_roc_destinations(bool, std::vector<MatPosi>*);

std::vector<MatPosi*>* calc_king_move_path(bool, int, std::vector<MatPosi>*);

std::pair<MatPosi*,MatPosi*> sort_two_mpos(MatPosi*, MatPosi*);

BitypeVar<std::vector<MatPosi>*>* calc_zones_between_zones(MatPosi*, MatPosi*, Player*);

class BaseChess{
    private:
		Plateau* plateau;
		Player* low_player;
		Player* high_player;
		Player* active_player;
		Dico* dico;
		std::string langue;

	public:
        BaseChess(Player*,Player*,Dico*,std::string); //*< Constructor
        BaseChess() noexcept = default; //*< Constructor
        virtual ~BaseChess() noexcept = default; //Destructor
        BaseChess(const BaseChess&) noexcept = default;
        BaseChess& operator= (const BaseChess&) noexcept = default;
        
        // pas d'interactions avec le jeu, il gère tout --> peu de fonctions publiques
        virtual bool execute_step() = 0;
        
	protected:
		Player* get_low_player();
		Player* get_high_player();
		Player* get_other_player(Player*);
		Player* get_active_player();
		Player* get_non_active_player();
		
		void set_active_player(Player*);
		void set_low_player(Player*);
		void set_high_player(Player*);
		
		int get_player_row(Player*);
		
		Plateau* get_plateau();
		void set_plateau(Plateau*);
		
		Dico* get_dico();
		
		std::string get_langue();
		void set_langue(std::string);
		
		void initial_set_piece(Chesspiece*,Player*,std::string);
		void initialisation();
		virtual void initialise_board() = 0;
		virtual void initialise_low_pieces() = 0;
		virtual void initialise_high_pieces() = 0;
		
		void show_bitype_vect(std::vector<BitypeVar<Chesspiece*>>);
		BitypeVar<std::vector<MatPosi>*>* calculate_zones_between_zones(MatPosi*, MatPosi*);
		
		void changement_langue_input();
		Trinome<bool,bool,bool>* check_in_for_special_symbol(std::string,bool);
		Trinome<Quadrinome<bool,bool,bool,bool>*, BitypeVar<Chesspiece*>, std::string > check_out_for_special_symbol(BitypeVar<Chesspiece*>, std::string,bool);
		
		Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* in_input(Interpret*,Interpret*,Interpret*,bool);
		Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* in_input(Interpret*,Interpret*,Interpret*);
		Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* in_depl_input();
		Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* in_roc_input();
		
		bool check_illegal_move(std::string,std::string);
		
		virtual std::pair<bool,BitypeVar<Chesspiece*>> normal_output_check(std::string,std::string) = 0;
		
		bool verify_possible_roc(Roi*,Tour*);
		
		Trinome<Trinome<bool,bool,bool>*,BitypeVar<Chesspiece*>,std::string>* roc_first_pe_is_waiting(Chesspiece* pe);

		Trinome<Trinome<bool,bool,bool>*,BitypeVar<Chesspiece*>,std::string>* roc_output_check(BitypeVar<Chesspiece*>);
		virtual Trinome<std::string,BitypeVar<Chesspiece*>,Trinome<bool,bool,bool>*>* out_input(std::string,BitypeVar<Chesspiece*>) = 0;
		
		void show_depl_possibles(Chesspiece*);
		void show_depl_possibles(std::string);
		
		Trinome<std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<bool,bool>>* ask_for_input();
		
		bool verify_validity_input(std::string);
		void change_active_player();
		bool verify_in_board(std::string);
		
		void print_mpos_vect(std::vector<MatPosi*>*,bool);
		void print_mpos_vect(std::vector<MatPosi*>*);
		
		//
		BitypeVar<std::pair<MatPosi*,MatPosi*>>* sort_mpos_and_calc_roc_info(MatPosi*,MatPosi*);
		bool exec_roc(MatPosi*, MatPosi*);
		//

		void exec_move(MatPosi*, MatPosi*, bool);
		void exec_move(MatPosi*, MatPosi*);
		void exec_move(std::string, std::string, bool);
		void exec_move(std::string, std::string);
		void exec_move(std::pair<int,int>, std::pair<int,int>, bool);
		void exec_move(std::pair<int,int>, std::pair<int,int>);

		bool verify_move(MatPosi*, MatPosi*, std::string);
		bool verify_move(MatPosi*, MatPosi*);
		bool verify_move(std::string, std::string, std::string);
		bool verify_move(std::string, std::string);
		bool verify_move(std::pair<int,int>, std::pair<int,int>, std::string);
		bool verify_move(std::pair<int,int>, std::pair<int,int>);
		
		std::vector<MatPosi*>* check_possible_mouvement(Chesspiece*, std::string);
		BitypeVar<AdvTuple*>* find_linking_advtuple(std::pair<int,int>, std::pair<int,int>, std::string);
		bool complete_danger_test(std::pair<int,int> , std::pair<int,int> , std::string);
		
		void show_possible_mouvement(Chesspiece*, std::string);
		
		virtual void affichage() = 0;
		
		Chesspiece* ask_evolution_input(std::vector<Chesspiece*>*);
		void check_evolution();
		
		bool can_escape_position(Chesspiece* ,std::string);
		
		//experiences
		bool more_dangers_part(std::pair<int,int>, Player*, int, std::string);
		
		BitypeVar<MatPosi*>* in_endangered_part(std::pair<int,int>, Player*, int, std::string);			
		BitypeVar<MatPosi*>* is_endangered(MatPosi*,Player*);
		BitypeVar<MatPosi*>* is_endangered(MatPosi*);
		
		bool check_more_than_one_danger(MatPosi*,Player*);
		bool check_more_than_one_danger(MatPosi*);
		
		std::vector<MatPosi*>* recup_zones_between_part(std::vector<std::pair<int,int>>*, MatPosi*, MatPosi*); // ,Plateau*  static
		std::vector<MatPosi*>* recup_zones_between(std::pair<int,int>, AdvTuple, std::pair<int,int>);
		
		std::vector<MatPosi*>* get_zones_between(std::pair<int,int>, std::pair<int,int> , std::string);
		
		bool check_between_is_empty_part(std::vector<std::pair<int,int>>*, MatPosi*, MatPosi*); // ,Plateau*  static		
		bool check_between_is_empty(std::pair<int,int>, AdvTuple, std::pair<int,int>);
		
		bool check_non_active_player_king(Chesspiece*);
		
		bool verify_kings();
		std::vector<Chesspiece*>* get_kings();
		
		bool check_danger_mouvement_and_path(std::pair<int,int>, AdvTuple, std::pair<int,int>, std::string);
		
};
#endif
