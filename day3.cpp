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

std::set<Pair> findValidPoint(std::vector<std::string> const &inputString){
    std::set<Pair> returnValue;
    for(int i = 0; i < inputString.size();i++){
        for(int j = 0; j < inputString[i].length(); j++){
            if(isdigit(inputString[i][j]) ==0 && inputString[i][j] != '.'){
                returnValue.insert(Pair {i+1,j+1});
                returnValue.insert(Pair {i+1,j});
                returnValue.insert(Pair {i+1,j-1});
                returnValue.insert(Pair {i,j+1});
                returnValue.insert(Pair {i,j-1});
                returnValue.insert(Pair {i-1,j+1});
                returnValue.insert(Pair {i-1,j});
                returnValue.insert(Pair {i-1,j-1});
            }
        }
    }
    return returnValue;
}

void part1(std::vector<std::string> const &inputString){
    int d;
    int sum = 0;
    std::vector<int> nums;
    std::set<Pair> validPoint = findValidPoint(inputString);
    for(int i = 0; i < inputString.size();i++){
        for(int j = 0; j < inputString[i].length(); j++){
            if(isdigit(inputString[i][j])){
                d = 1;
                while(isdigit(inputString[i][j+d])){
                    d++;
                }
                for(int x = 0; x < d; x++){
                    if(validPoint.count(Pair {i, j+x}) > 0){
                        nums.push_back(std::stoi(inputString[i].substr(j,d)));
                        break;
                    }
                }
                j+=d;
            }
        }
    }
    for(auto n : nums){
        sum += n;
    }
    std::cout << "ans1: " << sum << std::endl;
}

int main(int argc, char * argv[]){
    auto input = readInput();
    part1(input);
}
