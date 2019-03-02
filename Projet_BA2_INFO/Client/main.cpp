#include "srcs/client.cpp"

MyOstream mout("logfile.txt");

int main(){
    Client* client = new Client(); // "0.0.0.0" plus nécéssaire?
    return 0;
}
