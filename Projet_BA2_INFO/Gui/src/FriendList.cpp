#ifndef FRIENDLIST_CPP
#define FRIENDLIST_CPP
#include "FriendList.hpp"
#include <iostream>
FriendList::FriendList(QWidget *parent) : QWidget(parent) {
    init_widget();
    init_layout();
}

void FriendList::init_widget() {
    _lineEditFriend = new QLineEdit(this);
    _listWidgetFriendList = new QListWidget(this);
    _listWidgetFriendRequestList = new QListWidget(this);
    _pushButtonAddFriend = new QPushButton("Add friend", this);
    _selectFriend = "init";
    _tabWidget = new QTabWidget(this);
    QWidget *tFriendList = new QWidget(this);
    QVBoxLayout *layoutTabFriendList = new QVBoxLayout(tFriendList);
    layoutTabFriendList->addWidget(_listWidgetFriendList);
    _tabWidget->addTab(tFriendList, "Friend");
    QWidget *tFriendRequestList = new QWidget(this);
    QVBoxLayout *layoutTabFriendRequestList = new QVBoxLayout(tFriendRequestList);
    layoutTabFriendRequestList->addWidget(_listWidgetFriendRequestList);
    _tabWidget->addTab(tFriendRequestList, "Friend Request");
}

void FriendList::init_layout() {
    _hBoxLayoutPushButton = new QHBoxLayout();
    _hBoxLayoutPushButton->addWidget(_pushButtonAddFriend);
    _hBoxLayoutPushButton->addWidget(_lineEditFriend);

    _vBoxLayoutFriendList = new QVBoxLayout();
    _vBoxLayoutFriendList->addLayout(_hBoxLayoutPushButton);
    _vBoxLayoutFriendList->addWidget(_tabWidget);
    setLayout(_vBoxLayoutFriendList);
}

QPushButton *FriendList::getPushButtonAddFriend() const {
    return _pushButtonAddFriend;
}

QListWidget *FriendList::getListWidgetFriendList() const {
    return _listWidgetFriendList;
}

QString FriendList::getSelectFriend() const{
    return _selectFriend;
}

QLineEdit *FriendList::getLineEditFriend() const {
    return _lineEditFriend;
}

void FriendList::setSelectFriend(QString name){
    _selectFriend = name;
}

void FriendList::setFriendList(std::vector<std::pair<std::string,bool> > friendList){
    _listWidgetFriendList->clear();
    for (int i = 0; i<friendList.size(); i++){
        _listWidgetFriendList->addItem(QString::fromStdString(friendList[i].first));
        if (friendList[i].second){
            _listWidgetFriendList->item(i)->setBackgroundColor(Qt::green);
        }
        else{
            _listWidgetFriendList->item(i)->setBackgroundColor(Qt::red);
        }
    }
}

void FriendList::setFriendRequestsList(std::vector<std::string> friendRequestsList){
    _listWidgetFriendRequestList->clear();
    for (int i = 0; i<friendRequestsList.size(); i++){
        _listWidgetFriendRequestList->addItem(QString::fromStdString(friendRequestsList[i]));
        _listWidgetFriendRequestList->item(i)->setBackgroundColor(Qt::gray);
    }
}

QListWidget *FriendList::getListWidgetFriendRequestList() const{
    return _listWidgetFriendRequestList;
}

QTabWidget *FriendList::getTabWidget() const{
    return _tabWidget;
}
#endif
