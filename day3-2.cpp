#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <array>
#include <utility>
#include <set>

using Pair = std::pair<int,int>;

bool connected(Pair a, Pair b){
    if(a.first==b.first && a.second == b.second)
        return false;
    if (abs(a.first-b.first) <= 1 && abs(a.second - b.second) <= 1)
        return true;
    else
        return false;
}

struct Num{
    Pair start;
    Pair end;
    int value;

    Num(int const &v, Pair const &s, Pair const &e){
        start = s;
        end = e;
        value = v;
    }
    bool ifNeighbor(Pair star){
        if(connected(start,star) || connected(end,star)){
            return true;
        }
        else{
            return false;
        }
    }


};

std::vector<std::string> readInput()
{
    std::vector<std::string> returnValue;
    std::ifstream file("data/day3.txt");
    auto start = std::istream_iterator<std::string>(file);
    auto end = std::istream_iterator<std::string>();
    std::vector<std::string> tmpValue(start,end);
    std::string tmpVector;
    for(auto i : tmpValue){
        returnValue.push_back(i);
    }
    return returnValue;
}

std::vector<Num> findNum(std::vector<std::string> const &inputString){
    int d;
    std::vector<Num> returnValue;
    for(int i = 0; i < inputString.size();i++){
        for(int j = 0; j < inputString[i].length(); j++){
            if(isdigit(inputString[i][j])){
                d = 1;
                while(isdigit(inputString[i][j+d])){
                    d++;
                }
                Pair start = {i,j};
                Pair end = {i,j+d-1};
                int v = std::stoi(inputString[i].substr(j,d));
                Num n = Num(v,start,end);
                returnValue.push_back(n);
                j+=d;
            }
        }
    }
    return returnValue;
}

void part2(std::vector<std::string> const &inputString){
    int ans = 0;
    auto nums = findNum(inputString);
    // for(auto n: nums){
    //     std::cout << n.value << std::endl;
    // }
    for(int i = 0; i < inputString.size();i++){
        for(int j = 0; j < inputString[i].length(); j++){
            if(inputString[i][j] == '*'){
                Pair star = {i,j};
                int count = 0;
                int multi = 1;
                for(auto n:nums){
                    if(n.ifNeighbor(star)){
                        count++;
                        multi*=n.value;
                    }
                }
                if(count == 2){
                    ans+=multi;
                }
            }
        }
    }
    std::cout << "ans1: " << ans << std::endl;
}

void test(){
    Pair p1 = {1,2};
    Pair p2 = {2,2};
    std::cout << connected(p1,p2) << std::endl;
}

int main(int argc, char * argv[]){
    auto input = readInput();
    part2(input);
    // test();
}
