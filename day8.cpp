#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <map>
#include <string>

struct inputDigits{
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;
    std::map<std::string, int> digitsMap;
    int outputValue;

    inputDigits(std::vector<std::string> const &combinedInputs){
        std::string s;
        for (int i = 0; i < 10; i++){
            s = combinedInputs[i];
            sort(s.begin(),s.end());
            inputs.push_back(s);
        }
        for (int i = 11; i < 15; i++){
            s = combinedInputs[i];
            sort(s.begin(),s.end());
            outputs.push_back(s);
        }
        decoder();
        calOutput();
    }

    int countOutput1478(){
        int count = 0;
        for(auto o : outputs){
            int l = o.length();
            if(l == 2 || l == 3 || l == 4 || l == 7){
                count++;
            }
        }
        return count;
    }

    std::vector<std::string> findByDigit(int d){
        std::vector<std::string> returnValue;
        for(auto i : inputs){
            if(i.length() == d){
                returnValue.push_back(i);
            }
        }
        return returnValue;
    }

    bool containOrNot(std::string inputString, std::string targetString){
        for(int i = 0; i < targetString.length(); i++){
            std::string::size_type idx;
            idx = inputString.find(targetString[i]);
            if(idx == std::string::npos){
                return false;
            }
        }
        return true;
    }

    void decoder(){
        std::vector<std::string> digit2 = findByDigit(2);
        digitsMap[digit2[0]] = 1;
        std::vector<std::string> digit3 = findByDigit(3);
        digitsMap[digit3[0]] = 7;
        std::vector<std::string> digit4 = findByDigit(4);
        digitsMap[digit4[0]] = 4;
        std::vector<std::string> digit7 = findByDigit(7);
        digitsMap[digit7[0]] = 8;

        std::vector<std::string> digit6 = findByDigit(6);
        std::string string9;
        for(auto d6:digit6){
            if(containOrNot(d6,digit4[0])){ // include 4
                digitsMap[d6] = 9;
                string9 = d6;
            }
            else if (!containOrNot(d6,digit2[0])) // not include 1
            {
                digitsMap[d6] = 6;
            }
            else
            {
                digitsMap[d6] = 0;
            }    
        }

        std::vector<std::string> digit5 = findByDigit(5);
        for(auto d5:digit5){
            if(containOrNot(d5,digit3[0])){ // include 7
                digitsMap[d5] = 3;
            }
            else if (containOrNot(string9,d5)) // included in 9
            {
                digitsMap[d5] = 5;
            }
            else
            {
                digitsMap[d5] = 2;
            }    
        }
    }

    void calOutput(){
        outputValue = digitsMap[outputs[0]] * 1000 +
                        digitsMap[outputs[1]] * 100 +
                        digitsMap[outputs[2]] * 10 +
                        digitsMap[outputs[3]] * 1;
    }

    void print(){
        for(auto i : inputs){
            std::cout << i << " ";
        }
        std::cout << "| ";
        for(auto o : outputs){
            std::cout << o << " ";
        }
        std::cout << std::endl;
    }

    void printMap(){
        for(std::map<std::string, int>::iterator it = digitsMap.begin(); it != digitsMap.end(); ++it) {
            std::cout<<it->first<<":"<<it->second<<std::endl;
        }
    }
};


// std::vector<std::string> readInput(){
//     std::vector<std::string> inputVector;
//     std::ifstream file("data/day8.txt");
//     std::string t;
//     while(!file.eof()){
//         file >> t;
//         inputVector.push_back(t);
//     }
//     return inputVector;
// }

std::vector<inputDigits> readInput(){
    std::vector<inputDigits> inputVector;
    std::vector<std::string> templateVector;
    std::ifstream input("data/day8.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    while(s!=end){
        const std::string t = *s;
        s++;
        templateVector.push_back(t);
        if(templateVector.size() == 15){
            inputVector.push_back(inputDigits(templateVector));
            templateVector.clear();
        }
    }
    return inputVector;
}

void part1(){
    auto inputs = readInput();
    int ans = 0;
    for(auto i : inputs){
        ans += i.countOutput1478();
    }
    std::cout << "Ans1:" << ans <<std::endl;
}

void part2(){
    auto inputs = readInput();
    int ans = 0;
    for(auto i : inputs){
        ans += i.outputValue;
    }
    std::cout << "Ans1:" << ans <<std::endl;
}

int main(int argc, char * argv[]) {
    part1();
    part2();    
}