#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <stdlib.h>

struct Path {
    int x1;
    int y1;
    int x2;
    int y2;

    int x_direction;
    int y_direction;
    bool vertical;
    bool horizontal;

    Path(std::vector<int> inputs){
        x1 = inputs[0];
        y1 = inputs[1];
        x2 = inputs[2];
        y2 = inputs[3];
        if(x1 == x2){
            x_direction = 0;
            vertical = true;
        }
        else{
            x_direction = (x2 - x1) / std::abs(x2 - x1);
            vertical = false;
        }
        if(y1 == y2){
            y_direction = 0;
            horizontal = true;
        }  
        else{
            y_direction = (y2 - y1) / std::abs(y2 - y1);
            horizontal = false;
        }
    }

    void printPath(){
        std::cout << "x1: " << x1 << " y1: " << y1 << " x2: " << x2 << " y2: " << y2 << std::endl;
        std::cout << "x direction: " << x_direction << " y direction: " << y_direction << std::endl;
    }
};

std::vector<Path> readInput(){
    std::vector<Path> returnValue;
    std::ifstream file("data/day5.txt");
    std::vector<int> templateVector = {0,0,0,0};
    int i = 0;
    while(!file.eof()){
        file >> templateVector[i++];
        if (i == 4){
            returnValue.push_back(Path(templateVector));
            i = 0;
            templateVector = {0,0,0,0};
        }
    }
    return returnValue;
}

int main(int argc, char * argv[]) {
    auto inputPaths = readInput();
    std::map<int, int> answer;
    int key;
    for(auto p : inputPaths){
        int i;
        if(p.vertical){
            i = p.y1;
            while(i != p.y2 + p.y_direction){
                key = p.x1 * 1000 + i;
                if(answer.count(key)){
                    answer[key] += 1;
                }
                else{
                    answer[key] = 1;
                }
                i += p.y_direction;
            }
        }
        else if(p.horizontal){
            i = p.x1;
            while(i!=p.x2 + p.x_direction){
                key = i * 1000 + p.y1;
                if(answer.count(key)){
                    answer[key] += 1;
                }
                else{
                    answer[key] = 1;
                }
                i += p.x_direction;
            }
        }
    }
    std::map<int,int>::iterator iter;
    int answerCount = 0;
    for(iter = answer.begin(); iter != answer.end(); iter++){
        int t = iter -> second;
        int n = iter -> first;
        if(t > 1){
            answerCount++;
            std::cout << n << std::endl;
        }
            
    }
    std::cout << "Part1: " << answerCount << std::endl;
}