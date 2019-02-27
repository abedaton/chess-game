#pragma once
#include <string>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

class FriendList{
    public:
        std::string getString();
        void setString(std::string string);
    private:
        int _a;
        int _b;
        std::string _john;
};