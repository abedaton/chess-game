#pragma once
#ifndef TRINOME_HPP
#define TRINOME_HPP
#include <iostream>
#include <string>
#include <vector>

template<typename T1, typename T2, typename T3>
class Trinome{
    private:
		
		T1 first;
        T2 second;
        T3 third;
        
	public:
        Trinome(); //*< Constructor
        Trinome(T1,T2,T3); //*< Constructor
        ~Trinome() noexcept = default; //Destructor
        Trinome(const Trinome&);
        Trinome& operator= (const Trinome<T1,T2,T3>&) noexcept = default;
        
        template<typename S1, typename S2, typename S3>
        friend std::ostream& operator<< (std::ostream &s,Trinome<S1,S2,S3> &c);
        
        template<typename S1, typename S2, typename S3>
        friend std::ostream& operator<< (std::ostream &s,Trinome<S1,S2,S3>* c);
        
        T1 get_first();
        T2 get_second();
        T3 get_third();
        
        void set_first(T1);
        void set_second(T2);
        void set_third(T3);
   
};

template<typename T1, typename T2, typename T3>
Trinome<T1,T2,T3>::Trinome() : first(T1()), second(T1()), third(T3()) {}

template<typename T1, typename T2, typename T3>
Trinome<T1,T2,T3>::Trinome(T1 one, T2 two, T3 three) : first(one), second(two), third(three) {}

template<typename T1, typename T2, typename T3>
Trinome<T1,T2,T3>::Trinome(const Trinome<T1,T2,T3>& tri) : first(tri.first), second(tri.second), third(tri.third) {}

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
T1 Trinome<T1,T2,T3>::get_first(){return this->first;}

template<typename T1, typename T2, typename T3>
T2 Trinome<T1,T2,T3>::get_second(){return this->second;}

template<typename T1, typename T2, typename T3>
T3 Trinome<T1,T2,T3>::get_third(){return this->third;}


template<typename T1, typename T2, typename T3>
void Trinome<T1,T2,T3>::set_first(T1 fi){this->first = fi;}

template<typename T1, typename T2, typename T3>
void Trinome<T1,T2,T3>::set_second(T2 sec){this->second = sec;}

template<typename T1, typename T2, typename T3>
void Trinome<T1,T2,T3>::set_third(T3 thi){this->third = thi;}
#endif
