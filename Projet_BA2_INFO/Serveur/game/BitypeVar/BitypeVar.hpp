#pragma once
#ifndef BITYPEVAR_HPP
#define BITYPEVAR_HPP
#include <iostream>
#include <string>
#include <vector>

template<typename Type>
class BitypeVar{
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
        
        /*
        template<class T>
        friend std::ostream& operator<< (std::ostream &s,BitypeVar<T>* c);
        */
        
        bool get_state();
        Type get_var();
        
        void set_state(bool);
        void set_var(Type);
        
};

template<typename Type>
std::ostream& operator <<(std::ostream &s,BitypeVar<Type> &c){
	/* affchage d'un BitypeVar<Type> */
	
	Type variable;
	variable = c.get_var();
	
    s<<"BitypeVar("<<"state:"<<c.get_state()<<" ,var:"<<variable<<")";
    return s;
}

/*
template<typename Type>
std::ostream& operator <<(std::ostream &s,BitypeVar<Type>* c){
	// affchage d'un BitypeVar<Type> 
    s<<(*c);
    return s;
}
*/

template<typename Type>
BitypeVar<Type>::BitypeVar() : state(false), var(Type()) {}

template<typename Type>
BitypeVar<Type>::BitypeVar(bool b, Type t) : state(b), var(t) {}

template<typename Type>
bool BitypeVar<Type>::get_state(){return this->state;}

template<typename Type>
Type BitypeVar<Type>::get_var(){return this->var;}

template<typename Type>
void BitypeVar<Type>::set_state(bool etat){this->state = etat;}

template<typename Type>
void BitypeVar<Type>::set_var(Type variable){this->var = variable;}

#endif
