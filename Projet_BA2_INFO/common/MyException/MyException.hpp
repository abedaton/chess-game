
#include <iostream>
#include <string>
#include <exception>

#include "MyOstream/MyOstream.hpp"

class MyException: public std::exception{
	private:
		std::string texte;
		MyOstream* stream;
		
	public:
		MyException(MyOstream*,std::string);
		MyException(const MyException&);// noexcept = default;
		~MyException(); // Updated
		MyException& operator= (const MyException&) noexcept = default;
		const char* what() const throw() override;
};
