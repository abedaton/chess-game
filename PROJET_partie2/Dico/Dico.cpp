
#include "Dico.hpp"

extern MyOstream mout;

// ------------DICO--------------------------------------------------------------------------------------------

Dico::Dico() : CsvReader() {} //*< Constructor

std::ostream& operator <<(std::ostream &s,Dico &c){
	/* affchage d'un Dico */
	(void)c;
    s<<"Dico()";
    return s;
}

std::ostream& operator <<(std::ostream &s,Dico* c){
	/* affchage d'un Dico */
    s<<(*c);
    return s;
}

void Dico::show(){
	
	affichage_tableau(this->get_tableau());
}

std::string Dico::search(std::string langue, std::string rch){
	
	std::vector<std::string> legende;
	std::vector<std::string> lang_vect;
	bool rch_found = false;
	std::string res = "";
	
	legende = this->get_tableau()[0];
	
	lang_vect = this->search_col(langue);
	
	long long unsigned int j = 1;
	while (j<legende.size() and rch_found == false){
		
		if (legende[j] == rch){
			res = lang_vect[j];
			rch_found = true;
		}
			
		j++;
	}
	
	return res;
	
}
