#include "../Serveur.cpp"

MyOstream mout("logfile.txt");

int main(){
    Serveur serveur("0.0.0.0", 5555);
    return 0;
}
