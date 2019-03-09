#pragma once
#ifndef TRINOME_HPP
#define TRINOME_HPP
#include <string>
#include <vector>

#include "Paire/Paire.hpp"

template<typename T1, typename T2, typename T3>
class Trinome: public Paire<T1,T2>{
    private:
        T3 third;
        
	public:
        Trinome(); //*< Constructor
        Trinome(T1,T2,T3); //*< Constructor
        ~Trinome() noexcept = default; //Destructor
        Trinome(const Trinome<T1,T2,T3>&);
        Trinome<T1,T2,T3>& operator= (const Trinome<T1,T2,T3>&) noexcept = default;
        
        template<typename S1, typename S2, typename S3>
        friend std::ostream& operator<< (std::ostream &s,Trinome<S1,S2,S3> &c);
        
        template<typename S1, typename S2, typename S3>
        friend std::ostream& operator<< (std::ostream &s,Trinome<S1,S2,S3>* c);
        
        T3 get_third() const;
        
        void set_third(T3);
   
};

template<typename T1, typename T2, typename T3>
Trinome<T1,T2,T3>::Trinome() : Paire<T1,T2>(), third(T3()) {}

template<typename T1, typename T2, typename T3>
Trinome<T1,T2,T3>::Trinome(T1 one, T2 two, T3 three) : Paire<T1,T2>(one,two), third(three) {}

template<typename T1, typename T2, typename T3>
Trinome<T1,T2,T3>::Trinome(const Trinome<T1,T2,T3>& tri) : Paire<T1,T2>(tri), third(tri.third) {}

template<typename S1, typename S2, typename S3>
std::ostream& operator <<(std::ostream &s,Trinome<S1,S2,S3> &c){
	/* affchage d'un Trinome */
	
	S1 one = c.get_first();
    S2 two = c.get_second();
    S3 three = c.get_third();
	
    s<<"Trinome("<<one<<","<<two<<","<<three<<")";
    return s;
}

template<typename S1, typename S2, typename S3>
std::ostream& operator <<(std::ostream &s,Trinome<S1,S2,S3>* c){
	/* affchage d'un Trinome */
    s<<(*c);
    return s;
}

template<typename T1, typename T2, typename T3>
T3 Trinome<T1,T2,T3>::get_third() const {return this->third;}

template<typename T1, typename T2, typename T3>
void Trinome<T1,T2,T3>::set_third(T3 thi){this->third = thi;}
#endif
