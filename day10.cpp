#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#include <algorithm>

std::map<int, int> charMapScore = {
    {1, 3}, {2, 57}, {3 ,1197}, {4, 25137},
};

std::map<std::string, int> charMap = {
    {"(", -1}, {")", 1},
    {"[" ,-2}, {"]", 2},
    {"{", -3}, {"}", 3},
    {"<", -4}, {">", 4}
};

struct LineString{
    std::vector<int> stringVector;
    std::vector<int> missingPart;
    long missingScore;
    LineString(std::string const &s){
        std::string str;
        for(int i = 0; i < s.length(); i++){
            str = s[i];
            stringVector.push_back(charMap[str]);
        }
    }

    int findCorruptOrMissing(){
        std::stack<int> myStack;
        for(auto sv: stringVector){
            if(sv < 0){
                myStack.push(sv);
            }
            else{
                if(sv + myStack.top() == 0){
                    myStack.pop();
                }
                else{
                    return sv;
                }
            }
        }
        while(!myStack.empty()){
            missingPart.push_back(myStack.top() * (-1));
            myStack.pop();
        }
        calMissingScore();
        return 0;
    }

    void calMissingScore(){
        missingScore = 0;
        for(auto r : missingPart){
            missingScore *= 5;
            missingScore += r;
        }   
    }

    void print(){
        for(auto i : stringVector){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};

std::vector<LineString> readInput(){
    std::vector<LineString> returnValue;
    std::ifstream input("data/day10.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    while(s!=end){
        const std::string t = *s;
        s++;
        returnValue.push_back(LineString(t));
    }
    return returnValue;
}

void part1(){
    auto inputString = readInput();
    int ans = 0;
    for(auto i : inputString){
        ans += charMapScore[i.findCorruptOrMissing()];
    }
    std::cout << "part1: " << ans << std::endl;
}

void part2(){
    auto inputString = readInput();
    std::vector<long> ansVector;
    for(auto i : inputString){
        if(i.findCorruptOrMissing() == 0){
            ansVector.push_back(i.missingScore);
        }
    }
    std::sort(ansVector.begin(), ansVector.end());
    long ans = ansVector[ansVector.size() / 2];
    std::cout << "part2: " << ans << std::endl;
}

int main(int argc, char* argv[]){
    part1();
    part2();
}