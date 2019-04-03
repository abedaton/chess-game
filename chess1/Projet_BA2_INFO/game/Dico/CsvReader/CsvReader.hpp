/*
#include <iostream>
#include <string>
#include <string>
#include <vector>
#include <fstream>
*/

#pragma once
#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <istream>

#include "../../common/common.cpp"

enum class CSVState;
std::vector<std::string> readCSVRow(const std::string&);
std::vector<std::vector<std::string>> readCSV(std::istream&);
std::vector<std::vector<std::string>> invert_tableau(std::vector<std::vector<std::string>>);
void affichage_tableau(std::vector<std::vector<std::string>>);


class CsvReader{
    private:
		std::vector<std::vector<std::string>> tab;
	
	public:
        CsvReader(); //*< Constructor
        ~CsvReader() noexcept = default; //Destructor
        CsvReader(const CsvReader&) noexcept = default;
        CsvReader& operator= (const CsvReader&) noexcept = default;
        
        friend std::ostream& operator<< (std::ostream &s,CsvReader &c);
        friend std::ostream& operator<< (std::ostream &s,CsvReader* c);
        
        std::vector<std::vector<std::string>> get_tableau();
        void load(std::string);
        
        std::vector<std::string> get_hor_legende();
        
        std::vector<std::string> search_col(std::string);
};
#endif
