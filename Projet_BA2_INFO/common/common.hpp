/*
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
*/
#include <utility>
#include <sys/types.h>
#include <dirent.h>
#include <sstream>

#include "../BitypeVar/BitypeVar.hpp"
#include "MyException/MyException.cpp"
#include "Quadrinome/Quadrinome.hpp"

extern MyOstream mout;

bool is_prime(int);

bool isvalid_coord(std::string);

std::vector<std::string>* os_list_dir(const std::string&);

std::string get_first_file_of_dir(const std::string&,std::string);

template<typename Type>
BitypeVar<Type>* intel_min_max(BitypeVar<Type>* val_one,BitypeVar<Type>* val_two,std::string cas){
	BitypeVar<Type>* res;
	
	if (((val_one != nullptr) and (val_one->get_state() != false)) and ((val_two != nullptr) and (val_two->get_state() != false))){
		if (cas == "max"){
			if (val_one->get_var() < val_two->get_var()){
				res = val_two;
			}
			else{res = val_one;}
		}

		else if (cas == "min"){
			if (val_one->get_var() > val_two->get_var()){
				res = val_two;
			}
			else{res = val_one;}
			
		}
		
		else throw MyException(&mout, "cas invalide!");
	}
	
	else if (((val_one == nullptr) or (val_one->get_state() == false)) and (val_two->get_state() != false)){
		res = val_two;
	}
	
	else if ((val_one->get_state() != false) and ((val_two == nullptr) or (val_two->get_state() == false))){
		res = val_one;
	}
	
	else{
		res = val_one;
	} //peu importe, les 2 sont false
		
	return res;
}

template<typename Type>
bool is_in_vect(std::vector<Type>* vect, Type elem){
	/* fonction déterminant si un element se trouve dans un vecteur (de même type) */
	bool res = false;
	
	long long unsigned int i=0;
	while(i<vect->size() and res == false){
		
		if ((*vect)[i] == elem){res = true;}
		
		i++;
		}
	return res;
	
}
