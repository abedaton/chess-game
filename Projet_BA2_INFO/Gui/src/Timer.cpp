#ifndef TIMER_CPP
#define TIMER_CPP

#include "Timer.hpp"

Timer::Timer(QWidget *parent) : QWidget(parent) {
    init_widget();
    init_layout();
    init_connect();
    _timer->start(1000);
}

void Timer::init_widget() {
    _isTimeUp = false;
    _labelTimerDown = new QLabel(this);
    _labelTimerDown->setStyleSheet("font: 75 18pt Noto Sans Mono CJK JP Bold;");
    _labelTimerUp = new QLabel(this);
    _labelTimerUp->setStyleSheet("font: 75 18pt Noto Sans Mono CJK JP Bold;");
    _pushButtonSwitch = new QPushButton("Switch", this);
    _timer = new QTimer(this);
    _timeUp = new QTime(0, 5, 0);
    _timeDown = new QTime(0, 5, 0);
    QString timeText = _timeUp->toString("mm : ss");
    _labelTimerUp->setText(timeText);
    _labelTimerDown->setText(timeText);


}

void Timer::init_layout() {
    _vBoxLayoutTimer = new QVBoxLayout(this);
    _vBoxLayoutTimer->addWidget(_labelTimerUp);
    _vBoxLayoutTimer->addWidget(_labelTimerDown);
    _vBoxLayoutTimer->addWidget(_pushButtonSwitch);
    setLayout(_vBoxLayoutTimer);
}

void Timer::init_connect() {
    connect(_timer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
    connect(_pushButtonSwitch, SIGNAL(clicked()), this, SLOT(on_pushButtonSwitch_clicked()));
}

void Timer::on_timer_timeout() {
    if (_isTimeUp) {
        QString timeText = _timeUp->toString("mm : ss");
        *_timeUp = _timeUp->addSecs(-1);
        _labelTimerUp->setText(timeText);

    } else {
        QString timeText = _timeDown->toString("mm : ss");
        *_timeDown = _timeDown->addSecs(-1);
        _labelTimerDown->setText(timeText);
    }
}

void Timer::on_pushButtonSwitch_clicked() {
    if (_isTimeUp){
        _isTimeUp = false;
    }
    else{
        _isTimeUp = true;
    }
}
#endif
