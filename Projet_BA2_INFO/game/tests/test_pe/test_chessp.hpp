
#include <iostream>

#include "../Tester/Tester.cpp"

typedef Trinome<std::string,std::string,BitypeVar<bool>> TriVect;

template <typename Type>
std::pair<int,int> test_pe(std::string name,std::vector<TriVect> vect,std::string pos_ini){
	std::pair<int,int> paire;

	Plateau* plat= new Plateau(8);
	mout <<"taille plateau : "<< plat->get_taille() << std::endl;
	
	Type* piece = new Type();

	mout<<piece->get_name()<<std::endl;
	
	Tester* tester = new Tester(piece,name,plat,vect,pos_ini);
	paire = tester->execute();
	
	return paire;
}
