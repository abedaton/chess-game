#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H
#include "GameWindow.h"
#include "Login.h"
#include "PlateauScene.h"
#include "Register.h"
#include <QtWidgets>
#include <iostream>

class FenPrincipale : public QMainWindow {

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
    void goToClassic();

    private:
    void init_window();
    void init_connect();
    void init_stack();
    QMenu *_menuReglages;
    QStatusBar *_statusBar;
    Login *_login;
    Register *_register;
    QStackedWidget *_stack;
    GameWindow *_gameWindow;
    PlateauScene *_classicWindow;
};

#endif // FENPRINCIPALE_H
