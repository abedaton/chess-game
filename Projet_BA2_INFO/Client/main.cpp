#include "srcs/client.cpp"

MyOstream mout("logfile.txt");

int main(int argc,char** argv){
    if (argc > 1){
        Client* client = new Client(argv[1] , true);
    } else {
        Client* client = new Client("127.0.0.1", true);
    }
    return 0;
}
