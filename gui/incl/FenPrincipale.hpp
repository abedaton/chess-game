#ifndef FENPRINCIPALE_HPP
#define FENPRINCIPALE_HPP
#include "Menu.hpp"
#include "GameWindow.hpp"
#include "Login.hpp"
#include "PlateauScene.hpp"
#include "Register.hpp"
#include "Chat.hpp"
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
    void goToMenu();
    void sendMessage();

    private:
    void init_window();
    void init_connect();
    void init_stack();
    void init_dock();
    QMenu *_menuReglages;
    QStatusBar *_statusBar;
    QStackedWidget *_stack;
    QDockWidget *_dockChat;

    Login *_login;
    Register *_register;
    Menu *_menu;
    GameWindow *_gameWindow;
    PlateauScene *_classicWindow;
    Chat *_chat;
};

#endif // FENPRINCIPALE_HPP