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
    std::vector<int> head;
    std::vector<int> tail;
    std::set<long> tailmap;

    HeadTail(){
        head = {0,0};
        tail = {0,0};
        recordTail();
    }

    void recordTail(){
        // std::cout << "x: " << tail[0] << ", y: " << tail[1] << std::endl;
        tailmap.insert(tail[0] * 10000 + tail[1]);
    }

    bool checkTail(){
        if(std::abs(head[0] - tail[0]) > 1 || std::abs(head[1] - tail[1]) > 1){
            return true; // need move tail
        }
        else
            return false;
    }

    void moveTail(){
        if(!checkTail()){
            return;
        }
        if(head[0] == tail[0]){
            if(head[1] > tail[1]){
                tail[1]++;
            }
            else if(head[1] < tail[1]){
                tail[1]--;
            }
        }
        else if(head[1] == tail[1]){
            if(head[0] > tail[0]){
                tail[0]++;
            }
            else if(head[0] < tail[0]){
                tail[0]--;
            }
        }
        else{
            if(head[0] > tail[0]){
                tail[0]++;
            }
            else if(head[0] < tail[0]){
                tail[0]--;
            }
            if(head[1] > tail[1]){
                tail[1]++;
            }
            else if(head[1] < tail[1]){
                tail[1]--;
            }
        }
        recordTail();
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
    HeadTail myHeadTail;
    for(auto action:input){
        for(int i = 0; i < action.distance; i++){
            action.doAction(myHeadTail.head[0],myHeadTail.head[1]);
            // std::cout << "x: " << myHeadTail.head[0] << ", y: " << myHeadTail.head[1] << std::endl;
            myHeadTail.moveTail();
        }
    }
    std::cout << myHeadTail.tailmap.size() << std::endl;
}