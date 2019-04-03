#include "srcs/Serveur.cpp"

MyOstream mout("logfile.txt");

int main(){
    Serveur serveur(5555); //"0.0.0.0" plus nécéssaire?
    return 0;
}
