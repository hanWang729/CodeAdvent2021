#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#include <algorithm>

struct Action
{
    int move;
    int from;
    int to;

    Action(int m, int f, int t){
        move = m;
        from = f;
        to = t;
    }
};


std::vector<std::stack<std::string>> readInput1(){
    std::vector<std::stack<std::string>> returnValue;
    std::ifstream input("data/day5-1.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    while(s!=end){
        const std::string t = *s;
        std::stack<std::string> myStack;
        s++;
        for(int i = 0; i < t.length(); i++){
            myStack.push(t.substr(i,1));
        }
        returnValue.push_back(myStack);
    }
    return returnValue;
}

std::vector<Action> readInput2(){
    std::vector<Action> returnValue;
    std::ifstream input("data/day5-2.txt");
    auto start = std::istream_iterator<int>(input);
    auto end = std::istream_iterator<int>();
    auto s = start;
    while(s!=end){
        const int move = *s;
        s++;
        const int from = *s;
        s++;
        const int to = *s;
        s++;
        returnValue.push_back(Action(move,from,to));
    }
    return returnValue;
}

void move(std::vector<std::stack<std::string>> & stackVector, Action action){
    for(int i = 0; i < action.move ; i++){
        stackVector[action.to-1].push(stackVector[action.from-1].top());
        stackVector[action.from-1].pop();
    }
}

void move2(std::vector<std::stack<std::string>> & stackVector, Action action){
    std::stack<std::string> t;
    for(int i = 0; i < action.move ; i++){
        t.push(stackVector[action.from-1].top());
        stackVector[action.from-1].pop();
    }
    for(int i = 0; i < action.move ; i++){
        stackVector[action.to-1].push(t.top());
        t.pop();
    }
}

int main(int argc, char* argv[]) {
    auto stackVector = readInput1();
    auto actionVector = readInput2();
    for(auto action : actionVector){
        move2(stackVector,action);
    }
    for(auto s : stackVector){
        std::cout << s.top();
    }
    std::cout << std::endl;
}