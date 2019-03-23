#ifndef FENPRINCIPALE_HPP
#define FENPRINCIPALE_HPP
#include "Chat.hpp"
#include "GameWindow.hpp"
#include "Login.hpp"
#include "Menu.hpp"
#include "Pendulum.hpp"
#include "PlateauScene.hpp"
#include "Register.hpp"
#include <QtWidgets>
#include <iostream>

#include "../../Client/includes/abstractInterface.hpp"
#include "../../Client/includes/abstractClient.hpp"

class Client;
class FenPrincipale : public QMainWindow{

    Q_OBJECT

    public:
    FenPrincipale(AbstractClient* client);
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
    QDockWidget *_dockPendulum;

    AbstractClient* _client;

    Login *_login;
    Register *_register;
    Menu *_menu;
    GameWindow *_gameWindow;
    PlateauScene *_classicWindow;
    Chat *_chat;
    Pendulum *_pendulum;

};

#endif // FENPRINCIPALE_HPP
