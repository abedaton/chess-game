
//#include <iostream>

#include "../../Affichage/Affichage.cpp"

MyOstream mout("logfile.txt");

int main(){
	
	std::string langue = "francais";
	
	Human* test_player = new Human("Test_player",langue);
	
	//this->get_pe()->set_owner(test_player);
	
	Dico* dict = make_dico("../../csv");
	
	//Affichage* aff = new Affichage(this->get_plateau(), dict,"Symbole_","",langue,test_player, test_player,"*" ,"");
	
	Tour* piece = new Tour();
	piece->set_owner(test_player);
	
	Plateau* plat = new Plateau(8);
	
	MatPosi* mpos = new MatPosi("F5");
	plat->set_piece(mpos->to_pair(),piece);
	
	mout<<plat->get_piece(mpos->to_pair()).get_state()<<std::endl;
	
	Affichage* aff = new Affichage(plat, dict,"Symbole_","",langue,test_player, test_player,"*" ,"");
	//mout<<*plat<<std::endl;
	mout<<aff->get_affichage()<<std::endl;
	
	Plateau first_plat = *plat;
	Plateau second_plat = *plat;
	
	MatPosi* in = new MatPosi("F5");
	MatPosi* out = new MatPosi("G5");
	
	mout<<"ini "<<first_plat.get_piece(in->to_pair()).get_state()<<std::endl;
	
	Affichage* first_aff = new Affichage(&first_plat, dict,"Symbole_","",langue,test_player, test_player,"*" ,"");
	//mout<<first_plat<<std::endl;
	mout<<first_aff->get_affichage()<<std::endl;
	
	first_plat.move(in->to_pair(),out->to_pair());
	
	mout<<"first "<<first_plat.get_piece(in->to_pair()).get_state()<<std::endl;
	//mout<<first_plat<<std::endl;
	mout<<first_aff->get_affichage()<<std::endl;
	
	mout<<"second "<<second_plat.get_piece(in->to_pair()).get_state()<<std::endl;
	
	Affichage* second_aff = new Affichage(&second_plat, dict,"Symbole_","",langue,test_player, test_player,"*" ,"");
	//mout<<second_plat<<std::endl;
	mout<<second_aff->get_affichage()<<std::endl;
	
	return 0;
}
