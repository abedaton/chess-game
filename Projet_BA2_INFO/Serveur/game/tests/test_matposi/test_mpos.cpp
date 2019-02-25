
#include <iostream>
#include <string>

#include "../../AdvTuple/MatPosi/MatPosi.cpp"

MyOstream mout("logfile.txt");

void compare(MatPosi* prem,std::string nom_prem,MatPosi* sec,std::string nom_sec){
	
	std::cout<<std::endl;
	std::cout<<nom_prem<<" < "<<nom_sec<<" :: "<<(*prem < *sec)<<std::endl;
	std::cout<<nom_prem<<" > "<<nom_sec<<" :: "<<(*prem > *sec)<<std::endl;
	std::cout<<nom_prem<<" == "<<nom_sec<<" :: "<<(*prem == *sec)<<std::endl;
	std::cout<<nom_prem<<" != "<<nom_sec<<" :: "<<(*prem != *sec)<<std::endl;
	std::cout<<nom_prem<<" <= "<<nom_sec<<" :: "<<(*prem <= *sec)<<std::endl;
	std::cout<<nom_prem<<" >= "<<nom_sec<<" :: "<<(*prem >= *sec)<<std::endl;
	std::cout<<std::endl;
	
}

int main(){
	
	MatPosi* mpos_3_4 = new MatPosi(3,4);
	MatPosi* mpos_4_4 = new MatPosi(4,4);
	MatPosi* mpos_4_4_bis = new MatPosi(4,4);
	
	MatPosi* mpos_co = new MatPosi("B12");
	
	compare(mpos_3_4,"mpos_3_4",mpos_4_4,"mpos_4_4");
	compare(mpos_4_4_bis,"mpos_4_4_bis",mpos_4_4,"mpos_4_4");
	
	
	std::pair<int,int> co_int = mpos_co->to_pair();;	
	std::cout<<"INT: "<<co_int.first<<","<<co_int.second<<std::endl;
	
	std::string co_str = mpos_co->to_string();
	std::cout<<"STR: "<<co_str<<std::endl;
	
	return 0;
}
