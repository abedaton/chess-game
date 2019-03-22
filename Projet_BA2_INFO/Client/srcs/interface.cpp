//JUSTE POUR TEST

#include "../includes/interface.hpp"

Graphic::Graphic(AbstractClient* client, int argc, char** argv):  _client(client) {
    makeGui(argc,argv);
    //TO DO
}

Graphic::~Graphic(){
    ;; //TO DO
}
void Graphic::connectionError(){
    ;; //TO DO
}

void Graphic::gameStart(std::string opponent){
    ;; //TO DO
}

void Graphic::recvMessage(std::string name, std::string mov){
    ;; //TO DO
}

void Graphic::pingForUpdate(){
    ;; //TO DO
}
void Graphic::win(){
    ;; //TO DO
}
void Graphic::lose(){
    ;; //TO DO
}

int Graphic::makeGui(int argc, char** argv){
    QApplication app(argc, argv);

    FenPrincipale* _gui = new FenPrincipale();
    
    _gui->_graphic = this;

    _gui->show();

    return app.exec(); 
}

bool Graphic::loginGUI(std::string username,std::string password){
    bool res = _client->login(username, password);
    return res;
}