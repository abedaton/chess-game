#include "friendListTest.hpp"

std::string FriendList::getString(){
    return this->_john;
}

void FriendList::setString(std::string string){
    this->_john = string;
}

FriendList* getFile(){
    int fd2 = open("save.txt", O_RDONLY);
    FriendList *newObj = static_cast<FriendList*>(malloc(sizeof(class FriendList)));
    read(fd2, newObj, sizeof(class FriendList));
    return newObj;
}

void saveFile(FriendList* obj2){
    int fd = open("save.txt", O_CREAT | O_RDWR);
    write(fd, obj2, sizeof(class FriendList));
    close(fd);
}

int main(){
    FriendList* obj = new FriendList();
    obj->setString("hello");
    std::cout << obj->getString() << std::endl;
    saveFile(obj);
    free(obj);
    FriendList* heyyy = getFile();
    std::string john = heyyy->getString();
    std::cout << john << std::endl;
    free(heyyy);
    return 0;
}