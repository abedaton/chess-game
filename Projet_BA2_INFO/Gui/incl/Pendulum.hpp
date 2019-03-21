#ifndef PENDULUM_HPP
#define PENDULUM_HPP
#include <QtWidgets>

class Pendulum : public QWidget {
    Q_OBJECT

    private slots:
    void on_timer_timeout();
    void on_pushButtonSwitch_clicked();

    public:
    Pendulum(QWidget *parent = nullptr);

    private:
    void init_widget();
    void init_layout();
    void init_connect();
    bool _isTimeUp;
    QLabel *_labelTimerDown;
    QTime *_timeDown;
    QLabel *_labelTimerUp;
    QTime *_timeUp;
    QPushButton *_pushButtonSwitch;
    QTimer *_timer;
    QVBoxLayout *_vBoxLayoutPendulum;
};
#endif // PENDULUM_HPP