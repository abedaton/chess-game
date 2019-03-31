#ifndef MATCHMAKINGDIALOG_HPP
#define MATCHMAKINGDIALOG_HPP

#include <QDialog>
#include <QLabel>
#include <QtWidgets>
#include <iostream>


class MatchmakingDialog : public QDialog {
Q_OBJECT
public:
    MatchmakingDialog(QWidget* parent = nullptr);
    void fondOpponent(std::string opponent);
    QPushButton* getOkButton();
    QPushButton* getCancelButton();
private:
    void init_window();
    void init_layout();

    QGridLayout* _gbox;
    QLabel* _label;
    QPushButton* _okButton;
    QPushButton* _cancelButton;

};

#endif // MATCHMAKINGDIALOG_HPP
