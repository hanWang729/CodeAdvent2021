#include <iostream>
#include <vector>
#include <fstream>

const int vectorSize = 5;

struct InputVector {
    std::vector<std::vector<int>> inputValue;
    std::vector<std::vector<int>> checkVector;
    int steps = 999;
    int finalAnswer = 0;

    InputVector(std::vector<std::vector<int>> const &input){
        inputValue = input;
        std::vector<int> v = {0,0,0,0,0};
        for(int i = 0; i < vectorSize; i++){
            checkVector.push_back(v);
        }
    }

    int findAnswer(std::vector<int> const &puzzleInput) {
        int stat;
        for (int i = 0; i < puzzleInput.size(); i++){
            findANumber(puzzleInput[i]);
            stat = checkFinalStatus();
            if(stat == 1){
                finalAnswer = calculateFinalAnswer(puzzleInput[i]);
                steps = i;
                return finalAnswer;
            }
        }
        return 0;
    }
    
    int calculateFinalAnswer(int finalNum){
        int sumUnmarked = 0;
        for(int i = 0; i < vectorSize; i++){
            for(int j =0; j < vectorSize; j++){
                if(checkVector[i][j] == 0){
                    sumUnmarked += inputValue[i][j];
                }
            }
        }
        return finalNum * sumUnmarked;
    }

    int checkFinalStatus() {
        int row;
        int column;
        for(int i = 0; i < vectorSize; i++){
            row = 0;
            column = 0;
            for(int j = 0; j < vectorSize; j++){
                row += checkVector[i][j];
                column += checkVector[j][i];
            }
            if(row == 5 || column == 5){
                return 1;
            } 
            
        }
        return 0;
    }

    int findANumber(int num){
        for(int i = 0; i < vectorSize; i++){
            for(int j =0; j < vectorSize; j++){
                if(inputValue[i][j] == num){
                    checkVector[i][j] = 1;
                    return 1;
                }
            }
        }
        return 0;
    }

    void printVector(){
        std::cout << "Vector Input" << std::endl;
        for(int i = 0; i < vectorSize; i++){
            for(int j =0; j < vectorSize; j++){
                std::cout << inputValue[i][j] << ", ";
            }
            std::cout << std::endl;
        }
        std::cout << "Vector Status" << std::endl;
        for(int i = 0; i < vectorSize; i++){
            for(int j =0; j < vectorSize; j++){
                std::cout << checkVector[i][j] << ", ";
            }
            std::cout << std::endl;
        }
    }
};

std::vector<InputVector> readInput(){
    std::vector<InputVector> returnValue;
    std::ifstream file("data/day4.txt");
    std::vector<std::vector<int>> templateVector = {{0,0,0,0,0},
                                    {0,0,0,0,0},
                                    {0,0,0,0,0},
                                    {0,0,0,0,0},
                                    {0,0,0,0,0}};
    int i = 0, j = 0;
    while(!file.eof()){
        
        file >> templateVector[i][j++];
        if(j == vectorSize){
            i++;
            if(i == vectorSize){
                i = 0;
                returnValue.push_back(InputVector(templateVector));
                templateVector = {{0,0,0,0,0},
                                    {0,0,0,0,0},
                                    {0,0,0,0,0},
                                    {0,0,0,0,0},
                                    {0,0,0,0,0}};
            }
            j = 0;
        }      
    }
    return returnValue;
}

void part1(std::vector<int> puzzleInput){
    int steps = 99;
    int finalAnswer = 0;
    auto inputVectors = readInput();
    for(auto v : inputVectors){
        v.findAnswer(puzzleInput);
        if(v.steps < steps){
            steps = v.steps;
            finalAnswer = v.finalAnswer;
        }
    }
    std::cout << "Part 1: " << finalAnswer << std::endl;
}

void part2(std::vector<int> puzzleInput){
    int steps = 0;
    int finalAnswer = 0;
    auto inputVectors = readInput();
    for(auto v : inputVectors){
        v.findAnswer(puzzleInput);
        if(v.steps > steps){
            steps = v.steps;
            finalAnswer = v.finalAnswer;
        }
    }
    std::cout << "Part 2: " << finalAnswer << std::endl;
}

int main(int argc, char * argv[]) {
    std::vector<int> puzzleInput = {25,8,32,53,22,94,55,80,33,4,63,14,60,95,31,89,30,5,47,66,
                                    84,70,17,74,99,82,21,35,64,2,76,9,90,56,78,28,51,86,49,98,
                                    29,96,23,58,52,75,41,50,13,72,92,83,62,37,18,11,34,71,91,85,
                                    27,12,24,73,7,77,10,93,15,61,3,46,16,97,1,57,65,40,0,48,69,6,
                                    20,68,19,45,42,79,88,44,26,38,36,54,81,59,43,87,39,67};
    part1(puzzleInput);
    part2(puzzleInput);
    
}