#pragma once
#ifndef POSI_HPP
#define POSI_HPP
#include <iostream>
#include <utility>

class Posi{
    private:
		int x;
		int y;
	
	public:
        Posi(int,int); //*< Constructor
        Posi(std::pair<int,int>); //*< Constructor
        Posi() noexcept = default; //*< Constructor
        ~Posi() noexcept = default; //Destructor
        Posi(const Posi&) noexcept = default;
        Posi& operator= (const Posi&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,Posi &c);
        friend std::ostream& operator<< (std::ostream &s,Posi* c);
        
        int get_x() const;
        int get_y() const;
        
        void set_x(int);
        void set_y(int);
        
        bool operator==( const Posi&) const;
        bool operator!=( const Posi&) const;
        
        bool operator==( const Posi*) const;
        bool operator!=( const Posi*) const;
        
};
#endif
