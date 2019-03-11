/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QVBoxLayout *verticalLayoutLogin;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelUsername;
    QLabel *labelPassword;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditUsername;
    QLineEdit *lineEditPassword;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonSignIn;
    QPushButton *pushButtonRegister;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(300, 130);
        Login->setMaximumSize(QSize(600, 200));
        verticalLayoutLogin = new QVBoxLayout(Login);
        verticalLayoutLogin->setObjectName(QStringLiteral("verticalLayoutLogin"));
        verticalLayoutLogin->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        labelUsername = new QLabel(Login);
        labelUsername->setObjectName(QStringLiteral("labelUsername"));

        verticalLayout_2->addWidget(labelUsername);

        labelPassword = new QLabel(Login);
        labelPassword->setObjectName(QStringLiteral("labelPassword"));

        verticalLayout_2->addWidget(labelPassword);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lineEditUsername = new QLineEdit(Login);
        lineEditUsername->setObjectName(QStringLiteral("lineEditUsername"));

        verticalLayout->addWidget(lineEditUsername);

        lineEditPassword = new QLineEdit(Login);
        lineEditPassword->setObjectName(QStringLiteral("lineEditPassword"));

        verticalLayout->addWidget(lineEditPassword);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayoutLogin->addLayout(verticalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButtonSignIn = new QPushButton(Login);
        pushButtonSignIn->setObjectName(QStringLiteral("pushButtonSignIn"));

        horizontalLayout_2->addWidget(pushButtonSignIn);

        pushButtonRegister = new QPushButton(Login);
        pushButtonRegister->setObjectName(QStringLiteral("pushButtonRegister"));

        horizontalLayout_2->addWidget(pushButtonRegister);


        verticalLayoutLogin->addLayout(horizontalLayout_2);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Login", Q_NULLPTR));
        labelUsername->setText(QApplication::translate("Login", "Username", Q_NULLPTR));
        labelPassword->setText(QApplication::translate("Login", "Password", Q_NULLPTR));
        pushButtonSignIn->setText(QApplication::translate("Login", "Sign In", Q_NULLPTR));
        pushButtonRegister->setText(QApplication::translate("Login", "Register", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
