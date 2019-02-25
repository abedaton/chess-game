/*
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <sstream>      // std::stringstream
*/

#pragma once
#ifndef PLATEAU_HPP
#define PLATEAU_HPP

#include "../Pieces/Pieces.cpp"

bool detect_pair_in_list_of_pairs(std::vector<std::pair<int,int>>, std::pair<int,int>);
bool detect_pair_in_list_of_double_pairs(std::vector<std::pair<std::pair<int,int>,AdvTuple>>, std::pair<int,int>);
std::string adaptive_mode(BitypeVar<Chesspiece*>, std::string);
std::vector<std::vector<BitypeVar<Chesspiece*>>>* make_board(int);


class Plateau{
    private:
		int taille;
		std::vector<std::vector<BitypeVar<Chesspiece*>>>* board;
	
	public:
        Plateau(int); //*< Constructor
        Plateau() noexcept = default; //*< Constructor
        ~Plateau() noexcept = default; //Destructor
        Plateau(const Plateau&);// noexcept = default;
        Plateau& operator= (const Plateau&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,Plateau &c);
        friend std::ostream& operator<< (std::ostream &s,Plateau* c);
        
        int get_taille();
        
        std::vector<BitypeVar<Chesspiece*>> get_row(int);
        
        void set_piece(std::pair<int,int>,Chesspiece*,bool);
        void set_piece(std::pair<int,int>,Chesspiece*);
        BitypeVar<Chesspiece*> get_piece(std::pair<int,int>) const;
        
        std::pair<bool,std::string> isvalid_move(std::pair<int,int>,std::pair<int,int>);
        std::pair<bool,std::string> isvalid_move(std::pair<int,int>,std::pair<int,int>,std::string);
        
        bool move(std::pair<int,int>,std::pair<int,int>);
        bool switch_positions(std::pair<int,int>,std::pair<int,int>);
        
        bool verify_in_board(std::pair<int,int>);
        
        bool is_empty_location(std::pair<int,int>);

};
#endif
