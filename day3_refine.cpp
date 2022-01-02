#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <cstring>
#include <numeric>
#include <cmath>


struct BinaryStruct{
    std::vector<int> binaryVector;
    int value;
    int size;
    
    BinaryStruct(std::string const &stringInput){
        value = std::stoi(stringInput,nullptr,2);
        for(int i = 0; i < stringInput.length(); i++){
            int j = std::stoi(stringInput.substr(i,1));
            binaryVector.push_back(j);
        }
        size = binaryVector.size();
    }
};

std::vector<BinaryStruct> readInput()
{
    std::ifstream input("data/day3.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    std::vector<BinaryStruct> returnValue;
    for(auto s = start; s != end; s++){
        returnValue.push_back(BinaryStruct(*s));
    }
    return returnValue;
}

void calOnesZeros(std::vector<BinaryStruct> const &readInput, std::vector<int> &ones, std::vector<int> &zeros) {
    int num0;
    int num1;
    for(int i = 0; i < readInput[0].size; i++){
        num0 = 0;
        num1 = 0;
        for(auto ri : readInput){
            if(ri.binaryVector[i] == 0)
                num0 += 1;
            else
                num1 += 1;
        }
        ones.push_back(num1);
        zeros.push_back(num0);
    }
}

int part1(){
    auto binaryValue = readInput();
    std::string gammaString = "";
    std::string epsilonString = "";
    std::vector<int> ones;
    std::vector<int> zeros;
    calOnesZeros(binaryValue,ones,zeros);
    for(int i = 0; i < ones.size(); i++){
        if(ones[i] > zeros[i]){
            gammaString += "1";
            epsilonString += "0";
        }
        else{
            gammaString += "0";
            epsilonString += "1";
        }
    }
    BinaryStruct gamma = BinaryStruct(gammaString);
    BinaryStruct epsilon = BinaryStruct(epsilonString);
    std::cout << gammaString << " " << epsilonString;
    return gamma.value * epsilon.value;
}

int main(int argc, char * argv[]){

    // std::cout << "Ans of part1: " << part1() << std::endl;
    int ans1 = part1();
    std::cout << "Ans of part2: " << ans1 << std::endl;
    return 0;
}