#include <iostream>
#include <mutex>


int main(){
    std::mutex mut;
    std::cout << "A\n" ;
    mut.lock();
    std::cout << "b\n" ;
    mut.unlock();
    std::cout << "4" << std::endl;
    mut.unlock();
    std::cout << "5" << std::endl;

    return 0;
}