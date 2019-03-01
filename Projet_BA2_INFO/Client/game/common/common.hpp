/*
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
*/
#pragma once
#ifndef COMMON_HPP
#define COMMON_HPP
#include <utility>
#include <sys/types.h>
#include <dirent.h>
#include <sstream>

#include "../BitypeVar/BitypeVar.hpp"
#include "MyException/MyException.cpp"
#include "Quadrinome/Quadrinome.hpp"

extern MyOstream mout;

bool is_prime(int);

std::vector<std::string>* os_list_dir(const std::string&);

std::string get_first_file_of_dir(const std::string&,std::string);


template<typename Type>
BitypeVar<Type>* intel_max_part(BitypeVar<Type>* val_one,BitypeVar<Type>* val_two){
	/* fonction qui est envoyé en pointeur a intel_min_max
	 * fonction de recuperation du maximum qui gère le None */
	
	BitypeVar<Type>* res;
	
	if (val_one->get_var() < val_two->get_var()){
		res = val_two;
	}
	else{res = val_one;}
	
	return res;
	
}

template<typename Type>
BitypeVar<Type>* intel_min_part(BitypeVar<Type>* val_one,BitypeVar<Type>* val_two){
	/* fonction qui est envoyé en pointeur a intel_min_max
	 * fonction de recuperation du minimum qui gère le None */
	
	BitypeVar<Type>* res;
	
	if (val_one->get_var() > val_two->get_var()){
		res = val_two;
	}
	else{res = val_one;}
	
	return res;
	
}

// passage d'une fonction a une autre avec lock (voulu) des types.

template <typename Type>
using FunctionType = BitypeVar<Type>* (*)(BitypeVar<Type>*,BitypeVar<Type>*); // declaration typage d'une fonction

template<typename Type>
BitypeVar<Type>* intel_min_max(BitypeVar<Type>* val_one,BitypeVar<Type>* val_two,FunctionType<Type> func_part){
	/* fonction retournant soit le maximum soit le minimum (des 2 premiers paramètres données) en fonction " func_part " d'une fonction externe donné en paramètre
	 * fonction gêrant aussi le cas des variable a None
	 * 
	 * utilisation de la technique de pointeurs vers des fonctions pour éviter des doublons de code*/
	 
	 /* template <typename Type> 
	  * using FunctionType = BitypeVar<Type>* (*)(BitypeVar<Type>*,BitypeVar<Type>*);*/
	
	BitypeVar<Type>* res;
	
	if (((val_one != nullptr) and (val_one->get_state() != false)) and ((val_two != nullptr) and (val_two->get_state() != false))){
		res = func_part(val_one,val_two);
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
BitypeVar<Type>* intel_min(BitypeVar<Type>* val_one,BitypeVar<Type>* val_two){
	/* fonction de recuperation du minimum qui gère le None */
	
	return intel_min_max(val_one,val_two,intel_min_part);
}

template<typename Type>
BitypeVar<Type>* intel_max(BitypeVar<Type>* val_one,BitypeVar<Type>* val_two){	
	/* fonction de recuperation du maximum qui gère le None */
	
	return intel_min_max(val_one,val_two,intel_max_part);
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
#endif
