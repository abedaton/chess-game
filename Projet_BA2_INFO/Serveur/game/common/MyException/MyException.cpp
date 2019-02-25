
#include "MyException.hpp"

MyException::MyException(MyOstream* st,std::string txt) : texte(txt), stream(st) {
	this->stream->log_only("MyException(");
	this->stream->log_only(this->texte);
	this->stream->log_only(")",true);
} //*< Constructor

MyException::MyException(const MyException& ex) : texte(ex.texte) , stream(ex.stream) {}

MyException::~MyException() throw () {} // Updated

const char* MyException::what() const throw() {return this->texte.c_str();}
