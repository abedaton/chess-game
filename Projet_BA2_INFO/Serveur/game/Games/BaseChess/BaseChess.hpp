
#pragma once
#ifndef BASECHESS_HPP
#define BASECHESS_HPP
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <sstream>      // std::stringstream
#include <cmath>

#include "../../AffichageDarkChess/Affichage/Affichage.cpp"

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

bool is_elem_in_vect(std::vector<MatPosi*>*,MatPosi*);

std::vector<MatPosi*>* get_path_intesection(std::vector<std::vector<MatPosi*>*>*);

bool is_roquable(Chesspiece*);

std::vector<std::string>* split_string(std::string, std::string);

class BaseChess{
    private:
		Plateau* plateau;
		Player* low_player;
		Player* high_player;
		Player* active_player;
		Dico* dico;
		int action_cnt;

	public:
        BaseChess(Player*,Player*,Player*,Dico*); //*< Constructor
        BaseChess() noexcept = default; //*< Constructor
        virtual ~BaseChess() noexcept = default; //Destructor
        BaseChess(const BaseChess&) noexcept = default;
        BaseChess& operator= (const BaseChess&) noexcept = default;
        
        // pas d'interactions avec le jeu, il gère tout --> peu de fonctions publiques
        virtual std::pair<bool,std::string> execute_step(std::string);
        virtual std::pair<bool,std::string> execute_step();
        
        
        virtual std::pair<bool,bool> execute_forced_step(std::string,Player*);
        virtual std::pair<bool,bool> execute_forced_step(std::string, bool,Player*);
        virtual std::pair<bool,bool> execute_forced_step(std::string, bool, std::string,Player*);
        virtual std::pair<bool,bool> execute_forced_step(std::string,std::string,Player*);
        
        virtual std::pair<bool,bool> execute_forced_step(std::string);
        virtual std::pair<bool,bool> execute_forced_step(std::string, bool);
        virtual std::pair<bool,bool> execute_forced_step(std::string, bool, std::string);
        virtual std::pair<bool,bool> execute_forced_step(std::string,std::string);
        
        virtual std::pair<bool,bool> execute_forced_step_play(std::string,std::string); // creation de 2e serie car sinon overlap de surcharge
        virtual std::pair<bool,bool> execute_forced_step_play(std::string, bool,std::string);
        virtual std::pair<bool,bool> execute_forced_step_play(std::string, bool, std::string,std::string);
        virtual std::pair<bool,bool> execute_forced_step_play(std::string,std::string,std::string);
        
        friend class TempsReel;
		
        
	protected:
		Player* get_low_player() const;
		Player* get_high_player() const;
		Player* get_other_player(Player*) const;
		Player* get_active_player() const;
		Player* get_non_active_player() const;
		Player* get_player(std::string);
		
		void set_active_player(Player*);
		void set_low_player(Player*);
		void set_high_player(Player*);
		
		int get_action_cnt() const;
		void inc_action_cnt();
		
		int get_player_row(Player*) const;
		
		Plateau* get_plateau() const;
		void set_plateau(Plateau*);
		
		Dico* get_dico() const;
		
		std::string get_ret_symbol() const;
		std::string get_roc_symbol() const;
		std::string get_end_symbol() const;
		std::string get_lang_symbol() const;
		std::string get_liste_depl_symbol() const;
		std::string get_liste_capt_symbol() const;
		
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
		
		std::pair<bool,BitypeVar<Chesspiece*>> check_in_validity_non_symbol(std::string,std::string,std::string);
		
		Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* in_input(Interpret*,Interpret*,Interpret*,bool);
		Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* in_input(Interpret*,Interpret*,Interpret*);
		Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* in_depl_input();
		Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* in_roc_input();
		
		virtual bool check_illegal_move(std::string,std::string);
		
		virtual std::pair<bool,BitypeVar<Chesspiece*>> normal_output_check(std::string,std::string);
		
		bool verify_possible_roc(Roi*,Tour*);
		
		bool check_roc_validity(Roi*, Tour*, BitypeVar<Chesspiece*>, bool, bool);
		Trinome<Trinome<bool,bool,bool>*,BitypeVar<Chesspiece*>,std::string>* roc_first_pe_is_waiting(Chesspiece* pe);

		Trinome<Trinome<bool,bool,bool>*,BitypeVar<Chesspiece*>,std::string>* roc_output_check(BitypeVar<Chesspiece*>);
		virtual Trinome<std::string,BitypeVar<Chesspiece*>,Trinome<bool,bool,bool>*>* out_input(std::string,BitypeVar<Chesspiece*>);
		
		void show_depl_possibles(Chesspiece*);
		void show_depl_possibles(std::string);
		
		Trinome<std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<bool,bool>>* ask_for_input();
		
		bool verify_validity_input(std::string);
		void change_active_player();
		bool verify_in_board(std::string);
		
		void print_mpos_vect(std::vector<MatPosi*>*,bool);
		void print_mpos_vect(std::vector<MatPosi*>*);
		
		virtual bool roc_check_king_position_and_path_danger(MatPosi*,MatPosi*,bool,int,std::vector<MatPosi>*);
		
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

		BitypeVar<std::vector<AdvTuple*>*>* find_linking_advtuple(std::pair<int,int>, std::pair<int,int>, std::string);
		bool complete_danger_test(std::pair<int,int> , std::pair<int,int> , std::string);
		
		void show_possible_mouvement(Chesspiece*, std::string);
		
		virtual void affichage() = 0;
		
		Chesspiece* ask_evolution_input(std::vector<Chesspiece*>*);
		virtual std::vector<Chesspiece*>* evolution_possibilities() = 0;
		virtual int get_evolution_row(Player*);
		void check_evolution();
		
		bool can_escape_position(Chesspiece* ,std::string);
		
		bool can_player_move(Player*);

		bool more_dangers_part(std::pair<int,int>, Player*, int, std::string);
		
		BitypeVar<MatPosi*>* in_endangered_part(std::pair<int,int>, Player*, int, std::string);			
		BitypeVar<MatPosi*>* is_endangered(MatPosi*,Player*);
		BitypeVar<MatPosi*>* is_endangered(MatPosi*);
		
		bool check_more_than_one_danger(MatPosi*,Player*);
		bool check_more_than_one_danger(MatPosi*);
		
		std::vector<MatPosi*>* recup_zones_between_part(std::vector<std::pair<int,int>>*, MatPosi*, MatPosi*); // ,Plateau*  static
		std::vector<MatPosi*>* recup_zones_between(std::pair<int,int>, AdvTuple, std::pair<int,int>);
		
		std::vector<std::vector<MatPosi*>*>* get_zones_between(std::pair<int,int>, std::pair<int,int> , std::string);
		
		bool check_between_is_empty_part(std::vector<std::pair<int,int>>*, MatPosi*, MatPosi*); // ,Plateau*  static		
		bool check_between_is_empty(std::pair<int,int>, AdvTuple, std::pair<int,int>);
		
		std::pair<bool,MatPosi*> check_if_echec(MatPosi*);
		virtual bool check_non_active_player_king(Chesspiece*);
		
		virtual bool verify_kings();
		std::vector<Chesspiece*>* get_kings();
		
		bool check_danger_mouvement_and_path(std::pair<int,int>, AdvTuple, std::pair<int,int>, std::string);
		
		Trinome<std::string,std::string,bool>* decode_merged_string(std::string);
        
		virtual std::pair<bool,bool> execute_forced_step(BitypeVar<Trinome<std::string,std::string,bool>*>*,Player*) = 0;
		virtual std::pair<bool,bool> execute_forced_step(BitypeVar<Trinome<std::string,std::string,bool>*>*,std::string);
		virtual std::pair<bool,bool> execute_forced_step(BitypeVar<Trinome<std::string,std::string,bool>*>*);
		
		bool check_pat();
		
		virtual std::string get_affichage_pat() const;
		std::string get_affichage_resultat(bool, bool, bool) const;
		void affichage_resultat(bool, bool, bool) const ;
		
		bool exec_step(std::string, std::string, BitypeVar<Chesspiece*>, bool, bool);
		
		virtual bool check_roc_accept(BitypeVar<Chesspiece*>) const;

		virtual bool verify_all_eaten();
		
		virtual std::pair<bool,std::string> execute_step(Player*) = 0;
		
};
#endif
