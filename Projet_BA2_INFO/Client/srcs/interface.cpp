//JUSTE POUR TEST

#include "../includes/interface.hpp"

Graphic::Graphic(AbstractClient* client, int argc, char** argv){
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

    FenPrincipale fenetre;
    fenetre.show();

    return app.exec(); 
}