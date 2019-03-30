#pragma once
#ifndef FRIENDLIST_HPP
#define FRIENDLIST_HPP
#include <QtWidgets>

class FriendList : public QWidget {
    Q_OBJECT

    public:
    explicit FriendList(QWidget *parent = nullptr);

    QListWidget *getListWidgetFriendList() const;
    QPushButton *getPushButtonAddFriend() const;
    QPushButton *getPushButtonRemoveFriend() const;
    QString getSelectFriend() const;
    void setSelectFriend(QString name);
    private:
    void init_widget();
    void init_layout();

    QString _selectFriend;
    QVBoxLayout *_vBoxLayoutFriendList;
    QHBoxLayout *_hBoxLayoutPushButton;

    QListWidget *_listWidgetFriendList;
    QPushButton *_pushButtonAddFriend;
    QPushButton *_pushButtonRemoveFriend;
};
#endif