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

int order(int a){
    if (a>0)
        return a + order(a-1);
    else
        return 0;
}

void part2(){
    auto inputs = readInput();
    int sum = std::accumulate(inputs.begin(), inputs.end(),0);
    int ave = sum / inputs.size();
    int ans2_1 = 0;
    for(auto i : inputs){
        ans2_1 += order(std::abs(i - ave));
    }
    std::cout << "ave: " << ave << " asw2: " << ans2_1 << std::endl;

    int ans2_2 = 0;
    for(auto i : inputs){
        ans2_2 += order(std::abs(i - ave - 1));
    }
    std::cout << "ave: " << ave << " asw2: " << ans2_2 << std::endl;
}

int main(int argc, char * argv[]) {
    // part1();
    // std::cout << order(5) << std::endl;
    part2();
}