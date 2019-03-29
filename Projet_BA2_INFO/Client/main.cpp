#include "srcs/client.cpp"

MyOstream mout("logfile.txt");

int main(int argc,char** argv){
    std::regex regip("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");
    bool terminalMod = false;
    bool goodParam = true;
    std::string ip = "127.0.0.1";

    for (int i = 0; i < argc; i++){
        if (! strcmp(argv[i], "-t")) {
            terminalMod = true;
        } else if (! strcmp(argv[i], "-i")){
            if (i+1 < argc){
                goodParam = false;
            } else {
                i++;
                ip = argv[i];
                if (! std::regex_match(ip.begin(), ip.end(), regip)){
                    goodParam = false;
                }
            }
        } else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help")){
            std::cout << "Usage: ./cli [OPTION]\n\nOPTION:\n\t-t   start the game in terminal mod\n\t-i [4.2.1.127]   connect to a spécific ip" << std::endl; //TO Do
            goodParam = false;
        }
    }
    if (goodParam){
        Client* client = new Client(ip.c_str() , terminalMod, argc, argv);
        (void)(*client); // OK????
    } else {
        std::cout << "Invalide parameter.\nEnter './cli --help' for more information." << std::endl;
    }
    return 0;
}
