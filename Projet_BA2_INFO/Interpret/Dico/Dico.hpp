
#include <iostream>
#include <istream>
#include <string>
#include <vector>
#include <fstream>

#include "CsvReader/CsvReader.cpp"

class Dico: public CsvReader{	
	public:
        Dico(); //*< Constructor
        ~Dico() noexcept = default; //Destructor
        Dico(const Dico&) noexcept = default;
        Dico& operator= (const Dico&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,Dico &c);
        friend std::ostream& operator<< (std::ostream &s,Dico* c);
        
        void show();
        std::vector<std::string> get_ver_legende();
        std::vector<std::string> get_possible_laguages();
        std::string search(std::string, std::string);
};
