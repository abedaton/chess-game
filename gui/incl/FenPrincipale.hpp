#ifndef FENPRINCIPALE_HPP
#define FENPRINCIPALE_HPP
#include "FriendList.hpp"
#include "Chat.hpp"
#include "GameWindow.hpp"
#include "Login.hpp"
#include "Menu.hpp"
#include "Pendulum.hpp"
#include "PlateauScene.hpp"
#include "Register.hpp"
#include "Publicity.hpp"
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
    void addFriend();
    void removeFriend();

    private:
    void init_window();
    void init_connect();
    void init_stack();
    void init_dock();
    QMenu *_menuReglages;
    QStatusBar *_statusBar;
    QStackedWidget *_stack;
    QDockWidget *_dockChat;
    QDockWidget *_dockPendulum;
    QDockWidget *_dockAdvertisement;

    FriendList *_friendList;
    Login *_login;
    Register *_register;
    Menu *_menu;
    GameWindow *_gameWindow;
    PlateauScene *_classicWindow;
    Chat *_chat;
    Pendulum *_pendulum;
    Publicity *_advertisement;
};

#endif // FENPRINCIPALE_HPP
