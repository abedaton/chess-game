#pragma once
#ifndef MENU_HPP
#define MENU_HPP

#include <QtWidgets>

class Menu : public QWidget {
    Q_OBJECT

    public:
    explicit Menu(QWidget *parent = nullptr);
    QPushButton *getNewGame() const;
    QPushButton *getExit() const;

    private:
    void init_pushButton();
    void init_layout();

    QPushButton *_newGame;
    QPushButton *_exit;

    QVBoxLayout *_vBoxLayoutMenu;
};

#endif // MENU_HPP