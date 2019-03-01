
#include <iostream>

#include "../../ClassicChess/ClassicChess.cpp"

MyOstream mout("logfile.txt");

void show_steps_between(std::string str_beg,std::string str_end){
	
	Human* player = new Human("player1");
	
	MatPosi* mpos_beg = new MatPosi(str_beg);
	MatPosi* mpos_end = new MatPosi(str_end);

	BitypeVar<std::vector<MatPosi>*>* secure_vect = calc_zones_between_zones(mpos_beg,  mpos_end,player);
	
	if(secure_vect->get_state() == true){
		
		std::vector<MatPosi>* vect = secure_vect->get_var();
		
		mout<<"steps: "<<std::endl;
		for(long long unsigned int i=0;i<vect->size();i++){
			mout<<" * "<<(*vect)[i]<<std::endl;
		}
		mout<<std::endl;
	}
	else {mout<<"no positions correlations"<<std::endl;}
}

int main(){	
	
	show_steps_between("B2","B6");
	show_steps_between("B6","B2");
	
	show_steps_between("B2","H2");
	show_steps_between("H2","B2");
	
	show_steps_between("A1","D4");
	show_steps_between("D4","A1");
	
	show_steps_between("A2","D5");
	show_steps_between("D5","A2");
	
	show_steps_between("A2","D7");
	show_steps_between("D7","A2");
	
	return 0;
}
