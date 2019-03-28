#ifndef Timer_HPP
#define Timer_HPP
#include <QtWidgets>

class Timer : public QWidget {
    Q_OBJECT

    private slots:
    void on_timer_timeout();
    void on_pushButtonSwitch_clicked();

    public:
    Timer(QWidget *parent = nullptr);

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
    QVBoxLayout *_vBoxLayoutTimer;
};
#endif // Timer_HPP