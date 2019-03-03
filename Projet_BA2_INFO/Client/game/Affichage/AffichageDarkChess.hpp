#pragma once
#include "Affichage.cpp"

class AffichageDarkChess : public Affichage
{
    private:
    std::vector<std::vector<int>> fog;

    public:
    AffichageDarkChess(Plateau*, Dico*,std::string,std::string,std::string,Player*,Player*,std::string,std::string,std::vector<std::vector<int>>); //*< Constructor                
    ~AffichageDarkChess(){}

    protected:
    std::string get_affichage_line(int, int) override;
};