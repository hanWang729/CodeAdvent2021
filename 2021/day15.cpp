#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <cstring>
#include <algorithm>

const int SIZE = 100;

std::vector<std::vector<int>> readInput(){
    std::ifstream input("data/day15.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    std::vector<std::vector<int>> returnValue;
    auto s = start;
    std::vector<int> row;
    while(s!=end){
        const std::string t = *s;
        for(int i = 0; i<t.length();i++){
            int x = std::stoi(t.substr(i,1));
            row.push_back(x);
        }
        returnValue.push_back(row);
        row.clear();
        s++;
    }
    return returnValue;
}

void printInput(std::vector<std::vector<int>> inputMap){
    for(auto i : inputMap){
        for(auto j : i) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> countMap(std::vector<std::vector<int>> inputMap){
    std::vector<std::vector<int>> countMap;
    std::vector<int> zeroRow;
    int size = inputMap.size();
    for(int i = 0;i<size;i++){
        zeroRow.push_back(0);
    }
    for(int i=0;i<size;i++){
        countMap.push_back(zeroRow);
    }
    countMap[0][0] = 0;
    for(int i = 1; i < size; i++){
        countMap[0][i] = countMap[0][i-1] + inputMap[0][i];
        countMap[i][0] = countMap[i-1][0] + inputMap[i][0];
    }
    for(int i = 1; i < size; i++){
        for(int j = 1;j<size;j++){
            countMap[i][j] = std::min(countMap[i-1][j], countMap[i][j-1]) + inputMap[i][j];
        }
    }
    return countMap;
}

std::vector<std::vector<int>> secondMap(std::vector<std::vector<int>> inputMap){
    std::vector<std::vector<int>> secondMap;
    std::vector<int> zeroRow;
    for(int i=0; i<SIZE*5;i++){
        zeroRow.push_back(0);
    }
    for(int i=0; i<SIZE*5;i++){
        secondMap.push_back(zeroRow);
    }
    for(int i=0;i<SIZE*5;i++){
        for(int j=0; j<SIZE*5; j++){
            secondMap[i][j] = inputMap[i%SIZE][j%SIZE] + i/SIZE + j/SIZE;
            if(secondMap[i][j] > 9){
                secondMap[i][j] = (secondMap[i][j] - 1) % 9 + 1;
            }
            if(secondMap[i][j] > 9){
                std::cout<< i << "," << j << ": " << secondMap[i][j] << std::endl;
            }
        }
    }
    return secondMap;
}

int main(int argc, char* argv[]){
    auto inputMap = readInput();
    // printInput(inputMap);
    // Part 1
    std::vector<std::vector<int>> resultMap = countMap(inputMap);
    std::cout << "part 1: " << resultMap[SIZE-1][SIZE-1] << std::endl;
    // Part 2
    auto inputMap2 = secondMap(inputMap);
    // printInput(inputMap2);
    auto result2 = countMap(inputMap2);
    printInput(result2);
    std::cout << "part 2:" << result2[5*SIZE-1][5*SIZE-1] << std::endl;
    std::cout << "part 1: " << result2[SIZE-1][SIZE-1] << std::endl;
    // printInput(secondMap);
}