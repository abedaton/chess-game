#pragma once
#ifndef FRIENDLIST_HPP
#define FRIENDLIST_HPP
#include <QtWidgets>

class FriendList : public QWidget {
    Q_OBJECT

    public:
    explicit FriendList(QWidget *parent = nullptr);


    QListWidget *getListWidgetFriendList() const;
    QListWidget *getListWidgetFriendRequestList() const;
    QPushButton *getPushButtonAddFriend() const;
    QPushButton *getPushButtonRemoveFriend() const;
    QString getSelectFriend() const;
    void setSelectFriend(QString name);
    void setFriendList(std::vector<std::pair<std::string,bool> > friendList);
    void setFriendRequestsList(std::vector<std::string> friendRequestsList);
    QLineEdit *getLineEditFriend();

    private:
    void init_widget();
    void init_layout();
    
    QLineEdit *_lineEditFriend;
    QString _selectFriend;
    QVBoxLayout *_vBoxLayoutFriendList;
    QHBoxLayout *_hBoxLayoutPushButton;

    QTabWidget *_tabWidget;
    QListWidget *_listWidgetFriendList;
    QListWidget *_listWidgetFriendRequestList;
    QPushButton *_pushButtonAddFriend;
    QPushButton *_pushButtonRemoveFriend;
};
#endif