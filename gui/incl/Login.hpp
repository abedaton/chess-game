#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <QObject>
#include <QtWidgets>
#include <iostream>

class Login : public QWidget {

    Q_OBJECT

    public:
    explicit Login(QWidget *parent = nullptr);
    QPushButton *getSI() const;
    QPushButton *getRegister() const;
    QString getUsername() const;
    QString getPassword() const;

    public slots:
    void on_signIn();
    void on_register();

    signals:
    void enterPressed();

    private:
    void init_pushButton();
    void init_lineEdit();
    void init_layout();

    QLineEdit *_nom;
    QLineEdit *_mdp;
    QFormLayout *_formLayout;
    QHBoxLayout *_hbox;
    QPushButton *_SIButton;
    QPushButton *_RegiButton;
    QVBoxLayout *_vbox;

    protected:
    void keyPressEvent(QKeyEvent *);
};

#endif // LOGIN_HPP
