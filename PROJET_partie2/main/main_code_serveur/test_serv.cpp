
#include <iostream>
#include <sstream>

#include "../../Serveur/Serveur.cpp"

MyOstream mout("logfile.txt");

int main(){
	
	Serveur* serv = new Serveur();
	serv->execute();
	
	return 0;
}
