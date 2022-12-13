#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <cstring>
#include <set>

enum ActionType{
    Addx,
    Noop,
};

struct InputAction{
    ActionType action;
    int value;

    InputAction(std::string const &actionType, std::string const &val){
        if(actionType == "noop")
            action = Noop;
        else if(actionType == "addx")
            action = Addx;
        // std::cout << "Distance: " << val << std::endl;
        value = std::stoi(val);
    }
};

struct Signal
{
    std::vector<int> strength;
    int circle;

    Signal(){
        strength.push_back(1);
        circle = 0;
    }

    void noop(){
        circle++;
        strength.push_back(strength.back());
    }

    void addx(int i){
        circle++;
        strength.push_back(strength.back());
        circle++;
        strength.push_back(strength.back()+i);
    }

    void doAction(InputAction a){
        switch (a.action){
            case Noop:
                noop();
                break;
            case Addx:
                addx(a.value);
                break;
        }
    }
};


std::vector<InputAction> readInput()
{
    std::ifstream input("data/day10.txt");
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

int main(int argc, char * argv[]){
    auto input = readInput();
    Signal signal;
    for(auto i : input) {
        signal.doAction(i);
    }
    int sum = 0;
    std::vector<int> v = {20,60,100,140,180,220};
    for(int i : v){
        sum += signal.strength[i-1] * i;
    }
    std::cout << sum << std::endl;
    std::cout << signal.strength.size() << std::endl;
    // part2()
    for(int i = 0; i < 6; i++){
        for (int j = 0; j < 40; j++){
            if(abs(signal.strength[j+i*40] - j) <= 1){
                std::cout << "#";
            }
            else{
                std::cout << ".";
            }
        }
        std::cout << std::endl;
    }
}