#include "friendListTest.hpp"

std::string FriendList::getString(){
    return this->_john;
}

void FriendList::setString(std::string string){
    this->_john = string;
}

void FriendList::addEdge(std::vector<int> adj[], int u, int v){
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void FriendList::printGraph(std::vector<int> adj[], int size){
    for (int v = 0; v < size; v++){
        std::cout << "Vertex " << v << "\n head ";
        for (auto x : adj[v]){
            std::cout << "-> " << x;
        }
        std::cout << std::endl;
    }
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

    ////////////////////////////////////////////////////
    // remplacer vector<int> par vector<Player>
    // u et v sont deux joueurs
    // size est le nombre de joueur total enregistré, a augmenter a chaque register
    // mettre size et la matrice adjacente en attribut

    int size = 5;
    std::vector<int> adj[size];
    heyyy->addEdge(adj, 0, 1);
    heyyy->addEdge(adj, 0, 4); 
    heyyy->addEdge(adj, 1, 2); 
    heyyy->addEdge(adj, 1, 3); 
    heyyy->addEdge(adj, 1, 4); 
    heyyy->addEdge(adj, 2, 3); 
    heyyy->addEdge(adj, 3, 4); 
    heyyy->printGraph(adj, size); 
    return 0;
}