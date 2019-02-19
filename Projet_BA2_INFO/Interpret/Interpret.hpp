
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Dico/Dico.cpp"

class Interpret{
	private:
		Dico* dico;
		std::vector<Trinome<std::string,bool,bool>*>* text_list;
		
	public:
        Interpret(Dico*); //*< Constructor
        ~Interpret() noexcept = default; //Destructor
        Interpret(const Interpret&) noexcept = default;
        Interpret& operator= (const Interpret&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,Interpret &c);
        friend std::ostream& operator<< (std::ostream &s,Interpret* c);
        
        Dico* get_dico();
        
        void add_text(std::string,bool,bool);
        std::string get_text(std::string);

};
