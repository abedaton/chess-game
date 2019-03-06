#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QStatusBar>
#include "gamewindow.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushButtonSignIn_clicked();

    void on_pushButtonRegister_clicked();

private:
    Ui::Login *ui;
    GameWindow *gameWindow;
    QStatusBar *statusBar;
};

#endif // LOGIN_H
