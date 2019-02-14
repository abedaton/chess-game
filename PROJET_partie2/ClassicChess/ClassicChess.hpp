
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <sstream>      // std::stringstream
#include <cmath>

#include "../Plateau/Plateau.cpp"
#include "Trinome/Trinome.hpp"

class ClassicChess{
	// code classe simulant un serveur
    private:
		Plateau* plateau;
		Player* low_player;
		Player* high_player;
		Player* active_player;
		Dico* dico;
		std::string langue;
		Message* messenger;

	public:
        ClassicChess(Player*,Player*,Dico*,std::string,Message*); //*< Constructor
        ClassicChess() noexcept = default; //*< Constructor
        ~ClassicChess() noexcept = default; //Destructor
        ClassicChess(const ClassicChess&) noexcept = default;
        ClassicChess& operator= (const ClassicChess&) noexcept = default;
        
        // pas d'interactions avec le "serveur", il gère tout --> peu de fonctions publiques
        void execute();
        
	private:
		Player* get_low_player();
		Player* get_high_player();
		Player* get_other_player(Player*);
		Player* get_active_player();
		Player* get_non_active_player();
		
		Message* get_messenger();
		
		void set_active_player(Player*);
		void set_low_player(Player*);
		void set_high_player(Player*);
		
		int get_player_row(Player*);
		
		Plateau* get_plateau();
		void set_plateau(Plateau*);
		
		Dico* get_dico();
		
		std::string get_langue();
		
		void initial_set_piece(Chesspiece*,Player*,std::string);
		void initialisation();
		void initialise_board();
		void initialise_low_pieces();
		void initialise_high_pieces();
		
		void show_bitype_vect(std::vector<BitypeVar<Chesspiece*>>);
		BitypeVar<std::vector<MatPosi>*>* calculate_zones_between_zones(MatPosi*, MatPosi*);
		
		std::pair<std::string,BitypeVar<Chesspiece*>> in_input(std::string,std::string,std::string,bool);
		std::pair<std::string,BitypeVar<Chesspiece*>> in_input(std::string,std::string,std::string);
		std::pair<std::string,BitypeVar<Chesspiece*>> in_depl_input();
		std::pair<std::string,BitypeVar<Chesspiece*>> in_roc_input();
		
		bool check_illegal_move(std::string,std::string);
		
		std::pair<bool,BitypeVar<Chesspiece*>> normal_output_check(std::string,std::string);
		
		bool verify_possible_roc(Roi*,Tour*);
		
		Trinome<std::pair<bool,bool>,BitypeVar<Chesspiece*>,std::string>* roc_first_pe_is_waiting(Chesspiece* pe);

		Trinome<std::pair<bool,bool>,BitypeVar<Chesspiece*>,std::string>* roc_output_check(BitypeVar<Chesspiece*>);
		Trinome<std::string,BitypeVar<Chesspiece*>,std::pair<bool,bool>>* out_input(std::string,BitypeVar<Chesspiece*>);
		
		void show_depl_possibles(Chesspiece*);
		void show_depl_possibles(std::string);
		
		Trinome<std::pair<std::string,BitypeVar<Chesspiece*>>,std::pair<std::string,BitypeVar<Chesspiece*>>,bool>* ask_for_input();
		
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

		bool verify_move(std::string, std::string);
		bool verify_move(std::string, std::string, std::string);
		bool verify_move(std::pair<int,int>, std::pair<int,int>);
		bool verify_move(std::pair<int,int>, std::pair<int,int>, std::string);
		bool verify_move(MatPosi*, MatPosi*);
		bool verify_move(MatPosi*, MatPosi*, std::string);
		
		std::vector<MatPosi*>* check_possible_mouvement(Chesspiece*, std::string);
		BitypeVar<AdvTuple*>* find_linking_advtuple(std::pair<int,int>, std::pair<int,int>, std::string);
		bool complete_danger_test(std::pair<int,int> , std::pair<int,int> , std::string);
		
		void show_possible_mouvement(Chesspiece*, std::string);
		
		void affichage();
		
		Chesspiece* ask_evolution_imput(std::vector<Chesspiece*>*);
		void check_evolution();
		
		bool can_escape_position(Chesspiece* ,std::string);
		
		bool check_more_than_one_danger(MatPosi*);
		bool check_more_than_one_danger(MatPosi*,Player*);
		
		std::vector<MatPosi*>* get_zones_between(std::pair<int,int>, std::pair<int,int> , std::string);
		bool check_non_active_player_king(Chesspiece*);
		
		bool verify_kings();
		std::vector<Chesspiece*>* get_kings();
		BitypeVar<MatPosi*>* is_endangered(MatPosi*,Player*);
		BitypeVar<MatPosi*>* is_endangered(MatPosi*);
		
		bool en_danger(std::pair<int,int>, AdvTuple, std::pair<int,int>, std::string);
		
		bool check_between(std::pair<int,int>, AdvTuple, std::pair<int,int>);
		
};
