#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <cstring>
#include <numeric>
#include <cmath>


std::vector<std::string> readInput()
{
    std::ifstream input("data/day3.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    std::vector<std::string> returnValue(start,end);
    return returnValue;
    
}

int part1(){
    auto stringValue = readInput();
    std::vector<int> intValue;
    for (auto s : stringValue){
        int i = std::stoi(s,nullptr,2);
        intValue.push_back(i);
        // std::cout << i << std::endl;
    }
    int gamma = 0;
    int epsilon = 0;
    int digits = stringValue[0].length();
    int zeros = 0;
    int ones = 0;
    while(digits > 0){
        for(auto i : intValue){
            i = i >> (digits - 1);
            if (i % 2 == 0)
                zeros += 1;
            else
                ones += 1;
        }
        if (zeros >= ones){
            epsilon += 1;
        }
        else{
            gamma += 1;
        }
        gamma = gamma << 1;
        epsilon = epsilon << 1;
        digits -= 1;
        ones = 0;
        zeros = 0;  
    }
    gamma = gamma >> 1;
    epsilon = epsilon >> 1;
    std::cout << "gamma: " << gamma << ", epsilon: " << epsilon << std::endl;
    return gamma * epsilon;
}

int part2(){
    auto stringValue = readInput();
    std::vector<int> intValue;
    for (auto s : stringValue){
        int i = std::stoi(s,nullptr,2);
        intValue.push_back(i);
        // std::cout << i << std::endl;
    }
    int oxygen = 0;
    int CO2 = 0;
    int digits = stringValue[0].length();
    int zeros = 0;
    int ones = 0;
    std::vector<int> startValue = intValue;
    while(digits > 0 && startValue.size() > 1){
        std::vector<int> oneSet;
        std::vector<int> zeroSet;
        for(auto val : startValue){
            int i = val >> (digits - 1);
            if (i % 2 == 0){
                zeros += 1;
                zeroSet.push_back(val);
            }                
            else {
                oneSet.push_back(val);
                ones += 1;
            }
        }
        if (zeros <= ones){
            oxygen += 1;
            startValue = zeroSet;
        }
        else{
            startValue = oneSet;
        }
        if (startValue.size() == 1){
            oxygen = startValue[0];
        }

        oxygen = oxygen << 1;
        digits -= 1;
        ones = 0;
        zeros = 0;
        zeroSet.clear();
        oneSet.clear(); 
        
        std::cout << "oxygen: " << oxygen << ", CO2: " << CO2 << std::endl;
    }
    oxygen = oxygen >> 1;

    digits = stringValue[0].length();
    startValue = intValue;
    while(digits > 0 && startValue.size() > 1){
        std::vector<int> oneSet;
        std::vector<int> zeroSet;
        for(auto val : startValue){
            int i = val >> (digits - 1);
            if (i % 2 == 0){
                zeros += 1;
                zeroSet.push_back(val);
            }               
            else {
                oneSet.push_back(val);
                ones += 1;
            }
                
        }
        if (zeros > ones){
            CO2 += 1;
            startValue = zeroSet;
        }
        else{
            startValue = oneSet;
        }
        if (startValue.size() == 1){
            CO2 = startValue[0];
        }
        CO2 = CO2 << 1;
        digits -= 1;
        ones = 0;
        zeros = 0;  
        zeroSet.clear();
        oneSet.clear(); 
        std::cout << "oxygen: " << oxygen << ", CO2: " << CO2 << std::endl;
    }
    CO2 = CO2 >> 1;

    std::cout << "oxygen: " << oxygen << ", CO2: " << CO2 << std::endl;
    return oxygen * CO2;
}

int main(int argc, char * argv[]){

    std::cout << "Ans of part1: " << part1() << std::endl;
    int ans2 = part2();
    std::cout << "Ans of part2: " << ans2 << std::endl;
    return 0;
}