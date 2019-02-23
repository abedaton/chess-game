
//#include <iostream>
//#include <vector>
//#include <string>

#include "../../Affichage/Affichage.cpp"


class Tester{
    private:
		Chesspiece* pe;
		std::string name;
		Plateau* plateau;
		std::vector<Trinome<std::string,std::string,BitypeVar<bool>>> actions;
		std::string posi_ini;
	
	public:
        Tester(Chesspiece*,std::string,Plateau*,std::vector<Trinome<std::string,std::string,BitypeVar<bool>>>,std::string); //*< Constructor
        Tester() noexcept = default; //*< Constructor
        ~Tester() noexcept = default; //Destructor
        Tester(const Tester&) noexcept = default;
        Tester& operator= (const Tester&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,Tester &c);
        
        std::string get_name();
        Chesspiece* get_pe();
        Plateau* get_plateau();
        std::vector<Trinome<std::string,std::string,BitypeVar<bool>>> get_actions();
        std::string get_posi_ini();
        
        std::pair<int,int> execute();
};
