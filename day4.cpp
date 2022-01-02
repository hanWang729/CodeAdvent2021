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
    std::vector<int> puzzleInput = {83,5,71,61,88,55,95,6,0,97,20,16,27,7,79,25,81,29,22,52,43,21,53,59,99,18,35,96,51,93,14,
                                    77,15,3,57,28,58,17,50,32,74,63,76,84,65,9,62,67,48,12,8,68,31,19,36,85,98,30,91,89,66,80,
                                    75,47,4,23,60,70,87,90,13,38,56,34,46,24,41,92,37,49,73,10,94,26,42,40,33,54,86,82,72,39,2,
                                    45,78,11,1,44,69,64};
    part1(puzzleInput);
    part2(puzzleInput);
    
}