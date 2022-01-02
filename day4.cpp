#include <iostream>
#include <vector>

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

int main(int argc, char * argv[]) {
    std::vector<int> puzzleInput = {7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1};
    std::vector<std::vector<int>> testVector = {{14,21,17,24,4},
                                    {10,16,15,9,19},
                                    {18,8,23,26,20},
                                    {22,11,13,6,5},
                                    {2,0,12,3,7}};
    auto inputVector = InputVector(testVector);
    
    int f = inputVector.findAnswer(puzzleInput);
    inputVector.printVector();
    std::cout << "Final num: " << f << " Steps: " << inputVector.steps << std::endl;
}