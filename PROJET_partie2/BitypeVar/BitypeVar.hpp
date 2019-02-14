
#include <iostream>
#include <string>
#include <vector>

template<class Type>
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
        
        template<class T>
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

template<class Type>
std::ostream& operator <<(std::ostream &s,BitypeVar<Type> &c){
	/* affchage d'un BitypeVar<Type> */
	
	Type variable;
	variable = c.get_var();
	
    s<<"BitypeVar("<<"state:"<<c.get_state()<<" ,var:"<<variable<<")";
    return s;
}

/*
template<class Type>
std::ostream& operator <<(std::ostream &s,BitypeVar<Type>* c){
	// affchage d'un BitypeVar<Type> 
    s<<(*c);
    return s;
}
*/

template<class Type>
BitypeVar<Type>::BitypeVar() : state(false), var(Type()) {}

template<class Type>
BitypeVar<Type>::BitypeVar(bool b, Type t) : state(b), var(t) {}

template<class Type>
bool BitypeVar<Type>::get_state(){return this->state;}

template<class Type>
Type BitypeVar<Type>::get_var(){return this->var;}

template<class Type>
void BitypeVar<Type>::set_state(bool etat){this->state = etat;}

template<class Type>
void BitypeVar<Type>::set_var(Type variable){this->var = variable;}
