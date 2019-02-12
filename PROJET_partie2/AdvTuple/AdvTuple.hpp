
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>

#include "../Dico/Dico.cpp"
#include "MatPosi/MatPosi.cpp"

class AdvTuple{
    private:
		int x;
        int y;
        
        std::string depl_type;

        BitypeVar<int>* k_min;
        BitypeVar<int>* k_max;
        BitypeVar<std::pair<int,std::string>>* k_pas;
        
        bool update_needed;

	public:
        AdvTuple(); //*< Constructor
        AdvTuple(int,int,std::string); //*< Constructor
        AdvTuple(int,int,std::string,BitypeVar<int>*,BitypeVar<int>*,BitypeVar<std::pair<int,std::string>>*); //*< Constructor
        AdvTuple(int,int,std::string,BitypeVar<int>*,BitypeVar<int>*,BitypeVar<std::pair<int,std::string>>*,bool); //*< Constructor
        ~AdvTuple() noexcept = default; //Destructor
        AdvTuple(const AdvTuple&);// noexcept = default;
        AdvTuple& operator= (const AdvTuple&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,AdvTuple &c);
        friend std::ostream& operator<< (std::ostream &s,AdvTuple* c);
        
        int get_x();
        int get_y();
        std::string get_depl_type();
        
        void set_x(int);
        void set_y(int);
        void set_depl_type(std::string);
        
        BitypeVar<int>* get_k_min();
        BitypeVar<int>* get_k_max();
        BitypeVar<std::pair<int,std::string>>* get_k_pas();
        
        void set_k_min(BitypeVar<int>*);
        void set_k_max(BitypeVar<int>*);
        void set_k_pas(BitypeVar<std::pair<int,std::string>>*);
        
        void verify_k_pas();
        void verify_depl_type();
        
        bool need_update();
        void set_need_update(bool);
        
        std::vector<std::pair<int,int>>* get_res(int,Posi);

};
