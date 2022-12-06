#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>

struct LanternfishGroup{
    std::map<int,long long> fishGroup;

    LanternfishGroup(std::vector<int> const &inputs){
        for(int i = 0; i < 9; i++){
            fishGroup[i] = std::count(inputs.begin(),inputs.end(),i);
        }
    }

    void printGroupStatus(){
        for(int i = 0; i < 9; i++){
            std::cout << "age: " << i << " count: " << fishGroup[i] << std::endl;
        }
    }

    void growUp(){
        int count = 0;
        std::map<int, long long> newGroup;
        for(int i = 0; i < 6; i++){
            newGroup[i] = fishGroup[i+1];
        }
        newGroup[6] = fishGroup[0] + fishGroup[7];
        newGroup[7] = fishGroup[8];
        newGroup[8] = fishGroup[0];
        fishGroup = newGroup;
    }

    long long groupSize() {
        long long groupSize = 0;
        for (int i = 0; i < 9; i++){
            groupSize += fishGroup[i];
        }
        return groupSize;
    }
};

LanternfishGroup readInput(){
    std::vector<int> inputVector;
    std::ifstream file("data/day6.txt");
    int t;
    while(!file.eof()){
        file >> t;
        inputVector.push_back(t);
    }
    return LanternfishGroup(inputVector);
}

long long groupUpDays(LanternfishGroup &fishGroup, int days){
    while(days != 0){
        fishGroup.growUp();
        days--;
    }
    return fishGroup.groupSize();
}

int main(int argc, char * argv[]) {
    auto inputs = readInput();
    std::cout << "Ans of Part1: " << groupUpDays(inputs, 80) << std::endl;
    std::cout << "Ans of Part2: " << groupUpDays(inputs, 256 - 80) << std::endl;

}