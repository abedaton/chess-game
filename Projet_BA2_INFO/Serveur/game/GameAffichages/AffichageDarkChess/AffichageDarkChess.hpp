#pragma once
#include "../Affichage/Affichage.cpp"

class AffichageDarkChess : public Affichage
{
    private:
		std::vector<std::vector<int>> fog;
		Player* locked_player;

    public:
		//AffichageDarkChess(Plateau*, Dico*,std::string,std::string,std::string,Player*,Player*,std::string,std::string,std::vector<std::vector<int>>); //*< Constructor
		AffichageDarkChess(); //*< Constructor // noexcept = default
		virtual ~AffichageDarkChess() noexcept = default; //Destructor
		AffichageDarkChess(const AffichageDarkChess&) noexcept = default;
		AffichageDarkChess& operator= (const AffichageDarkChess&) noexcept = default;
	
		void set_locked_player(Player*);
		void set_fog(std::vector<std::vector<int>>);
		
    protected:
		std::vector<std::vector<int>> get_fog() const;
		
		std::string get_affichage_line(int, int) override;
		Player* get_locked_player() const;
};
