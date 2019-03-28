#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int main(){
    std::string plop1 = "bob1";
    std::string plop2 = "bob2";
    std::string plop3 = "bob3";
    std::string plop4 = "bob4";
    std::string plop5 = "bob5";
    std::vector<std::string> vec;
    vec.push_back(plop1);
    vec.push_back(plop2);
    vec.push_back(plop3);
    vec.push_back(plop4);
    vec.push_back(plop5);

    if (std::find(vec.begin(), vec.end(), "bob3") != vec.end()){
        std::cout << "hello" << std::endl;
    }


    return 0;
}