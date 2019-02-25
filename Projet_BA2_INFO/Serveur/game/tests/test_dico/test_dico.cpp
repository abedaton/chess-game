
//#include <iostream>

#include "../../Interpret/Dico/Dico.cpp"

MyOstream mout("logfile.txt");

int main(){
	
	Dico* dico = new Dico();
	
	std::string csv_path = "../../csv";
	std::string csv_filename = get_first_file_of_dir(csv_path,".csv");
	
	if (csv_filename == ""){throw MyException(&mout, "PAS DE FICHIER CSV! POUR LE DICTIONNAIRE");}
	
	std::stringstream ss;
	ss << csv_path << '/'<< csv_filename;
	
	dico->load(ss.str());
	
	dico->show();
	
	mout<<dico->search("francais","vict")<<std::endl;
	mout<<dico->search("anglais","vict")<<std::endl;
	mout<<dico->search("neerlandais","vict")<<std::endl;
	
}
