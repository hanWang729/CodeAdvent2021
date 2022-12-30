#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <algorithm>

int messageSize = 14;

std::string readInput(){
    std::ifstream input("data/day6.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    const std::string returnValue = *s;
    return returnValue;
}

bool unique(std::string s){
    std::set<char> mySet;
    for(auto i : s){
        mySet.insert(i);
    }
    if(mySet.size()==messageSize)
        return true;
    else
        return false;
}

int main(int argc, char* argv[]) {
    auto input = readInput();
    for(int i = 0; i < input.length() - messageSize; i++){
        if(unique(input.substr(i,messageSize))){
            std::cout << i + messageSize << std::endl;
            return 0;
        }        
    }
}