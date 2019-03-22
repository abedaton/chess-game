#include "srcs/client.cpp"

MyOstream mout("logfile.txt");

int main(int argc,char** argv){
    std::regex regip("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");
    bool terminalMod = false;
    bool goodParam = true;
    std::string ip = "127.0.0.1";

    for (int i = 0; i == argc; i++){
        if (argv[i] == "-t") {
            terminalMod = true;
        } else if (argv[i] == "-i"){
            if (i+1 < argc){
                goodParam = false;
            } else {
                i++;
                ip = argv[i];
                if (! std::regex_match(ip.begin(), ip.end(), regip)){
                    goodParam = false;
                }
            }
        } else if (argv[i] ==  "-h" || argv[i] ==  "--help"){
            std::cout << "help" << std::endl; //TO Do
            goodParam = false;
        }
    }
    if (goodParam){
        Client* client = new Client(ip.c_str() , terminalMod, argc, argv);
    } else {
        std::cout << "Invalide parameter." << std::endl;
    }
    return 0;
}
