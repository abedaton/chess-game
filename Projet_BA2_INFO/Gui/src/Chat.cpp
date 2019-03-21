#include "Chat.hpp"

Chat::Chat(QWidget *parent) : QWidget(parent) {
    init_widget();
    init_layout();
    connect(_lineEdit, SIGNAL(returnPressed()),this, SLOT(on_lineEdit_returnPressed()));
}

void Chat::init_widget() {
    _textEdit = new QTextEdit(this);
    _textEdit->setReadOnly(true);
    _lineEdit = new QLineEdit(this);
}

void Chat::init_layout() {
    _vBoxLayoutChat = new QVBoxLayout(this);
    _vBoxLayoutChat->addWidget(_textEdit);
    _vBoxLayoutChat->addWidget(_lineEdit);
    setLayout(_vBoxLayoutChat);
}

QLineEdit *Chat::getLineEdit(){
    return _lineEdit;
}

QTextEdit *Chat::getTextEdit(){
    return _textEdit;
}

void Chat::on_lineEdit_returnPressed(){
    if (!_lineEdit->text().isEmpty()){
        _textEdit->insertPlainText(_lineEdit->text()+"\n");
        _lineEdit->clear();
        _lineEdit->setFocus();
        emit signalLineEdit();
    }
}
