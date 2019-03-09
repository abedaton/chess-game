#include "GameWindow.h"

GameWindow::GameWindow(){
    _classicButton = new QPushButton("Classic Chess");
    _darkButton = new QPushButton("Dark Chess");
    _trapistButton = new QPushButton("Trapist Chess");
    _antiButton = new QPushButton("Anti Chess");

    _gbox = new QGridLayout;

    _gbox->addWidget(_classicButton,0,0,8,4);
    _gbox->addWidget(_darkButton,4,0,8,4);
    _gbox->addWidget(_trapistButton,0,4,8,4);
    _gbox->addWidget(_antiButton,4,4,8,4);

    this->setLayout(_gbox);

}
