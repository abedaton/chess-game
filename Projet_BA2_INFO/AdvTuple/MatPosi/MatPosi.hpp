
#include <iostream>
#include <utility>
#include <sstream>

#include "Posi/Posi.cpp"

class MatPosi: public Posi{
	public:
        MatPosi(int,int); //*< Constructor
        MatPosi(std::pair<int,int>); //*< Constructor
        MatPosi(std::string); //*< Constructor
        MatPosi() noexcept = default; //*< Constructor
        ~MatPosi() noexcept = default; //Destructor
        MatPosi(const MatPosi&) noexcept = default;
        MatPosi(const Posi&);
        MatPosi& operator= (const MatPosi&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,MatPosi &c);
        friend std::ostream& operator<< (std::ostream &s,MatPosi* c);
        
        int get_col() const;
        int get_lig() const;
        
        void set_col(int);
        void set_lig(int);
        
        std::string to_string();
        std::pair<int,int> to_pair();
        
        bool operator<( const MatPosi&) const;
        bool operator<=( const MatPosi&) const;
        bool operator>( const MatPosi&) const;
        bool operator>=( const MatPosi&) const;
        
        bool operator<( const MatPosi*) const;
        bool operator<=( const MatPosi*) const;
        bool operator>( const MatPosi*) const;
        bool operator>=( const MatPosi*) const;
        
        private:
			std::string get_alphabet();
        
};
