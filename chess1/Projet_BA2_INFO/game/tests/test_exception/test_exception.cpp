
//#include <iostream>
//#include <string>

#include "../../common/MyException/MyException.cpp"

MyOstream mout("logfile.txt");

int main(){
	mout<<"before myexception"<<std::endl;
	
	try{
		throw MyException(&mout,"MY EXECPT!");
		mout<<"after myexception"<<std::endl;
	}
	catch(MyException& e){
		mout<<e.what()<<std::endl;
		mout<<"myexception catched"<<std::endl;
	}
	
	return 0;
}
