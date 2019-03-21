#include "Login.hpp"

Login::Login(QWidget *parent) : QWidget(parent) {
    init_pushButton();
    init_lineEdit();
    init_layout();
}

void Login::init_pushButton() {
    _SIButton = new QPushButton("Sign In", this);
    _RegiButton = new QPushButton("Register", this);
}

void Login::init_lineEdit() {
    _nom = new QLineEdit(this);
    _mdp = new QLineEdit(this);
    _mdp->setEchoMode(QLineEdit::Password);
}

void Login::init_layout() {
    _formLayout = new QFormLayout;
    _formLayout->addRow("Username :", _nom);
    _formLayout->addRow("Password :", _mdp);

    _hbox = new QHBoxLayout;
    _hbox->addWidget(_SIButton);
    _hbox->addWidget(_RegiButton);

    _vbox = new QVBoxLayout;
    _vbox->addLayout(_formLayout);
    _vbox->addLayout(_hbox);

    this->setLayout(_vbox);
}

void Login::on_signIn() {
    ;
    ;
}

void Login::on_register() {
    ;
    ;
}

QPushButton *Login::getSI() const {
    return _SIButton;
}

QPushButton *Login::getRegister() const {
    return _RegiButton;
}

QString Login::getUsername() const {
    return _nom->text();
}

QString Login::getPassword() const {
    return _mdp->text();
}

void Login::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return) {
        emit enterPressed();
    }
}
