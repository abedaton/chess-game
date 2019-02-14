
#include <iostream>

#include "../../Plateau/Plateau.cpp"

MyOstream mout("logfile.txt");

int main(){
	Tour* piece = new Tour();
	
	Plateau* plat = new Plateau(8);
	
	MatPosi* mpos = new MatPosi("F5");
	plat->set_piece(mpos->to_pair(),piece);
	
	mout<<plat->get_piece(mpos->to_pair()).get_state()<<std::endl;
	
	mout<<*plat<<std::endl;
	
	Plateau first_plat = *plat;
	Plateau second_plat = *plat;
	
	MatPosi* in = new MatPosi("F5");
	MatPosi* out = new MatPosi("G5");
	
	mout<<"ini "<<first_plat.get_piece(in->to_pair()).get_state()<<std::endl;
	
	mout<<first_plat<<std::endl;
	
	first_plat.move(in->to_pair(),out->to_pair());
	
	mout<<"first "<<first_plat.get_piece(in->to_pair()).get_state()<<std::endl;
	mout<<first_plat<<std::endl;
	mout<<"second "<<second_plat.get_piece(in->to_pair()).get_state()<<std::endl;
	mout<<second_plat<<std::endl;
	
	return 0;
}
