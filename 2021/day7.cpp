#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <numeric>
#include <algorithm>

std::vector<int> readInput(){
    std::vector<int> inputVector;
    std::ifstream file("data/day7.txt");
    int t;
    while(!file.eof()){
        file >> t;
        inputVector.push_back(t);
    }
    return inputVector;
}

void printVector(std::vector<int> &inputs){
    for(auto i : inputs){
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void part1(){
    auto inputs = readInput();
    std::sort(inputs.begin(),inputs.end());

    int mid = inputs[inputs.size() / 2];
    int ans1 = 0;
    for(auto i : inputs){
        ans1 += std::abs(i - mid);
    }
    std::cout << "Ans1: " << ans1 << std::endl;
}

long long fuelConsume(std::vector<int>& inputs, int a){
    long long returnValue = 0;
    for(auto i : inputs){
        int length = std::abs(a - i);
        returnValue += length * (length + 1) / 2;
    }
    return returnValue;
}

void part2(){
    auto inputs = readInput();
    long long ans2 = fuelConsume(inputs, 0);
    long long anst;
    for(int i = 0; i < 1000; i++){
        anst = fuelConsume(inputs,i);
        // std::cout << i << " " << anst << std::endl;
        ans2 = std::min(ans2,anst);
    }
    
    std::cout << " asw2: " << ans2 << std::endl;

}

int main(int argc, char * argv[]) {
    part1();
    // std::cout << order(5) << std::endl;
    part2();
}