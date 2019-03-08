
#include <iostream>

#include "../../Interpret/Interpret.cpp"

MyOstream mout("logfile.txt");

int main(){
	
	Dico* dico = new Dico();
	
	std::string csv_path = "../../csv";
	std::string csv_filename = get_first_file_of_dir(csv_path,".csv");
	
	if (csv_filename == ""){throw MyException(&mout, "PAS DE FICHIER CSV! POUR LE DICTIONNAIRE");}
	
	std::stringstream ss;
	ss << csv_path << '/'<< csv_filename;
	
	dico->load(ss.str());
	
	//dico->show();
	
	//mout<<dico->search("francais","vict")<<std::endl;
	//mout<<dico->search("anglais","vict")<<std::endl;
	//mout<<dico->search("neerlandais","vict")<<std::endl;
	
	Interpret* interpret = new Interpret(dico);
	
	interpret->add_text(" ok ", true, false);
	interpret->add_text(" tjs ok ", false, false);
	interpret->add_text("illegal_move", false, true);
	interpret->add_text("ret", true, true);
	
	mout<<interpret->get_text("francais");
	mout<<std::endl<<"---------------------"<<std::endl;
	mout<<interpret->get_text("anglais");
	
}
