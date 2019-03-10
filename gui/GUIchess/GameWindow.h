#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QtWidgets>

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    QPushButton* getClassicButton() const;

private:
    QPushButton* _classicButton;
    QPushButton* _darkButton;
    QPushButton* _trapistButton;
    QPushButton* _antiButton;

    QGridLayout* _gbox;
};

#endif // GAMEWINDOW_H
