#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <cstring>

enum ActionType{
    Forward,
    Up,
    Down,
};

struct InputAction {
    ActionType action;
    int distance;

    InputAction(std::string const &actionType, std::string const &val){
        if(actionType == "forward")
            action = Forward;
        else if(actionType == "down")
            action = Down;
        else if(actionType == "up")
            action = Up;
        // std::cout << "Distance: " << val << std::endl;
        distance = std::stoi(val);
    }

    void doAction(int &horizontal, int &depth){
        switch (action){
            case Forward:
                horizontal += distance;
                break;
            case Down:
                depth += distance;
                break;
            case Up:
                depth -= distance;
                break;
        }            
    }

    void doAction(int &horizontal, int &depth, int& aim){
        switch (action){
            case Forward:
                horizontal += distance;
                depth += aim * distance;
                break;
            case Down:
                aim += distance;
                break;
            case Up:
                aim -= distance;
                break;
        }          
    }
};


std::vector<InputAction> readInput()
{
    std::ifstream input("data/day2.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    std::vector<InputAction> returnValue;
    auto s = start;
    while(s!=end){
        const std::string actionType = *s;
        s++;
        const std::string distance = *s;
        returnValue.push_back(InputAction(actionType,distance));
        s++;
    }
    return returnValue;
    
}

int part1(){
    auto inputs = readInput();
    int horizontal = 0;
    int depth = 0;
    for (auto s : inputs){
        s.doAction(horizontal,depth);
    }
    std::cout << "Part1: horizontal: " << horizontal << ", depth: " << depth << std::endl;
    return horizontal * depth;
}

int part2(){
    auto inputs = readInput();
    int horizontal = 0;
    int depth = 0;
    int aim = 0;
    for (auto s : inputs){
        s.doAction(horizontal,depth,aim);
    }
    std::cout << "Part2: horizontal: " << horizontal << ", depth: " << depth << std::endl;
    return horizontal * depth;
}

int main(int argc, char * argv[])
{
    int ans1 = part1();
    std::cout << ans1 << std::endl;
    int ans2 = part2();
    std::cout << ans2 << std::endl;
}
