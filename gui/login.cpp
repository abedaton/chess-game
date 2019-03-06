#include "login.h"
#include "ui_login.h"
#include <QMessageBox>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    statusBar = new QStatusBar;
    ui->verticalLayoutLogin->addWidget(statusBar);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButtonSignIn_clicked()
{
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();
    /*result = client->login(username, password)
     * if (username dont exist in dataBase)
     * Qmessage:: username invalide please register
     *
    */
    if (username == "test" && password == "test"){

        statusBar->showMessage("Username and password are correct", 5000);
        hide();
        gameWindow = new GameWindow(this);
        gameWindow->show();
    }
    else{
        statusBar->showMessage("Username or password is incorrect", 5000);
    }

}

void Login::on_pushButtonRegister_clicked()
{
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();
    /*result = client->login(username, password)
     * if (username dont exist in dataBase)
     * Qmessage:: username invalide please register
     *
    */
    if (username == "test" && password == "test"){
        statusBar->showMessage("Username and password are correct", 5000);
        hide();
        gameWindow = new GameWindow(this);
        gameWindow->show();
    }
    else{
        statusBar->showMessage("Username or password is incorrect", 5000);
    }

}
