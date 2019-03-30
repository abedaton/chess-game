#ifndef GAMEWINDOW_CPP
#define GAMEWINDOW_CPP
#include "GameWindow.hpp"

GameWindow::GameWindow(QWidget *parent) : QWidget(parent) {
    init_widget();
    init_layout();
}

void GameWindow::init_widget() {
    _classicButton = new QPushButton("Classic Chess", this);
    _darkButton = new QPushButton("Dark Chess", this);
    _trapistButton = new QPushButton("Trapist Chess", this);
    _antiButton = new QPushButton("Anti Chess", this);
    _exitButton = new QPushButton("Exit", this);
    _launchGame = new QPushButton("Launch", this);
    _comboBoxMode = new QComboBox(this);
    _comboBoxMode->addItem("Classic");
    _comboBoxMode->addItem("Pendulum");
    _comboBoxMode->addItem("Real time");

}

void GameWindow::init_layout() {
    _gbox = new QGridLayout;
    _gbox->addWidget(_classicButton, 0, 1);
    _gbox->addWidget(_darkButton, 0, 2);
    _gbox->addWidget(_trapistButton, 1, 1);
    _gbox->addWidget(_antiButton, 1, 2);
    _gbox->addWidget(_comboBoxMode, 2, 1);
    _gbox->addWidget(_exitButton, 2, 2);
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
int GameWindow::getCurrentGameMode(){
    //std::cout << _comboBoxMode->currentText().toStdString() << std::endl;
    std::string gameMode = _comboBoxMode->currentText().toStdString();
    if(gameMode == "Classic")
        return 0;
    else if(gameMode == "Pendulum")
        return 1;
    else
        return 2;
}
#endif