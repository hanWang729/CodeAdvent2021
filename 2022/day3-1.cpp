#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#include <algorithm>

struct day3
{
    std::string half1;
    std::string half2;
    day3(std::string const &s){
        half1 = s.substr(0,s.length()/2);
        half2 = s.substr(s.length()/2,s.length()/2);
    }

    char findSamePart(){
        std::map<char, int> charMap;
        for(auto s : half1){
            if(charMap.count(s) == 0)
                charMap[s] = 1;
            else
                charMap[s]++;
        }
        for(auto s : half2){
            if(charMap.count(s))
                return s;
        }
        return ' ';
    }

    int count(){
        std::map<char, int> scoreTable;
        int j = 1;
        for(char i = 'a'; i <= 'z'; i++){
            scoreTable[i] = j;
            j++;
        }
        for(char i = 'A'; i <= 'Z'; i++){
            scoreTable[i] = j;
            j++;
        }
        char c = findSamePart();
        if(c != ' '){
            return scoreTable[c];
        }
        else{
            std::cout << "Error" << std::endl;
            return 0;
        }
    }
};


std::vector<day3> readInput(){
    std::vector<day3> returnValue;
    std::ifstream input("data/day3.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    while(s!=end){
        const std::string t = *s;
        s++;
        returnValue.push_back(day3(t));
    }
    return returnValue;
}

void part1(){
    auto input = readInput();
    int ans = 0;
    for(auto i : input){
        ans += i.count();
    }
    std::cout<< "Part1: " << ans << std::endl;
}

int main(int argc, char* argv[]){
    part1();
}