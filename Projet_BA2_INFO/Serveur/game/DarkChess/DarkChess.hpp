
#pragma once
#ifndef DarkChess_HPP
#define DarkChess_HPP
//#include <iostream>
//#include <vector>
//#include <string>
//#include <utility>
//#include <sstream>      // std::stringstream
//#include <cmath>
#pragma once
#include "../Affichage/AffichageDarkChess.cpp"
#include "../ClassicChess/BaseChess/BaseChess.hpp"
//#include "DarkChess.cpp"

//std::vector<std::string> *split_string(std::string, std::string);

class DarkChess : public BaseChess {
    private:
    std::vector<std::vector<int>> fog;

    public:
    DarkChess(Player *, Player *, Player*, Dico *); //*< Constructor
    DarkChess() noexcept = default;        //*< Constructor
    ~DarkChess() noexcept = default;       // Destructor
    DarkChess(const DarkChess &) noexcept = default;
    DarkChess &operator=(const DarkChess &) noexcept = default;

    std::pair<bool, std::string> execute_step() override;
    std::pair<bool, bool> execute_step(std::string) override;
    std::pair<bool, bool> execute_step(std::string, std::string) override;

    protected:
    void initialise_board() override;
    void initialise_low_pieces() override;
    void initialise_high_pieces() override;

    void affichage() override;

    void make_fog();
    std::vector<std::pair<int, int>> *check_all_mov(Chesspiece *, std::string);

    std::pair<bool, BitypeVar<Chesspiece *>> normal_output_check(std::string, std::string) override;
    Trinome<std::string, BitypeVar<Chesspiece *>, Trinome<bool, bool, bool> *> *out_input(std::string, BitypeVar<Chesspiece *>) override;

    Trinome<std::string, std::string, bool> *decode_merged_string(std::string);
    bool exec_step(std::string, std::string, BitypeVar<Chesspiece *>, bool, bool);
};
#endif
