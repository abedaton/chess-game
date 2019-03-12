#include "Register.h"
#include <iostream>

Register::Register(QWidget *parent) : QWidget(parent){
    _fbox = new QFormLayout;
    _vbox = new QVBoxLayout;
    _hbox = new QHBoxLayout;

    _OKButton = new QPushButton("OK",this);
    _CanButton = new QPushButton("Cancel",this);

    _nom = new QLineEdit(this);
    _fbox->addRow("Username :", _nom);
    _email = new QLineEdit(this);
    _fbox->addRow("E-mail :", _email);
    _mdp1 = new QLineEdit(this);
    _mdp1->setEchoMode(QLineEdit::Password);
    _fbox->addRow("Password :", _mdp1);
    _mdp2 = new QLineEdit(this);
    _fbox->addRow("Password (again) :", _mdp2);
    _mdp2->setEchoMode(QLineEdit::Password);

    _hbox->addWidget(_OKButton);
    _hbox->addWidget(_CanButton);

    _vbox->addLayout(_fbox);
    _vbox->addLayout(_hbox);
    this->setLayout(_vbox);
}

QPushButton* Register::getCancel() const{
    return _CanButton;
}


QPushButton* Register::getOK() const{
    return _OKButton;
}

bool Register::isSamePassword() const{
    return (_mdp1->text() == _mdp2->text());
}

bool Register::isTextEmpty() const{
    return (_nom->text().isEmpty() && _email->text().isEmpty() && _mdp1->text().isEmpty() && _mdp2->text().isEmpty() );
}

void Register::keyPressEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_Return){
        emit enterPressed();
    }
    else if(event->key() == Qt::Key_Escape){
        emit escapePressed();
    }
}
