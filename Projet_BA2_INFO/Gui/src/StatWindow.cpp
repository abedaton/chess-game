#include "./Gui/incl/StatWindow.hpp"

StatWindow::StatWindow(QWidget *parent) : QWidget(parent){
    init_window();
    init_layout();
}

void StatWindow::init_window(){
    _search = new QLineEdit(this);
    _search->setPlaceholderText(QString("Search player..."));
    _gbox = new QGridLayout(this);

    _textEdit = new QTextEdit(this);
    _textEdit->setReadOnly(true);


}

void StatWindow::init_layout(){
    _gbox->addWidget(_search,0,2,1,5);
    _gbox->addWidget(_textEdit,1,3,5,5);
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
    }
}
