
#include <iostream>
#include <string>
#include <istream>
#include <string>
#include <vector>
#include <fstream>

#include "../../../common/common.cpp"

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
