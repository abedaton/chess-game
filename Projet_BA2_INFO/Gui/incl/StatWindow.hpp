#ifndef STATWINDOW_HPP
#define STATWINDOW_HPP

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QLayout>
#include <QTextEdit>
#include <QKeyEvent>
#include <iostream>
#include <QPushButton>
#include "../../Client/includes/abstractClient.hpp"



class StatWindow : public QWidget
{
    Q_OBJECT
public:
    explicit StatWindow(AbstractClient* client);
    QPushButton* getExitButton();
private:
    void init_window();
    void init_layout();

    QLineEdit *_search;
    QTextEdit *_textEdit;
    QGridLayout* _gbox;
    QPushButton* _exitButton;

signals:
    void enterPressed();

public slots:
    void showPlayerStats();

protected:
    void keyPressEvent(QKeyEvent *event);
private:
    AbstractClient* _client;
};

#endif // STATWINDOW_HPP
