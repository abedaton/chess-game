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
    _LaunchGame = new QPushButton("Launch", this);
    _comboBoxMode = new QComboBox(this);
    _comboBoxMode->addItem("Classic");
    _comboBoxMode->addItem("Real time");
    _comboBoxMode->addItem("Pendulum");
}

void GameWindow::init_layout() {
    _gbox = new QGridLayout;
    _gbox->addWidget(_comboBoxMode, 0, 0);
    _gbox->addWidget(_LaunchGame, 1, 0);
    _gbox->addWidget(_classicButton, 0, 1);
    _gbox->addWidget(_darkButton, 0, 2);
    _gbox->addWidget(_trapistButton, 1, 1);
    _gbox->addWidget(_antiButton, 1, 2);
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
