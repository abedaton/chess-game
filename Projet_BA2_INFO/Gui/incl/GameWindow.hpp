#pragma once
#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP

#include <QtWidgets>

class GameWindow : public QWidget {
    Q_OBJECT
    public:
    explicit GameWindow(QWidget *parent = nullptr);
    QPushButton *getClassicButton() const;
    QPushButton *getDarkButton() const;
    QPushButton *getTrapistButton() const;
    QPushButton *getAntiButton() const;

    private:
    void init_pushButton();
    void init_layout();

    QPushButton *_classicButton;
    QPushButton *_darkButton;
    QPushButton *_trapistButton;
    QPushButton *_antiButton;

    QGridLayout *_gbox;
};

#endif // GAMEWINDOW_HPP
