#include "Menu.hpp"

Menu::Menu(QWidget *parent) : QWidget(parent) {
    init_pushButton();
    init_layout();
}

void Menu::init_pushButton() {
    _newGame = new QPushButton("New Game", this);
    _exit = new QPushButton("Exit", this);
    _stat = new QPushButton("Statistics", this);
}

void Menu::init_layout() {
    _vBoxLayoutMenu = new QVBoxLayout(this);
    _vBoxLayoutMenu->addWidget(_newGame);
    _vBoxLayoutMenu->addWidget(_stat);
    _vBoxLayoutMenu->addWidget(_exit);

    setLayout(_vBoxLayoutMenu);
}

QPushButton *Menu::getNewGame() const{
    return _newGame;
}

QPushButton *Menu::getExit() const{
    return _exit;
}

QPushButton *Menu::getStat() const{
    return _stat;
}
