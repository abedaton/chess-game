#include "FenPrincipale.h"



FenPrincipale::FenPrincipale()
{
    this->setWindowTitle("On Veut Pas D'Échec");
    this->resize(QDesktopWidget().availableGeometry(this).size() * 0.5);

    _stack = new QStackedWidget;
    _statusBar = new QStatusBar;
    _register = new Register;
    _login = new Login;
    _gameWindow = new GameWindow;

    _stack->addWidget(_login);
    _stack->addWidget(_register);
    _stack->addWidget(_gameWindow);


    goToLogIn();
    MenuBar();
    setCentralWidget(_stack);

    setStatusBar(_statusBar);

    QObject::connect(_login->getSI(), SIGNAL(clicked()), this, SLOT(checkSignIn()));
    QObject::connect(_login->getRegister(), SIGNAL(clicked()), this, SLOT(goToRegister()));

    QObject::connect(_register->getCancel(), SIGNAL(clicked()), this, SLOT(goToLogIn()));
    QObject::connect(_register->getOK(), SIGNAL(clicked()), this, SLOT(checkRegister()));



}

void FenPrincipale::MenuBar(){
    _menuReglages = menuBar()->addMenu("&Réglages");
        QAction *actionLangues = new QAction("&Langues", this);
        _menuReglages->addAction(actionLangues);

}

void FenPrincipale::checkSignIn(){
    QString nom = _login->getUsername();
    QString mdp = _login->getPassword();

    /*result = client->login(username, password)
     * if (username dont exist in dataBase)
     * Qmessage:: username invalide please register
     *
    */

    if(nom == "achraf" && mdp == "achraf"){
        // _statusBar->showMessage("Username and password are correct", 5000);
         QObject::connect(_login->getSI(), SIGNAL(clicked()), this, SLOT(goToGame()));

    }
    else{
         _statusBar->showMessage("Username or password is incorrect", 5000);
         QMessageBox::critical(this, "Incorrect SignIn", "Username and Password do not match");
    }

}

void FenPrincipale::checkRegister(){
    if( _register->isTextEmpty()){
        QMessageBox::critical(this, "Incorrect Register", "Missing elements");
        _statusBar->showMessage("Missing elements");
    }
    else if(! _register->isSamePassword()){
        QMessageBox::critical(this, "Incorrect Register", "Passwords do not match");
        _statusBar->showMessage("Passwords do not match");
    }
}

void FenPrincipale::goToRegister(){
    _stack->setCurrentWidget(_register);


}

void FenPrincipale::goToLogIn(){
    _stack->setCurrentWidget(_login);

}

void FenPrincipale::goToGame(){
    _stack->setCurrentWidget(_gameWindow);

}
