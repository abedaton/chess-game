
#include <iostream>

#include "../Tester/Tester.cpp"

#include "test_chessp.hpp"

MyOstream mout("logfile.txt");

//typedef Trinome<std::string,std::string,BitypeVar<bool>> TriVect;

Paire<int,int> test_tour(){
	
	TriVect* tri_t_one = new TriVect("A1","B2",BitypeVar<bool>(true,false));
	TriVect* tri_t_two = new TriVect("A1","B1",BitypeVar<bool>(true,true));
	TriVect* tri_t_three = new TriVect("B1","B2",BitypeVar<bool>(true,true));
	
	std::vector<TriVect> vect = {*(tri_t_one),*(tri_t_two),*(tri_t_three)};
	
	return test_pe<Tour>("Tester Tour",vect,"A1");
}

Paire<int,int> test_fous(){
	
	TriVect* tri_one = new TriVect("A1","B2",BitypeVar<bool>(true,true));
	TriVect* tri_two = new TriVect("B2","C2",BitypeVar<bool>(true,false));
	TriVect* tri_three = new TriVect("B2","E5",BitypeVar<bool>(true,true));
	TriVect* tri_four = new TriVect("E5","F4",BitypeVar<bool>(true,true));
	TriVect* tri_five = new TriVect("F4","C7",BitypeVar<bool>(true,true));
	
	std::vector<TriVect> vect = {*(tri_one),*(tri_two),*(tri_three), *(tri_four), *(tri_five)};
	
	return test_pe<Fous>("Tester Fous",vect,"A1");
}

Paire<int,int> test_pion(){
	
	TriVect* tri_one = new TriVect("D2","D4",BitypeVar<bool>(true,true));
	TriVect* tri_two = new TriVect("D4","D6",BitypeVar<bool>(true,false));
	TriVect* tri_three = new TriVect("D4","D5",BitypeVar<bool>(true,true));
	TriVect* tri_four = new TriVect("D5","E5",BitypeVar<bool>(true,false));
	
	std::vector<TriVect> vect = {*(tri_one),*(tri_two),*(tri_three), *(tri_four)};
	
	return test_pe<Pion>("Tester Pion",vect,"D2");
}

Paire<int,int> test_dame(){
	
	TriVect* tri_one = new TriVect("A1","B2",BitypeVar<bool>(true,true));
	TriVect* tri_two = new TriVect("B2","B4",BitypeVar<bool>(true,true));
	TriVect* tri_three = new TriVect("B4","D4",BitypeVar<bool>(true,true));
	TriVect* tri_four = new TriVect("D4","B4",BitypeVar<bool>(true,true));
	TriVect* tri_five = new TriVect("B4","A5",BitypeVar<bool>(true,true));
	
	std::vector<TriVect> vect = {*(tri_one),*(tri_two),*(tri_three), *(tri_four), *(tri_five)};

	return test_pe<Dame>("Tester Dame",vect,"A1");
}

Paire<int,int> test_roi(){
	
	TriVect* tri_one = new TriVect("A1","C3",BitypeVar<bool>(true,false));
	TriVect* tri_two = new TriVect("A1","B2",BitypeVar<bool>(true,true));
	TriVect* tri_three = new TriVect("B2","C2",BitypeVar<bool>(true,true));
	TriVect* tri_four = new TriVect("C2","C3",BitypeVar<bool>(true,true));
	
	std::vector<TriVect> vect = {*(tri_one),*(tri_two),*(tri_three), *(tri_four)};
	
	return test_pe<Roi>("Tester Roi",vect,"A1");
}

Paire<int,int> test_chevalier(){
	
	TriVect* tri_one = new TriVect("D4","E6",BitypeVar<bool>(true,true));
	TriVect* tri_two = new TriVect("E6","F4",BitypeVar<bool>(true,true));
	TriVect* tri_three = new TriVect("F4","F5",BitypeVar<bool>(true,false));
	TriVect* tri_four = new TriVect("F4","E4",BitypeVar<bool>(true,false));
	
	std::vector<TriVect> vect = {*(tri_one),*(tri_two),*(tri_three), *(tri_four)};
	
	return test_pe<Chevalier>("Tester Chevalier",vect,"D4");
}

Paire<int,int> test_fonctionnaire(){
	
	TriVect* tri_one = new TriVect("B2","B7",BitypeVar<bool>(true,true));
	TriVect* tri_two = new TriVect("B7","G7",BitypeVar<bool>(true,true));
	TriVect* tri_three = new TriVect("G7","C7",BitypeVar<bool>(true,false));
	TriVect* tri_four = new TriVect("G7","B2",BitypeVar<bool>(true,false));
	
	std::vector<TriVect> vect = {*(tri_one),*(tri_two),*(tri_three), *(tri_four)};

	return test_pe<Fonctionnaire>("Tester Fonctionnaire",vect,"B2");
}

Paire<int,int> test_garde(){
	
	TriVect* tri_one = new TriVect("A1","C3",BitypeVar<bool>(true,false));
	TriVect* tri_two = new TriVect("A1","B2",BitypeVar<bool>(true,true));
	TriVect* tri_three = new TriVect("B2","C2",BitypeVar<bool>(true,true));
	TriVect* tri_four = new TriVect("C2","C3",BitypeVar<bool>(true,true));
	
	std::vector<TriVect> vect = {*(tri_one),*(tri_two),*(tri_three), *(tri_four)};
	
	return test_pe<Garde>("Tester Garde",vect,"A1");
}

Paire<int,int> test_faucon(){
	
	TriVect* tri_one = new TriVect("B2","B3",BitypeVar<bool>(true,false));
	TriVect* tri_two = new TriVect("B2","B4",BitypeVar<bool>(true,true));
	TriVect* tri_three = new TriVect("B4","B7",BitypeVar<bool>(true,true));
	TriVect* tri_four = new TriVect("B7","B2",BitypeVar<bool>(true,false));
	TriVect* tri_five = new TriVect("B7","C6",BitypeVar<bool>(true,false));
	TriVect* tri_six = new TriVect("B7","E4",BitypeVar<bool>(true,true));
	
	std::vector<TriVect> vect = {*(tri_one),*(tri_two),*(tri_three), *(tri_four), *(tri_five), *(tri_six)};
	
	return test_pe<Faucon>("Tester Faucon",vect,"B2");
}

Paire<int,int> test_chancellier(){
	
	TriVect* tri_one = new TriVect("D4","E6",BitypeVar<bool>(true,true));
	TriVect* tri_two = new TriVect("E6","F4",BitypeVar<bool>(true,true));
	TriVect* tri_three = new TriVect("F4","F5",BitypeVar<bool>(true,true));
	TriVect* tri_four = new TriVect("F5","E5",BitypeVar<bool>(true,true));
	
	std::vector<TriVect> vect = {*(tri_one),*(tri_two),*(tri_three), *(tri_four)};
	
	return test_pe<Chancellier>("Tester Chancellier",vect,"D4");
}

int main(){
	int final_passed_cnt = 0;
	int final_tot_cnt = 0;
	Paire<int,int> paire;
	
	paire = test_tour(); //OK
	final_passed_cnt += paire.first;
	final_tot_cnt += paire.second;
	
	paire = test_fous(); //OK
	final_passed_cnt += paire.first;
	final_tot_cnt += paire.second;
	
	paire = test_pion(); //OK
	final_passed_cnt += paire.first;
	final_tot_cnt += paire.second;
	
	paire = test_dame(); //OK
	final_passed_cnt += paire.first;
	final_tot_cnt += paire.second;
	
	paire = test_roi(); //OK
	final_passed_cnt += paire.first;
	final_tot_cnt += paire.second;
	
	paire = test_chevalier(); //OK
	final_passed_cnt += paire.first;
	final_tot_cnt += paire.second;
	
	
	paire = test_fonctionnaire(); //OK
	final_passed_cnt += paire.first;
	final_tot_cnt += paire.second;
	
	paire = test_garde(); //OK
	final_passed_cnt += paire.first;
	final_tot_cnt += paire.second;
	
	paire = test_faucon(); //OK
	final_passed_cnt += paire.first;
	final_tot_cnt += paire.second;
	
	paire = test_chancellier(); //OK
	final_passed_cnt += paire.first;
	final_tot_cnt += paire.second;
	
	mout<<std::endl<<"####################################################################################################################"<<std::endl;
	mout<<std::endl;
	mout<<"FINAL RECAP: "<<final_passed_cnt<<" tests reussi sur "<<final_tot_cnt<<std::endl;
	mout<<std::endl<<"####################################################################################################################"<<std::endl;
	mout<<std::endl;
	
	return 0;
}
