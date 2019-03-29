#include "GameWindow.hpp"

GameWindow::GameWindow(QWidget *parent) : QWidget(parent) {
    init_pushButton();
    init_layout();
}

void GameWindow::init_pushButton() {
    _classicButton = new QPushButton("Classic Chess", this);
    _darkButton = new QPushButton("Dark Chess", this);
    _trapistButton = new QPushButton("Trapist Chess", this);
    _antiButton = new QPushButton("Anti Chess", this);
    _exitButton = new QPushButton("Exit", this);
}

void GameWindow::init_layout() {
    _gbox = new QGridLayout;
    _gbox->addWidget(_classicButton, 0, 0, 8, 4);
    _gbox->addWidget(_darkButton, 4, 0, 8, 4);
    _gbox->addWidget(_trapistButton, 0, 4, 8, 4);
    _gbox->addWidget(_antiButton, 4, 4, 8, 4);
    _gbox->addWidget(_exitButton,9,4);
    this->setLayout(_gbox);
}

QPushButton *GameWindow::getClassicButton() const {
    return _classicButton;
}

QPushButton *GameWindow::getDarkButton() const {
    return _darkButton;
}

QPushButton *GameWindow::getTrapistButton() const {
    return _trapistButton;
}

QPushButton *GameWindow::getAntiButton() const {
    return _antiButton;
}
QPushButton* GameWindow::getExitButton() const {
    return _exitButton;
}
