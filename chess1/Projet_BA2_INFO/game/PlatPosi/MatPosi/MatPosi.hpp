#pragma once
#ifndef MATPOSI_HPP
#define MATPOSI_HPP
#include <iostream>
#include <utility>
#include <sstream>

#include "Posi/Posi.cpp"
#include "../../Interpret/Interpret.cpp"

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
        
        bool isvalid_coord(std::string) const;
        
	private:
		std::string get_letter_part_of_string(std::string) const ;
		std::string get_number_part_of_string(std::string) const ;
		
		std::string get_alphabet() const ;
		std::size_t get_col_from_string(std::string) const ;
		int get_lig_from_string(std::string) const ;
        
};
#endif
