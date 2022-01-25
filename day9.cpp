#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <cstring>
#include <sstream>

const int vectorSizeRow = 102;
const int VectorSizeColumn = 102;

struct InputVector{
    std::vector<std::vector<int>> inputVector;
    std::vector<std::vector<int>> lowestPointVector = 
                std::vector<std::vector<int>>(vectorSizeRow, std::vector<int>(VectorSizeColumn,0));

    InputVector(){
        std::vector<int> initialLine(VectorSizeColumn,9);
        inputVector.push_back(initialLine);
    }

    void push_back(std::string const &s){
        std::vector<int> nextLine(VectorSizeColumn,9);
        std::string str;
        for(int i = 0; i < s.length(); i++){
            str = s[i];
            nextLine[i+1] = std::stoi(str);
        }
        inputVector.push_back(nextLine);
    }

    void push_last_line(){
        std::vector<int> lastLine(VectorSizeColumn,9);
        inputVector.push_back(lastLine);
    }

    void find_lowest_point(){
        for(int i=1; i < vectorSizeRow-1; i++){
            for(int j=1; j<VectorSizeColumn-1; j++){
                int val = inputVector[i][j];
                if(val<inputVector[i+1][j] && val<inputVector[i-1][j] && val<inputVector[i][j+1] && val<inputVector[i][j-1]){
                    lowestPointVector[i][j] = 1;
                }
            }
        }
    }

    int calculateRisk(){
        int risk = 0;
        for(int i=1; i < vectorSizeRow-1; i++){
            for(int j=1; j<VectorSizeColumn-1; j++){
                if(lowestPointVector[i][j] == 1){
                    risk += (inputVector[i][j] + 1);
                }
            }
        }
        return risk;
    }

    void printInputVector(){
        for(auto line : inputVector){
            for(auto i : line){
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    }

    void printLowestPointVector(){
        for(auto line : lowestPointVector){
            for(auto i : line){
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    }
};

InputVector readInput(){
    InputVector inputVector;
    std::ifstream input("data/day9.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    while(s!=end){
        const std::string t = *s;
        s++;
        inputVector.push_back(t);
    }
    inputVector.push_last_line();
    return inputVector;
}

void part1(){
    auto inputVector = readInput();
    inputVector.find_lowest_point();
    auto ans = inputVector.calculateRisk(); 
    std::cout << "part1: " << ans << std::endl;
}

int main(int argc, char* argv[]){
    part1();
}