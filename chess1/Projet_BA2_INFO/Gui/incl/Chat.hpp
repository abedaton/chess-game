#pragma once
#ifndef CHAT_HPP
#define CHAT_HPP
#include <QtWidgets>
#include <iostream>

class Chat : public QWidget {
    Q_OBJECT

    signals:
    void signalLineEdit();

    private slots:
    void on_lineEdit_returnPressed();

    public:
    explicit Chat(QWidget *parent = nullptr);
    QLineEdit *getLineEdit();
    QTextEdit *getTextEdit();
    QString getFriendName();
    void setFriendName(QString name);

    private:
    void init_widget();
    void init_layout();

    QString _friendName;
    QPushButton *_pushButtonSend;
    QTextEdit *_textEdit;
    QLineEdit *_lineEdit;
    QVBoxLayout *_vBoxLayoutChat;
};

#endif //CHAT_HPP