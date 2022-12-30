#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <cstring>
#include <set>

enum ActionType{
    Left,
    Right,
    Up,
    Down,
};

struct InputAction{
    ActionType action;
    int distance;

    InputAction(std::string const &actionType, std::string const &val){
        if(actionType == "U")
            action = Up;
        else if(actionType == "D")
            action = Down;
        else if(actionType == "R")
            action = Right;
        else if(actionType == "L")
            action = Left;
        // std::cout << "Distance: " << val << std::endl;
        distance = std::stoi(val);
    }

    void doAction(int &x, int &y){
        switch (action){
            case Left:
                x -= 1;
                break;
            case Right:
                x += 1;
                break;
            case Down:
                y -= 1;
                break;
            case Up:
                y += 1;
                break;
        }          
    }
};

struct HeadTail{
    int size;
    std::vector<std::vector<int>> knots;
    std::vector<std::set<long>> knotsmap;

    HeadTail(int n){
        std::vector<int> knot = {0,0};
        std::set<long> s;
        size = n;
        for(int i = 0; i < n; i++){
            knots.push_back(knot);
            knotsmap.push_back(s);
        }
        recordKnots();
    }

    void recordKnots(){
        // std::cout << "x: " << knots[tail][0] << ", y: " << knots[tail][1] << std::endl;
        for(int i = 0; i < size; i++){
            knotsmap[i].insert(knots[i][0] * 10000 + knots[i][1]);
        }
    }

    bool checkTail(int head, int tail){
        if(std::abs(knots[head][0] - knots[tail][0]) > 1 || std::abs(knots[head][1] - knots[tail][1]) > 1){
            return true; // need move tail
        }
        else
            return false;
    }

    void moveTail(int head, int tail){
        if(!checkTail(head, tail)){
            return;
        }
        if(knots[head][0] == knots[tail][0]){
            if(knots[head][1] > knots[tail][1]){
                knots[tail][1]++;
            }
            else if(knots[head][1] < knots[tail][1]){
                knots[tail][1]--;
            }
        }
        else if(knots[head][1] == knots[tail][1]){
            if(knots[head][0] > knots[tail][0]){
                knots[tail][0]++;
            }
            else if(knots[head][0] < knots[tail][0]){
                knots[tail][0]--;
            }
        }
        else{
            if(knots[head][0] > knots[tail][0]){
                knots[tail][0]++;
            }
            else if(knots[head][0] < knots[tail][0]){
                knots[tail][0]--;
            }
            if(knots[head][1] > knots[tail][1]){
                knots[tail][1]++;
            }
            else if(knots[head][1] < knots[tail][1]){
                knots[tail][1]--;
            }
        }
        recordKnots();
    }
};

std::vector<InputAction> readInput()
{
    std::ifstream input("data/day9.txt");
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
    HeadTail myHeadTail(10);
    for(auto action:input){
        for(int i = 0; i < action.distance; i++){
            int head = 0;
            action.doAction(myHeadTail.knots[head][0],myHeadTail.knots[head][1]);
            // std::cout << "x: " << myHeadTail.knots[head][0] << ", y: " << myHeadTail.knots[head][1] << std::endl;
            for(head = 0; head < myHeadTail.size - 1; head++)
            myHeadTail.moveTail(head, head+1);
        }
    }
    std::cout << myHeadTail.knotsmap[9].size() << std::endl;
}