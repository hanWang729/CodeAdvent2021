#include <iostream>
#include <vector>
#include <fstream>

struct LanternfishGroup{
    std::vector<int> fishGroup;

    LanternfishGroup(std::vector<int> const &inputs){
        fishGroup = inputs;
    }

    void printGroupStatus(){
        for(auto i : fishGroup){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    void growUp(){
        std::vector<int> babyfish;
        int count = 0;
        for(int i = 0; i < fishGroup.size(); i++){
            fishGroup[i]--;
            if(fishGroup[i] == -1){
                fishGroup[i] = 6;
                count++;
            }
        }
        babyfish.resize(count, 8);
        fishGroup.insert(fishGroup.end(),std::make_move_iterator(babyfish.begin()),std::make_move_iterator(babyfish.end()));
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

int groupUpDays(LanternfishGroup &fishGroup, int days){
    while(days != 0){
        fishGroup.growUp();
        days--;
        std::cout << days << std::endl;
    }
    return fishGroup.fishGroup.size();
}

int main(int argc, char * argv[]) {
    auto inputs = readInput();
    // std::cout << "Ans of Part1: " << groupUpDays(inputs, 80) << std::endl;
    std::cout << "Ans of Part1: " << groupUpDays(inputs, 80) << std::endl;

}