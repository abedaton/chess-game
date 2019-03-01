#include "client.hpp"

int main(int argc, char *argv[]){
    if(argc > 1)
    {	Client* client = new Client();
    	client->Run(argv[1]);
    }
    else
    	std::cout << "name parameter required " << std::endl;
    return 0;
}
