#ifndef REGISTER_H
#define REGISTER_H

#include <QtWidgets>

class Register : public QWidget {
    Q_OBJECT

    public:
    explicit Register(QWidget *parent = nullptr);
    QPushButton *getOK() const;
    QPushButton *getCancel() const;
    bool isSamePassword() const;
    bool isTextEmpty() const;

    signals:
    void enterPressed();
    void escapePressed();

    private:
    void init_pushButton();
    void init_lineEdit();
    void init_layout();
    
    QFormLayout *_fbox;
    QHBoxLayout *_hbox;
    QVBoxLayout *_vbox;

    QPushButton *_OKButton;
    QPushButton *_CanButton;

    QLineEdit *_nom;
    QLineEdit *_email;
    QLineEdit *_mdp1;
    QLineEdit *_mdp2;

    protected:
    void keyPressEvent(QKeyEvent *);
};

#endif // REGISTER_H
