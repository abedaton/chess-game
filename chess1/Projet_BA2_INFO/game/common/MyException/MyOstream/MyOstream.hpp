#pragma once
#ifndef MYOSTREAM_HPP
#define MYOSTREAM_HPP
#include <iostream>
#include <string>
#include <fstream>

class MyOstream{
	private:
		std::ofstream my_fstream;
		
	public:
		MyOstream(std::string name);
		
		template<typename T>
		MyOstream& operator<<(T);
		
		// for manipulators like std::endl
		typedef std::ostream& (*stream_function)(std::ostream&);
		
		MyOstream& operator<<(stream_function func);
		
		template<typename T>
		void log_only(T,bool);
		
		template<typename T>
		void log_only(T);
};

MyOstream::MyOstream(std::string name) : my_fstream(name) {}
// check if opening file succeeded!!
//MyOstream() : my_fstream("some_file.txt") {}; // check if opening file succeeded!!
// for regular output of variables and stuff

template<typename T>
MyOstream& MyOstream::operator<<(T something){
	std::cout << something;
	my_fstream << something;
	return *this;
}

MyOstream& MyOstream::operator<<(stream_function func){
	func(std::cout);
	func(my_fstream);
	return *this;
}
		
template<typename T>
void MyOstream::log_only(T something,bool endline){
	my_fstream << something;
	if (endline == true){my_fstream << std::endl;}
}
		
template<typename T>
void MyOstream::log_only(T something){
	this->log_only(something,false);
}
#endif
