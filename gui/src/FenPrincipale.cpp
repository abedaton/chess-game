#include "FenPrincipale.h"

FenPrincipale::FenPrincipale() {
    _stack = new QStackedWidget(this);
    _statusBar = new QStatusBar(this);
    _register = new Register(this);
    _login = new Login(this);
    _gameWindow = new GameWindow(this);

    init_window();
    init_connect();
    init_stack();

    setCentralWidget(_stack);
    goToLogIn();
}

void FenPrincipale::init_window() {
    setWindowTitle("On Veut Pas D'Échec");
    resize(QDesktopWidget().availableGeometry(this).size() * 0.5);
    setStatusBar(_statusBar);
    MenuBar();
}

void FenPrincipale::init_connect() {
    connect(_login->getSI(), SIGNAL(clicked()), this, SLOT(checkSignIn()));
    connect(_login, SIGNAL(enterPressed()), this, SLOT(checkSignIn()));
    connect(_login->getRegister(), SIGNAL(clicked()), this, SLOT(goToRegister()));
    connect(_register->getCancel(), SIGNAL(clicked()), this, SLOT(goToLogIn()));
    connect(_register, SIGNAL(escapePressed()), this, SLOT(goToLogIn()));
    connect(_register->getOK(), SIGNAL(clicked()), this, SLOT(checkRegister()));
    connect(_register, SIGNAL(enterPressed()), this, SLOT(checkRegister()));
    connect(_gameWindow->getClassicButton(), SIGNAL(clicked()), this, SLOT(goToClassic()));
}

void FenPrincipale::init_stack() {
    _stack->addWidget(_login);
    _stack->addWidget(_register);
    _stack->addWidget(_gameWindow);
}

void FenPrincipale::MenuBar() {
    _menuReglages = menuBar()->addMenu("&Réglages");
    QAction *actionLangues = new QAction("&Langues", this);
    _menuReglages->addAction(actionLangues);
}

void FenPrincipale::checkSignIn() {
    QString nom = _login->getUsername();
    QString mdp = _login->getPassword();

    /*result = client->login(username, password)
     * if (username dont exist in dataBase)
     * Qmessage:: username invalide please register
     *
     */

    if (nom == "achraf" && mdp == "achraf") {
        goToGame();
        _statusBar->showMessage("Welcome " + nom + " !", 5000);
        // RAJOUTER LA TOUCHE ENTER

    } else {
        _statusBar->showMessage("Username or password is incorrect", 5000);
        QMessageBox::critical(this, "Incorrect SignIn", "Username and Password do not match");
    }
}

void FenPrincipale::checkRegister() {
    if (_register->isTextEmpty()) {
        QMessageBox::critical(this, "Incorrect Register", "Missing elements");
        _statusBar->showMessage("Missing elements");
    } else if (!_register->isSamePassword()) {
        QMessageBox::critical(this, "Incorrect Register", "Passwords do not match");
        _statusBar->showMessage("Passwords do not match");
    } else {
        goToGame();
        _statusBar->showMessage("Welcome new user !", 5000);
    }
}

void FenPrincipale::goToRegister() {
    _stack->setCurrentWidget(_register);
}

void FenPrincipale::goToLogIn() {
    _stack->setCurrentWidget(_login);
}

void FenPrincipale::goToGame() {
    _stack->setCurrentWidget(_gameWindow);
}

void FenPrincipale::goToClassic() {
    _classicWindow = new PlateauScene;
    _stack->addWidget(_classicWindow);
    _stack->setCurrentWidget(_classicWindow);
}
