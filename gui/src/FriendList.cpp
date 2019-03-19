#include "FriendList.hpp"

FriendList::FriendList(QWidget *parent) : QWidget(parent) {
    init_widget();
    init_layout();
}

void FriendList::init_widget() {
    _listWidgetFriendList = new QListWidget(this);
    _listWidgetFriendList->addItem("achraf");
    _pushButtonAddFriend = new QPushButton("Add friend", this);
    _pushButtonRemoveFriend = new QPushButton("Remove friend", this);
}

void FriendList::init_layout() {
    _hBoxLayoutPushButton = new QHBoxLayout();
    _hBoxLayoutPushButton->addWidget(_pushButtonAddFriend);
    _hBoxLayoutPushButton->addWidget(_pushButtonRemoveFriend);

    _vBoxLayoutFriendList = new QVBoxLayout();
    _vBoxLayoutFriendList->addWidget(_listWidgetFriendList);
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