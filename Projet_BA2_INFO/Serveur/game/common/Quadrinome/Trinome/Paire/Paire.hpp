
#pragma once
#ifndef PAIRE_HPP
#define PAIRE_HPP
#include <iostream>
#include <utility>

template<typename T1, typename T2>
class Paire: private std::pair<T1,T2>{	
	public:
        Paire(); //*< Constructor
        Paire(T1,T2); //*< Constructor
        ~Paire() noexcept = default; //Destructor
        Paire(const Paire<T1,T2>&);
        
        template<typename S1, typename S2>
        Paire<S1,S2>& operator= (const Paire<S1,S2>&) noexcept;
        //Paire& operator= (const Paire&) noexcept = default;
        
        template<typename S1, typename S2>
        friend std::ostream& operator<< (std::ostream &s,Paire<S1,S2> &c);
        
        template<typename S1, typename S2>
        friend std::ostream& operator<< (std::ostream &s,Paire<S1,S2>* c);
        
        T1 get_first() const;
        T2 get_second() const;
        
        void set_first(T1);
        void set_second(T2);
   
};

template<typename T1, typename T2>
Paire<T1,T2>::Paire() : std::pair<T1,T2>() {}

template<typename T1, typename T2>
Paire<T1,T2>::Paire(T1 one, T2 two) : std::pair<T1,T2>(one,two) {}

template<typename T1, typename T2>
Paire<T1,T2>::Paire(const Paire<T1,T2>& paire) : std::pair<T1,T2>(paire) {}

template<typename S1, typename S2>
std::ostream& operator <<(std::ostream &s,Paire<S1,S2> &c){
	/* affchage d'un Paire */
	
	S1 one = c.get_first();
    S2 two = c.get_second();
	
    //s<<"Paire("<<one<<","<<two<<")";
    s<<"("<<one<<","<<two<<")";
    return s;
}

template<typename S1, typename S2>
std::ostream& operator <<(std::ostream &s,Paire<S1,S2>* c){
	/* affchage d'un Paire */
    s<<(*c);
    return s;
}

template<typename T1, typename T2>
T1 Paire<T1,T2>::get_first() const {return this->first;}

template<typename T1, typename T2>
T2 Paire<T1,T2>::get_second() const {return this->second;}

template<typename T1, typename T2>
void Paire<T1,T2>::set_first(T1 fi){this->first = fi;}

template<typename T1, typename T2>
void Paire<T1,T2>::set_second(T2 sec){this->second = sec;}

#endif
