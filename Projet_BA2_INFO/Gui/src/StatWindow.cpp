#include "./Gui/incl/StatWindow.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

StatWindow::StatWindow(AbstractClient* client): _client(client){
    init_window();
    init_layout();
}



void StatWindow::init_window(){
    _search = new QLineEdit;
    _search->setPlaceholderText(QString("Search player..."));

    _textEdit = new QTextEdit;
    _textEdit->setReadOnly(true);

    _exitButton = new QPushButton("Exit");

    _gbox = new QGridLayout;

}

void StatWindow::init_layout(){
    _gbox->addWidget(_search,0,2,1,5);
    _gbox->addWidget(_textEdit,1,2,5,5);
    _gbox->addWidget(_exitButton,2,7);
    this->setLayout(_gbox);


}

void StatWindow::setUserInfo(std::string name, int nbrGame, int statWin, int statElo)
{
    _clientStateName =  name;
    _statNbrGames = nbrGame;
    _statWin = statWin;
    _statElo = statElo;
    _infoReceived = true;
}

//Affiche les stats dans le textedit
void StatWindow::showPlayerStats(){
    /*if (_search->text().isEmpty()){
        //Check dans la data base les stats du joueur connecté
        //getUserInfo();
    } else {
        //_lineEdit->text() et on cherche dans la database
        //getUserInfo(_lineEdit->text().toStdString())
        //et après on show les 6 stats avec les 3 recu
    }*/

    std::string tmp = "Parties Jouées: " + std::to_string(_statNbrGames);
    _textEdit->setText("Nom: " + _search->text());

    _textEdit->append(QString::fromStdString(tmp)); 
    tmp = "Parties gagnées: "+ std::to_string(_statWin);
    
    _textEdit->append(QString::fromStdString(tmp));
    tmp = "Elo: "+ std::to_string(_statElo);
    _textEdit->append(QString::fromStdString(tmp));
}


void StatWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return) {
        emit enterPressed();
        
        _infoReceived = false;
        _client->getUserInfo(_search->text().toStdString()); 
        int timeoutCounter = 0;
        while(_infoReceived == false || timeoutCounter < 20)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            timeoutCounter++;
        }
           
        //le serveur ne répond pas
        if(_infoReceived == false)
        {
            std::cout << "info wasn't receivede" << std::endl;
            _statNbrGames = 0;
            _statWin=0;
            _statElo = 0;
        }


        showPlayerStats();    
    }
}

QPushButton* StatWindow::getExitButton(){
    return _exitButton;
}