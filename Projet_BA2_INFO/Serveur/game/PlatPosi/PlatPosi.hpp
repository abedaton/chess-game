#pragma once
#ifndef PLATPOSI_HPP
#define PLATPOSI_HPP
#include <iostream>
#include <utility>
#include <sstream>

#include "MatPosi/MatPosi.cpp"

class PlatPosi: public MatPosi{
	private:
		BitypeVar<int> row_size;
	
	public:
        PlatPosi(int,int); //*< Constructor
        PlatPosi(std::pair<int,int>); //*< Constructor
        PlatPosi(std::string); //*< Constructor
        PlatPosi(int,BitypeVar<int>,BitypeVar<int>); //*< Constructor
        PlatPosi() noexcept = default; //*< Constructor
        
        ~PlatPosi() noexcept = default; //Destructor
        PlatPosi(const PlatPosi&) noexcept = default;
        PlatPosi(const MatPosi&);
        PlatPosi& operator= (const PlatPosi&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,PlatPosi &c);
        friend std::ostream& operator<< (std::ostream &s,PlatPosi* c);
        
        int to_sum_val();
        bool isvalid_coord(std::string);// override;
        
    private:
		int get_row_size() const;
		void set_row_size(BitypeVar<int>);
		
		bool is_in_plat(int,int,int);
		bool is_in_plat();
		void check_if_out_plat();
        
};
#endif
