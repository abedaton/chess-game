#include "./Gui/incl/StatWindow.hpp"

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

void StatWindow::showPlayerStats(){
    if (_search->text().isEmpty()){
        //Check dans la data base les stats du joueur connecté
        //getUserInfo();
    } else {
        //_lineEdit->text() et on cherche dans la database
        //getUserInfo(_lineEdit->text().toStdString())
        //et après on show les 6 stats avec les 3 recu
    }
}

void StatWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return) {
        std::cout << _search->text().toStdString() << std::endl;
        emit enterPressed();
        
          QString tmp = "Name: " + _search->text();
        _textEdit->setText(tmp);
        _textEdit->append("Wins: ");
        _client->getUserInfo(_search->text().toStdString()); 
       
       
    }
}

QPushButton* StatWindow::getExitButton(){
    return _exitButton;
}