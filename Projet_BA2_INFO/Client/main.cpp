#include "srcs/client.cpp"

MyOstream mout("logfile.txt");

int main(int argc,char** argv){
    if (argc > 2){
        Client* client = new Client(argv[1] , true, argc, argv); //CHAMGEMENT HERE
    } else {
        Client* client = new Client("127.0.0.1", false, 0, nullptr);
    }
    return 0;
}
