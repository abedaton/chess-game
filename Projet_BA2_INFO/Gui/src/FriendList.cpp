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
    _pushButtonRemoveFriend = new QPushButton("Remove friend", this);
    _selectFriend;
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
    _hBoxLayoutPushButton->addWidget(_pushButtonRemoveFriend);

    _vBoxLayoutFriendList = new QVBoxLayout();
    _vBoxLayoutFriendList->addWidget(_lineEditFriend);
    _vBoxLayoutFriendList->addWidget(_tabWidget);
    _vBoxLayoutFriendList->addLayout(_hBoxLayoutPushButton);
    setLayout(_vBoxLayoutFriendList);
}

QPushButton *FriendList::getPushButtonAddFriend() const {
    return _pushButtonAddFriend;
}

QPushButton *FriendList::getPushButtonRemoveFriend() const {
    return _pushButtonRemoveFriend;
}

QListWidget *FriendList::getListWidgetFriendList() const {
    return _listWidgetFriendList;
}

QString FriendList::getSelectFriend() const{
    return _selectFriend;
}

QLineEdit *FriendList::getLineEditFriend(){
    return _lineEditFriend;
}

void FriendList::setSelectFriend(QString name){
    _selectFriend = name;
}

void FriendList::setFriendList(std::vector<std::pair<std::string,bool> > friendList){
    _listWidgetFriendList->clear();
    for (int i = 0; i<friendList.size(); i++){
        std::cout<<"friend : "<< friendList[i].first<<std::endl;
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
        std::cout<<"friend request : "<< friendRequestsList[i]<<std::endl;
        _listWidgetFriendRequestList->addItem(QString::fromStdString(friendRequestsList[i]));
        _listWidgetFriendRequestList->item(i)->setBackgroundColor(Qt::gray);
    }
}

QListWidget *FriendList::getListWidgetFriendRequestList() const{
    return _listWidgetFriendRequestList;
}
#endif
