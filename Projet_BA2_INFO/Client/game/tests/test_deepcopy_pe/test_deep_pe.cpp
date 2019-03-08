
//#include <iostream>

#include "../../Pieces/Pieces.cpp"

MyOstream mout("logfile.txt");

int main(){
	//Tour Pion
	Tour* piece = new Tour();
	
	Posi* new_posi = new Posi(0,0);//(colonne,ligne);
	Posi* posi = new Posi(1,0);//(colonne,ligne);
	
	piece->set_posi(new_posi);
	piece->set_limite(8);

	mout<<piece->get_name()<<" "<<*(piece->get_posi())<<std::endl;
	
	Tour first_pe = *piece;
	Tour second_pe = *piece;
	
	second_pe.set_posi(posi);
	
	mout<<"first "<<first_pe.get_name()<<" "<<*(first_pe.get_posi())<<std::endl;
	mout<<"second "<<second_pe.get_name()<<" "<<*(second_pe.get_posi())<<std::endl;
	
	Tour* third_pe = &(*piece);
	mout<<"third "<<third_pe->get_name()<<" "<<*(third_pe->get_posi())<<std::endl;
	
	
	return 0;
}
