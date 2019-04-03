#pragma once
#ifndef CSVREADER_CPP
#define CSVREADER_CPP
#include "CsvReader.hpp"

extern MyOstream mout;

// ----------HORS CsvReader------------------------------------------------------------------------------------------

enum class CSVState {
    UnquotedField,
    QuotedField,
    QuotedQuote
};

std::vector<std::string> readCSVRow(const std::string &row) {
    CSVState state = CSVState::UnquotedField;
    std::vector<std::string> fields {""};
    size_t i = 0; // index of the current field
    for (char c : row) {
        switch (state) {
            case CSVState::UnquotedField:
                switch (c) {
                    case ';': // end of field
                              fields.push_back(""); i++;
                              break;
                    case '"': state = CSVState::QuotedField;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedField:
                switch (c) {
                    case '"': state = CSVState::QuotedQuote;
                              break;
                    default:  fields[i].push_back(c);
                              break; }
                break;
            case CSVState::QuotedQuote:
                switch (c) {
                    case ';': // , after closing quote
                              fields.push_back(""); i++;
                              state = CSVState::UnquotedField;
                              break;
                    case '"': // "" -> "
                              fields[i].push_back('"');
                              state = CSVState::QuotedField;
                              break;
                    default:  // end of quote
                              state = CSVState::UnquotedField;
                              break; }
                break;
        }
    }
    return fields;
}

/// Read CSV file, Excel dialect. Accept "quoted fields ""with quotes"""
std::vector<std::vector<std::string>> readCSV(std::istream &in) {
    std::vector<std::vector<std::string>> table;
    std::string row;
    while (!in.eof()) {
        std::getline(in, row);
        if (in.bad() || in.fail()) {
            break;
        }
        auto fields = readCSVRow(row);
        table.push_back(fields);
    }
    return table;
}
	
std::vector<std::vector<std::string>> invert_tableau(std::vector<std::vector<std::string>> tab){
	
	std::vector<std::vector<std::string>>* new_tab = new std::vector<std::vector<std::string>>();
	for(long long unsigned int i=0;i<tab.size();i++){
		for(long long unsigned int j=0;j<tab[i].size();j++){
			
			if (i==0){
				std::vector<std::string>* new_row = new std::vector<std::string>();
				for(long long unsigned int k=0;k<tab.size();k++){
					new_row->push_back("");
					}
				new_tab->push_back(*(new_row));	
			}
			
			(*(new_tab))[j][i] = tab[i][j];
			
		}
	}
	
	return *(new_tab);
}

void affichage_tableau(std::vector<std::vector<std::string>> tab){
	
	mout<<"[";
	for(long long unsigned int i=0;i<tab.size();i++){
		mout<<"[";
		for(long long unsigned int j=0;j<tab[i].size();j++){
			mout<<tab[i][j];
			if (j != tab[i].size()-1){mout<<", ";}
			
		}
		
		mout<<"]";
		if (i != tab.size()-1){mout<<", "<<std::endl;}
	}
	mout<<"]"<<std::endl;
	
}

// ------------CsvReader--------------------------------------------------------------------------------------------

CsvReader::CsvReader() : tab(std::vector<std::vector<std::string>>()) {} //*< Constructor

std::ostream& operator <<(std::ostream &s,CsvReader &c){
	/* affchage d'un CsvReader */
	(void)c;
    s<<"CsvReader()";
    return s;
}

std::ostream& operator <<(std::ostream &s,CsvReader* c){
	/* affchage d'un CsvReader */
    s<<(*c);
    return s;
}

std::vector<std::vector<std::string>> CsvReader::get_tableau(){return this->tab;}

void CsvReader::load(std::string filename){
	
	std::vector<std::vector<std::string>> res_csv;
	std::vector<std::vector<std::string>> inv_csv;
	std::ifstream myfile (filename);
	res_csv = readCSV(myfile);
	
	myfile.close();
	
	inv_csv = invert_tableau(res_csv);
	
	this->tab = inv_csv;
	
}

std::vector<std::string> CsvReader::get_hor_legende(){
	
	std::vector<std::string>* legende = new std::vector<std::string>();
	for(long long unsigned int i=0;i<this->get_tableau().size();i++){
		legende->push_back(this->get_tableau()[i][0]);
	}
	
	return *legende;

}

std::vector<std::string> CsvReader::search_col(std::string langue){
	
	std::vector<std::string> legende;
	std::vector<std::string> lang_vect;
	bool lang_found = false;
	
	legende = this->get_hor_legende();
	long long unsigned int i = 0;
	while (i<this->get_tableau().size() and lang_found == false){
		if (this->get_tableau()[i][0] == langue){
			lang_vect = this->get_tableau()[i];
			lang_found = true;
		}
			
		i++;
	}
		
	return lang_vect;
	
}

#endif