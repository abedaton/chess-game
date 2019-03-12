#include "srcs/client.cpp"

MyOstream mout("logfile.txt");

int main(int argc,char** argv){
    if (argc > 1){
        new Client(argv[1]);
    } else {
        Client* client = new Client("127.0.0.1");
    }
    return 0;
}
