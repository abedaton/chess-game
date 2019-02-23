/*
#include <iostream>
#include <string>
#include <vector>
*/

#include "Trinome/Trinome.hpp"

template<typename T1, typename T2, typename T3, typename T4>
class Quadrinome: public Trinome<T1,T2,T3>{
    private:
        T4 fourth;
        
	public:
        Quadrinome(); //*< Constructor
        Quadrinome(T1,T2,T3,T4); //*< Constructor
        ~Quadrinome() noexcept = default; //Destructor
        Quadrinome(const Quadrinome&);
        Quadrinome& operator= (const Quadrinome<T1,T2,T3,T4>&) noexcept = default;
        
        template<typename S1, typename S2, typename S3, typename S4>
        friend std::ostream& operator<< (std::ostream &s,Quadrinome<S1,S2,S3,S4> &c);
        
         template<typename S1, typename S2, typename S3, typename S4>
        friend std::ostream& operator<< (std::ostream &s,Quadrinome<S1,S2,S3,S4>* c);
        
        T4 get_fourth();
        void set_fourth(T4);
   
};

template<typename T1, typename T2, typename T3, typename T4>
Quadrinome<T1,T2,T3,T4>::Quadrinome() : Trinome<T1,T2,T3>(), fourth(T4()) {}

template<typename T1, typename T2, typename T3, typename T4>
Quadrinome<T1,T2,T3,T4>::Quadrinome(T1 one, T2 two, T3 three, T4 four) : Trinome<T1,T2,T3>(one,two,three), fourth(four) {}

template<typename T1, typename T2, typename T3, typename T4>
Quadrinome<T1,T2,T3,T4>::Quadrinome(const Quadrinome<T1,T2,T3,T4>& quad) : Trinome<T1,T2,T3>(quad), fourth(quad.fourth) {}

template<typename S1, typename S2, typename S3, typename S4>
std::ostream& operator <<(std::ostream &s,Quadrinome<S1,S2,S3,S4> &c){
	/* affchage d'un Quadrinome */
	
	S1 one = c.get_first();
    S2 two = c.get_second();
    S3 three = c.get_third();
    S4 four = c.get_fourth();
	
    s<<"Quadrinome("<<one<<","<<two<<","<<three<<","<<four<<")";
    return s;
}

template<typename S1, typename S2, typename S3, typename S4>
std::ostream& operator <<(std::ostream &s,Quadrinome<S1,S2,S3,S4>* c){
	/* affchage d'un Quadrinome */
    s<<(*c);
    return s;
}

template<typename T1, typename T2, typename T3, typename T4>
T4 Quadrinome<T1,T2,T3,T4>::get_fourth(){return this->fourth;}

template<typename T1, typename T2, typename T3, typename T4>
void Quadrinome<T1,T2,T3,T4>::set_fourth(T4 fou){this->fourth = fou;}
