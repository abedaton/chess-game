#pragma once
#ifndef PUBLICITY_HPP
#define PUBLICITY_HPP
#include <QtWidgets>

class Publicity : public QWidget {
    Q_OBJECT

    private slots:
    void on_timer_timeout();
    
    public:
    Publicity(QWidget *parent = nullptr);

    private:
    void init();
    void setPubToRandomImage();


    QVBoxLayout *_vBoxLayout;
    QLabel* _pub_label;
    QTimer *_timer;
    
};
#endif // PUBLICITY_HPP