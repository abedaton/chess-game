#pragma once
#include "../Affichage/Affichage.cpp"

class AffichageGraph : public Affichage{
    public:
		AffichageGraph(); //*< Constructor // noexcept = default
		virtual ~AffichageGraph() noexcept = default; //Destructor
		AffichageGraph(const AffichageGraph&) noexcept = default;
		AffichageGraph& operator= (const AffichageGraph&) noexcept = default;
};
