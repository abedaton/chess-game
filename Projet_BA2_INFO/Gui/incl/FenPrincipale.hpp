#ifndef FENPRINCIPALE_HPP
#define FENPRINCIPALE_HPP
#include "Chat.hpp"
#include "GameWindow.hpp"
#include "Login.hpp"
#include "Menu.hpp"
#include "Timer.hpp"
#include "PlateauScene.hpp"
#include "Register.hpp"
#include <QtWidgets>
#include <iostream>

#include "../../Client/includes/abstractInterface.hpp"
#include "../../Client/includes/abstractClient.hpp"

class FenPrincipale : public QMainWindow, public AbstractInterface{
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

//////////////////////////////tmp
    void myShow() override{this->show();}
    void gameStart(std::string opponent) override{}
    void connectionError() override{}
    void win() override{}
    void lose() override{}
	void recvMessage(std::string name, std::string mov) override{}
    void pingForUpdate() override{}
    

    private:
    void init_window();
    void init_connect();
    void init_stack();
    void init_dock();
    QMenu *_menuReglages;
    QStatusBar *_statusBar;
    QStackedWidget *_stack;
    QDockWidget *_dockChat;
    QDockWidget *_dockTimer;

    AbstractClient* _client;

    Login *_login;
    Register *_register;
    Menu *_menu;
    GameWindow *_gameWindow;
    PlateauScene *_classicWindow;
    Chat *_chat;
    Timer *_timer;

};

#endif // FENPRINCIPALE_HPP
