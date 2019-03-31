#include "MatchmakingDialog.hpp"


MatchmakingDialog::MatchmakingDialog(QWidget *parent) : QDialog(parent) {
    init_window();
    init_layout();

    show();

}

void MatchmakingDialog::init_window(){
    setWindowTitle("Matchmaking");
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(Qt::Window
    | Qt::WindowCloseButtonHint);

    resize(300,125);

    _label = new QLabel(this);
    _label->setAlignment(Qt::AlignCenter);
    _label->setText("Wating an oppenent");

    _okButton = new QPushButton("Ok", this);
    _okButton->setVisible(false);
    _cancelButton = new QPushButton("Cancel", this);
    _cancelButton->setVisible(false);



}

void MatchmakingDialog::init_layout(){
    _gbox =new QGridLayout;
    _gbox->addWidget(_label,0,1);

    _gbox->addWidget(_okButton,1,1);
    _gbox->addWidget(_cancelButton,1,2);

    this->setLayout(_gbox);
}

void MatchmakingDialog::fondOpponent(std::string opponent){
    std::string str = "Game fond versus : " + opponent;
    _label->setText(QString::fromStdString(str));

    _okButton->setVisible(true);
    _cancelButton->setVisible(true);
}

QPushButton* MatchmakingDialog::getOkButton(){
    return _okButton;
}

QPushButton* MatchmakingDialog::getCancelButton(){
    return _cancelButton;
}
