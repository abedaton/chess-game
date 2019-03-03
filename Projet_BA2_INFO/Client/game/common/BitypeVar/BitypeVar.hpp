#pragma once
#ifndef BITYPEVAR_HPP
#define BITYPEVAR_HPP
#include <iostream>
#include <string>
#include <vector>

template<typename Type>
class BitypeVar{
	/* classe permettant la recréation du None de python,
	 * basiquement une variable avec un bool caché qui indique si oui ou non la variable est cencé être a None */
	
    private:
		bool state;
        Type var;

	public:
        BitypeVar(); //*< Constructor
        BitypeVar(bool,Type); //*< Constructor
        ~BitypeVar() noexcept = default; //Destructor
        BitypeVar(const BitypeVar&) noexcept = default;
        BitypeVar& operator= (const BitypeVar&) noexcept = default;
        
        template<typename T>
        friend std::ostream& operator<< (std::ostream &s,BitypeVar<T> &c);
        
        
        //template<class T>
        //friend std::ostream& operator<< (std::ostream &s,BitypeVar<T>* c);
        
        
        bool get_state() const;
        Type get_var() const;
        
        void set_state(bool);
        void set_var(Type);
        
};

template<typename T>
std::ostream& operator <<(std::ostream &s,BitypeVar<T> &c){
	/* affchage d'un BitypeVar<T> */
	
	T variable;
	variable = c.get_var();
	
	bool status = c.get_state();
	
    s<<"BitypeVar("<<"state:"<<status<<" ,var:"<<variable<<")";
    return s;
}


/*
template<typename T> // ------------------------------------------------------- problème incomphrehensible, Triniome fonctionne alors que fait de la même façon
std::ostream& operator <<(std::ostream &s,BitypeVar<T>* c){
	// affchage d'un BitypeVar<T> 
    s<<(*c);
    return s;
}
*/

template<typename Type>
BitypeVar<Type>::BitypeVar() : state(false), var(Type()) {}

template<typename Type>
BitypeVar<Type>::BitypeVar(bool b, Type t) : state(b), var(t) {}

template<typename Type>
bool BitypeVar<Type>::get_state() const {return this->state;}

template<typename Type>
Type BitypeVar<Type>::get_var() const {return this->var;}

template<typename Type>
void BitypeVar<Type>::set_state(bool etat){this->state = etat;}

template<typename Type>
void BitypeVar<Type>::set_var(Type variable){this->var = variable;}

#endif
