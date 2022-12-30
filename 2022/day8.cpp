#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <cstring>
#include <sstream>
#include <set>
#include <algorithm>

const int vectorSizeRow = 99;
const int VectorSizeColumn = vectorSizeRow;

struct InputVector{
    std::vector<std::vector<int>> inputVector;

    InputVector(){
        inputVector.clear();
    }

    void push_back(std::string const &s){
        std::vector<int> nextLine(VectorSizeColumn,0);
        std::string str;
        for(int i = 0; i < s.length(); i++){
            str = s[i];
            nextLine[i] = std::stoi(str);
        }
        inputVector.push_back(nextLine);
    }

    bool visible(int x, int y){
        if(x == 0 || x == vectorSizeRow -1 || y == 0 || y == VectorSizeColumn -1)
            return true;
        int v_count = 0;
        for(int i = 0; i < x; i++){
            if(inputVector[i][y] >= inputVector[x][y]){
                v_count++;
                break;
            }
        }
        for(int i = x + 1; i < vectorSizeRow; i++){
            if(inputVector[i][y] >= inputVector[x][y]){
                v_count++;
                break;
            }
        }
        for(int i = 0; i < y; i++){
            if(inputVector[x][i] >= inputVector[x][y]){
                v_count++;
                break;
            }
        }
        for(int i = y + 1; i < vectorSizeRow; i++){
            if(inputVector[x][i] >= inputVector[x][y]){
                v_count++;
                break;
            }
        }
        if(v_count == 4)
            return false;
        else
            return true;
    }

    int countVisible(){
        int result = 0;
        for(int x = 0; x < vectorSizeRow; x++){
            for(int y = 0; y < VectorSizeColumn; y++){
                if(visible(x,y)){
                    result++;
                    std::cout << x << "," << y << ":" << inputVector[x][y] << std::endl;
                }
            }
        }
        return result;
    }

    int countTreePart2(int x, int y){
        if(x == 0 || x == vectorSizeRow -1 || y == 0 || y == VectorSizeColumn -1)
            return 0;
        int v_count = 1;
        int tmp = 0;
        for(int i = x - 1; i >= 0; i--){
            if(inputVector[i][y] < inputVector[x][y]){
                tmp++;
                if(i == 0){
                    v_count *= tmp;
                }
            }
            else {
                tmp++;
                v_count *= tmp;
                break;
            }
        }
        // std::cout << "1: " << tmp << "," << v_count << std::endl;
        tmp = 0;
        for(int i = x + 1; i < vectorSizeRow; i++){
            if(inputVector[i][y] < inputVector[x][y]){
                tmp++;
                if(i == vectorSizeRow -1){
                    v_count *= tmp;
                }
            }
            else {
                tmp++;
                v_count *= tmp;
                break;
            }
        }
        // std::cout << "2: " << tmp << "," << v_count << std::endl;
        tmp = 0;
        for(int i = y - 1; i >= 0; i--){
            if(inputVector[x][i] < inputVector[x][y]){
                tmp++;
                if(i == 0){
                    v_count *= tmp;
                }
            }
            else {
                tmp++;
                v_count *= tmp;
                break;
            }
        }
        // std::cout << "3: " << tmp << "," << v_count << std::endl;
        tmp = 0;
        for(int i = y + 1; i < VectorSizeColumn; i++){
            if(inputVector[x][i] < inputVector[x][y]){
                tmp++;
                if(i == VectorSizeColumn -1){
                    v_count *= tmp;
                }
            }
            else {
                tmp++;
                v_count *= tmp;
                break;
            }
        }
        // std::cout << "4: " << tmp << "," << v_count << std::endl;
        return v_count;
    }

    int findMaxVisible(){
        int result = 0;
        for(int x = 0; x < vectorSizeRow; x++){
            for(int y = 0; y < VectorSizeColumn; y++){
                int i = countTreePart2(x,y);
                if(result < i){
                    result = i;
                    std::cout << x << "," << y << ":" << i << std::endl;
                }
            }
        }
        return result;
    }

    void print(){
        for(int x = 0; x < vectorSizeRow; x++){
            for(int y = 0; y < VectorSizeColumn; y++){
                std::cout << inputVector[x][y];
            }
            std::cout << std::endl;
        }
    }
};

InputVector readInput(){
    InputVector inputVector;
    std::ifstream input("data/day8.txt");
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
    // inputVector.print();
    // int ans1 = inputVector.countVisible();
    // std::cout << ans1 << std::endl;
    int ans2 = inputVector.findMaxVisible();
    std::cout << ans2 << std::endl;
    // std::cout << inputVector.countTreePart2(3,2) << std::endl;
}