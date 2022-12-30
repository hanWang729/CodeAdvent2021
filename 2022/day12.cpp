#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <cstring>
#include <sstream>
#include <set>
#include <map>
#include <algorithm>
#include <iomanip>

const int vectorSizeRow = 41;
const int VectorSizeColumn = 136;

struct Maze
{
    std::map<int, int> lowestStep;
    std::map<int, int> height;
    std::map<int, std::vector<int>> neighbors;
    int start;
    int end;
    Maze(std::vector<std::string> inputVector){
        std::map<char, int> scoreTable;
        int j = 1;
        for(char i = 'a'; i <= 'z'; i++){
            scoreTable[i] = j;
            j++;
        }
        scoreTable['S'] = 1;
        scoreTable['E'] = 26;
        std::string tmpstring;
        for(int i = 0; i < vectorSizeRow; i++){
            tmpstring = inputVector[i];
            for(int j = 0; j < VectorSizeColumn; j++){
                lowestStep[i * 1000 + j] = vectorSizeRow * VectorSizeColumn;
                height[i * 1000 + j] = scoreTable[tmpstring[j]];
                if (tmpstring[j] == 'S'){
                    start = i * 1000 + j;
                    lowestStep[start] = 0;
                }
                else if(tmpstring[j] == 'E'){
                    end = i * 1000 + j;
                }
            }
        }

        createNeighbors();

    }

    void createNeighbors(){
        std::vector<int> neighborT;
        for(int i = 0; i < vectorSizeRow; i++){
            for(int j = 0; j < VectorSizeColumn; j++){
                neighborT.push_back((i+1) * 1000 + j);
                neighborT.push_back((i-1) * 1000 + j);
                neighborT.push_back(i * 1000 + j + 1);
                neighborT.push_back(i * 1000 + j - 1);
                for(auto n : neighborT){
                    if(height.count(n) != 0){
                        if(height[i * 1000 + j] - height[n] <= 1){
                            neighbors[i * 1000 + j].push_back(n);
                        }
                    }
                }
                neighborT.clear();
            }
        }
    }

    void printStep(){
        for(int i = 0; i < vectorSizeRow; i++){
            for(int j = 0; j < VectorSizeColumn; j++){
                std::cout << std::fixed << std::setw(5) << lowestStep[i * 1000 + j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void printHeight(){
        for(int i = 0; i < vectorSizeRow; i++){
            for(int j = 0; j < VectorSizeColumn; j++){
                std::cout << std::fixed << std::setw(2) << height[i * 1000 + j] << " ";
            }
            std::cout << std::endl;
        }
    }

    int updateStep(){
        for(int i = 0; i < vectorSizeRow; i++){
            for(int j = 0; j < VectorSizeColumn; j++){
                for(auto n : neighbors[i*1000+j]){
                    if(lowestStep[n] + 1 < lowestStep[i*1000+j]){
                        lowestStep[i*1000+j] = lowestStep[n] + 1;
                    }
                }
            }
        }
        return lowestStep[end];
    }

    void printNeighbors(int i){
        std::cout << "Neighbors of " << i << " : " << std::endl; 
        for(auto n : neighbors[i]){
            std::cout << n << std::endl;
        }
    }
};


std::vector<std::string> readInput(){
    std::vector<std::string> inputVector;
    std::ifstream input("data/day12.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    while(s!=end){
        const std::string t = *s;
        s++;
        inputVector.push_back(t);
    }
    return inputVector;
}

int main(int argc, char * argv[]){
    auto inputVector = readInput();
    Maze maze = Maze(inputVector);
    
    int i = 0;
    maze.printStep();
    while (i < 9999){
        std::cout<< maze.updateStep() << std::endl;
        if(maze.updateStep() == 456){
            std::cout << i << std::endl;
            break;
        }
        i++;
        // maze.printStep();
        // maze.printHeight();
    }
    // maze.printNeighbors(maze.end);
    
}