#ifndef PUB_HPP
#define PUB_HPP
#include <QtWidgets>

class Publicite : public QWidget {
    Q_OBJECT

    private slots:
    void on_timer_timeout();
    
    public:
    Publicite(QWidget *parent = nullptr);

    private:
    void init();
    void setPubToRandomImage();


    
    QLabel* _pub_label;
    QTimer *_timer;
    
};
#endif // PUB_HPP