#include <iostream>
#include <vector>
#include <istream>
#include <iterator>
#include <stdio.h>
#include <string.h>


int main(){
    std::string text = "A24;C46";
    std::vector<std::pair<int,int> > res;

    int mid = text.find(";");
    std::string coord1 = text.substr(0, mid);
    std::string coord2 = text.substr(mid+1, text.size());
    
    std::string tmp(coord1.begin()+1, coord1.end());
    res.push_back(std::make_pair<int,int>(static_cast<int>(coord1[0])-65, std::stoi(tmp)-1));
    std::string tmp2(coord2.begin()+1, coord2.end());
    res.push_back(std::make_pair<int,int>(static_cast<int>(coord2[0])-65, std::stoi(tmp2)-1));
    
    std::cout << res[0].first << ";" << res[0].second << std::endl;
    std::cout << res[1].first << ";" << res[1].second << std::endl;


    return 0;
}


//char ch = 'A' + p.first;
//std::string res =  ch + std::to_string(p.second+1);