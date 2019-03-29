#pragma once
#ifndef ADVTUPLE_CPP
#define ADVTUPLE_CPP
#include "AdvTuple.hpp"


AdvTuple::AdvTuple() : x(0), y(0), depl_type(""), k_min(nullptr), k_max(nullptr), k_pas(nullptr), update_needed(false){}
AdvTuple::AdvTuple(int x_val,int y_val, std::string d_t) :x(x_val), y(y_val), depl_type(d_t), k_min(nullptr), k_max(nullptr), k_pas(nullptr), update_needed(false){
	this->verify_depl_type();
}

AdvTuple::AdvTuple(int x_val,int y_val, std::string d_t,BitypeVar<int>* min_k,BitypeVar<int>* max_k,BitypeVar<std::pair<int,std::string>>* pas_k) :x(x_val), y(y_val), depl_type(d_t), k_min(min_k), k_max(max_k), k_pas(pas_k), update_needed(false){
	this->verify_depl_type();
	this->verify_k_pas();
}

AdvTuple::AdvTuple(int x_val,int y_val, std::string d_t,BitypeVar<int>* min_k,BitypeVar<int>* max_k,BitypeVar<std::pair<int,std::string>>* pas_k,bool up) :x(x_val), y(y_val), depl_type(d_t), k_min(min_k), k_max(max_k), k_pas(pas_k), update_needed(up){
	this->verify_depl_type();
	this->verify_k_pas();
}

AdvTuple::AdvTuple(const AdvTuple& adv) : x(adv.x), y(adv.y), depl_type(adv.depl_type), k_min(adv.k_min), k_max(adv.k_max), k_pas(adv.k_pas), update_needed(adv.update_needed){}

std::ostream& operator <<(std::ostream &s,AdvTuple &c){
	/* affchage d'un AdvTuple */
    s<<"AdvTuple("<<c.get_x()<<c.get_y()<<c.need_update()<<")"; //c.get_k_min()<<c.get_k_max()<<c.get_k_pas()
    return s;
}

std::ostream& operator <<(std::ostream &s,AdvTuple* c){
	/* affchage d'un AdvTuple */
    s<<(*c);
    return s;
}

int AdvTuple::get_x(){return this->x;}
int AdvTuple::get_y(){return this->y;}
std::string AdvTuple::get_depl_type(){return this->depl_type;}

void AdvTuple::set_x(int x){this->x = x;}
void AdvTuple::set_y(int y){this->y = y;}
void AdvTuple::set_depl_type(std::string d_t){
	this->depl_type = d_t;
	this->verify_depl_type();
}

BitypeVar<int>* AdvTuple::get_k_min(){return this->k_min;}
BitypeVar<int>* AdvTuple::get_k_max(){return this->k_max;}
BitypeVar<std::pair<int,std::string>>* AdvTuple::get_k_pas(){return this->k_pas;}
        
void AdvTuple::set_k_min(BitypeVar<int>* val){this->k_min = val;}
void AdvTuple::set_k_max(BitypeVar<int>* val){this->k_max = val;}
void AdvTuple::set_k_pas(BitypeVar<std::pair<int,std::string>>* val){
	this->k_pas = val;
	this->verify_k_pas();
}

void AdvTuple::verify_k_pas(){
	BitypeVar<std::pair<int,std::string>>* val = this->get_k_pas();
	if (val->get_state() == true and val->get_var().first < 0){throw MyException(&mout, "k pas ne peut pas etre negatif!");}
}

void AdvTuple::verify_depl_type(){
	std::string d_t = this->get_depl_type();
	if ((d_t != "saut") and (d_t != "translation")){throw MyException(&mout, "type deplacement invalide!");}
}

bool AdvTuple::need_update(){return this->update_needed;}

void AdvTuple::set_need_update(bool up){this->update_needed = up;}

std::vector<std::pair<int,int>>* AdvTuple::get_res(int limite,Posi posi){
	
	BitypeVar<int>* d_limite_min = new BitypeVar<int>();
	
	d_limite_min->set_state(true);
	d_limite_min->set_var(-limite);
	
	BitypeVar<int>* d_limite_max = new BitypeVar<int>();
	
	d_limite_max->set_state(true);
	d_limite_max->set_var(limite);
	
	BitypeVar<int>* real_k_min = intel_max(this->get_k_min(),d_limite_min);
	BitypeVar<int>* real_k_max = intel_min(this->get_k_max(),d_limite_max);
	
	std::vector<int>* vals_de_k = new std::vector<int>();
	
	if((this->get_k_pas() == nullptr) or (this->get_k_pas()->get_state() == true)){
		
		int beg,end,pas;
		
		if (real_k_min->get_state() == true){
			beg = real_k_min->get_var();
		}
		else {throw MyException(&mout, "k_min est None!");}
		
		if (real_k_max->get_state() == true){
			end = real_k_max->get_var();
		}
		else {throw MyException(&mout, "k_max est None!");}


		std::string special;
		if (this->get_k_pas() != nullptr){
			special = this->get_k_pas()->get_var().second;}
		else{special = "";}
		
		if (special == "prime"){pas=1;}
		else{
			if (this->get_k_pas() != nullptr){pas = this->get_k_pas()->get_var().first;}
			else{pas = 1;}
		}
		
		
		int cnt = beg;
		while (cnt <= end){
			if (((special == "prime") and is_prime(cnt)) or special != "prime"){
			vals_de_k->push_back(cnt);
			}
			cnt += pas;
		}
		
	}
	
	else{
		std::stringstream fmt;
		fmt << "Pas" << this->get_k_pas() << "inconnu!";
		
		throw MyException(&mout, fmt.str());
	}
		
	
	// partie set_res
	std::vector<std::pair<int,int>>* set_res = new std::vector<std::pair<int,int>>();
	
	int k,res_x,res_y;
	for(long long unsigned int i=0;i<vals_de_k->size();i++){
		 k = (*vals_de_k)[i];
		 res_x = this->get_x()*k + posi.get_x(); // x*k = position realtive, +px = transformation en concrètes
         res_y = this->get_y()*k + posi.get_y();
         
         if ((res_x < limite) and (res_x >= 0) and (res_y < limite) and (res_y >= 0)){ // positions concrètes
			 if (not((res_x == posi.get_x()) and (res_y == posi.get_y()))){
				 std::pair<int, int> tup = {res_x,res_y};
				 set_res->push_back(tup);
			 } 
		 }
	}
	
	return set_res;
}
#endif
