#pragma once
#include <string>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>

class FriendList{
    public:
        std::string getString();
        void setString(std::string string);
        int _a;
        int _b;
        void addEdge(std::vector<int> adj[], int u, int v);
        void printGraph(std::vector<int> adj[], int v);
    private:
        std::string _john;
};