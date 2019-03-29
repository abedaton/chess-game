#pragma once
#ifndef AFFICHAGEDARKCHESSGRAPH_HPP
#define AFFICHAGEDARKCHESSGRAPH_HPP
#include "../AffichageDarkChess/AffichageDarkChess.cpp"

class AffichageDarkChessGraph : public AffichageDarkChess{
    public:
		AffichageDarkChessGraph(); //*< Constructor // noexcept = default
		virtual ~AffichageDarkChessGraph() noexcept = default; //Destructor
		AffichageDarkChessGraph(const AffichageDarkChessGraph&) noexcept = default;
		AffichageDarkChessGraph& operator= (const AffichageDarkChessGraph&) noexcept = default;
};
#endif