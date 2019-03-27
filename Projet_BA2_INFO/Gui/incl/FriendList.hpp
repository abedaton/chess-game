#include <QtWidgets>

class FriendList : public QWidget {
    Q_OBJECT

    public:
    explicit FriendList(QWidget *parent = nullptr);

    QListWidget *getListWidgetFriendList() const;
    QPushButton *getPushButtonAddFriend() const;
    QPushButton *getPushButtonRemoveFriend() const;

    private:
    void init_widget();
    void init_layout();

    QVBoxLayout *_vBoxLayoutFriendList;
    QHBoxLayout *_hBoxLayoutPushButton;

    QListWidget *_listWidgetFriendList;
    QPushButton *_pushButtonAddFriend;
    QPushButton *_pushButtonRemoveFriend;
};