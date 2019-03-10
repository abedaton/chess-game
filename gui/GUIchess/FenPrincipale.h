#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H
#include <QtWidgets>
#include "Login.h"
#include "Register.h"
#include "GameWindow.h"
#include "PlateauScene.h"
#include <iostream>

class FenPrincipale : public QMainWindow{

    Q_OBJECT

public:
    FenPrincipale();
    void MenuBar();

public slots:
    void checkSignIn();
    void checkRegister();
    void goToRegister();
    void goToLogIn();
    void goToGame();
private:
    QMenu* _menuReglages;
    QStatusBar *_statusBar;
    Login* _login;
    Register* _register;
    QStackedWidget* _stack;
    GameWindow* _gameWindow;
};


#endif // FENPRINCIPALE_H
