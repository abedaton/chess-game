
#include <iostream>
#include <string>

#include "../../PlatPosi/MatPosi/Posi/Posi.cpp"
#include "../../common/MyException/MyOstream/MyOstream.hpp"

MyOstream mout("logfile.txt");
 
int main(){
	std::string texte;
	texte = "Hello Worlds!";
	mout << texte << std::endl;
			
	mout <<"HI!" << std::endl;
	
	Posi* pos = new Posi(3,2);
	
	mout << (*pos).get_x() << std::endl;

}
