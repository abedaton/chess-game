#ifndef GAMEWINDOW_HPP
#define GAMEWINDOW_HPP

#include <QtWidgets>

class GameWindow : public QWidget {
    Q_OBJECT
    public:
    explicit GameWindow(QWidget *parent = nullptr);
    QPushButton *getLaunchGame() const;
    QComboBox *getComboBoxMode() const;
    QPushButton *getClassicButton() const;
    QPushButton *getDarkButton() const;
    QPushButton *getTrapistButton() const;
    QPushButton *getAntiButton() const;

    private:
    void init_widget();
    void init_layout();

    QPushButton *_LaunchGame;
    QComboBox *_comboBoxMode;
    QPushButton *_classicButton;
    QPushButton *_darkButton;
    QPushButton *_trapistButton;
    QPushButton *_antiButton;

    QGridLayout *_gbox;
};

#endif // GAMEWINDOW_HPP
