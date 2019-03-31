#pragma once

#ifndef FENPRINCIPALE_HPP
#define FENPRINCIPALE_HPP

#include "FriendList.hpp"
#include "Publicity.hpp"
#include "Chat.hpp"
#include "GameWindow.hpp"
#include "Login.hpp"
#include "Menu.hpp"
#include "Timer.hpp"
#include "PlateauScene.hpp"
#include "Register.hpp"
#include "StatWindow.hpp"
#include "MatchmakingDialog.hpp"

#include <QtWidgets>
#include <QThread>
#include <iostream>

#include "../../Client/includes/abstractInterface.hpp"
#include "../../Client/includes/abstractClient.hpp"

class PlateauScene;
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
    void goToTrappist();
    void goToMenu();
    void goToStat();
    void goToMatchmaking();
    void sendMessage();
    void showFriendList();
    void setTheme(std::string pool);
    void addFriend();
    void removeFriend();
    void getFriendListItem(QListWidgetItem *item);
    void getMenuFriendListAction(QAction *action);

    AbstractClient* getTest();

    int getWichMatchmaking(std::string variante);

    void setFriendMenu();
    void setThemeMenu();

    void setPool0();
    void setPool1();
    void setPool2();
    void setPool3();
    void setPool4();

    void sendPosition(std::string pos);


//////////////////////////////tmp
    void myShow() override{this->show();}
    void gameStart(std::string opponent) override;
    void connectionError() override{}
	void recvMessage(std::string name, std::string mov) override{(void)name;(void)mov;}
    

    private:
    void init_window();
    void init_connect();
    void init_stack();
    void init_dock();
    void init_menu();

    QThread* _thread;

    QMenu *_menuReglages;
    QMenu *_menuAmis;
    QMenu *_menuThemes;
    QMenu *_menuFriendList;

    QStatusBar *_statusBar;
    QStackedWidget *_stack;
    QDockWidget *_dockChat;
    QDockWidget *_dockTimer;
    QDockWidget *_dockFriendList;
    QDockWidget *_dockPublicity;
    AbstractClient* _client;

    FriendList *_friendList;
    Publicity *_publicity; 
    Login *_login;
    Register *_register;
    Menu *_menu;
    GameWindow *_gameWindow;
    PlateauScene *_classicWindow;
    StatWindow* _statWindow;
    Chat *_chat;
    Timer *_timer;

    std::string _pool;

    MatchmakingDialog* _mdial;


};

#endif // FENPRINCIPALE_HPP
