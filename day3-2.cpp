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
    std::string line1;
    std::string line2;
    std::string line3;
    day3(std::string const &s1,std::string const &s2,std::string const &s3){
        line1 = s1;
        line2 = s2;
        line3 = s3;
    }

    char findSamePart(){
        std::map<char, int> charMap1;
        for(auto s : line1){
            if(charMap1.count(s) == 0)
                charMap1[s] = 1;
            else
                charMap1[s]++;
        }
        std::map<char, int> charMap2;
        for(auto s : line2){
            if(charMap2.count(s) == 0)
                charMap2[s] = 1;
            else
                charMap2[s]++;
        }
        for(auto s : line3){
            if(charMap1.count(s) && charMap2.count(s))
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
        const std::string t1 = *s;
        s++;
        const std::string t2 = *s;
        s++;
        const std::string t3 = *s;
        s++;
        returnValue.push_back(day3(t1,t2,t3));
    }
    return returnValue;
}

void part1(){
    auto input = readInput();
    int ans = 0;
    for(auto i : input){
        ans += i.count();
    }
    std::cout<< "Part2: " << ans << std::endl;
}

int main(int argc, char* argv[]){
    part1();
}