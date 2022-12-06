#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <set>
#include <map>
#include <stdlib.h>

struct Dot{
    unsigned int x;
    unsigned int y;
    bool folderLine = false;

    Dot(std::string const & x_, std::string const & y_){
        x = std::stoi(x_);
        y = std::stoi(y_);
    }
};


struct DotVector{
    std::vector<Dot> dotVector;

    DotVector(std::vector<Dot> v){
        dotVector = v;
    }

    int findMaxX(){
        int max = 0;
        for(auto d : dotVector){
            if(d.x > max){
                max = d.x;
            }
        }
        return max;
    }
    
    int findMaxY(){
        int max = 0;
        for(auto d : dotVector){
            if(d.y > max){
                max = d.y;
            }
        }
        return max;
    }

    void print(){
        for(auto d :dotVector){
            std::cout << "x: " << d.x << " y: " << d.y << std::endl;
        }
    }

    void fold(int direction, int position){
        if(direction > 0){
            for(int i = 0; i < dotVector.size(); i++){
                if(dotVector[i].x > position){
                    dotVector[i].x = 2*position - dotVector[i].x;
                }
                else if(dotVector[i].x == position){
                    dotVector[i].folderLine = true;
                }
            }
        }
        else{
            for(int i = 0; i < dotVector.size(); i++){
                if(dotVector[i].y > position){
                    dotVector[i].y = 2*position - dotVector[i].y;
                }
                else if(dotVector[i].y == position){
                    dotVector[i].folderLine = true;
                }
            }
        }
    }

    int countDot(){
        std::set<int> countSet;
        for(auto d : dotVector){
            if(!d.folderLine)
                countSet.insert(d.x * 10000 + d.y);
        }
        return countSet.size();
    }

    void printDot(){
        int maxY = findMaxX() + 1;
        int maxX = findMaxY() + 1;
        std::string str = ".";
        std::string str1 = "#";
        std::vector<std::vector<std::string>> map(maxX, std::vector<std::string>(maxY, str));
        for(auto i : dotVector){
            map[i.y][i.x] = str1;
        }
        for(auto i : map){
            for(auto j : i){
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
    }
};


DotVector readInput(){
    std::vector<Dot> inputVector;
    std::ifstream input("data/day13.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    while(s!=end){
        std::string x = *s;
        s++;
        std::string y = *s;
        s++;
        inputVector.push_back(Dot(x,y));
    }
    return DotVector(inputVector);
}

std::vector<int> readFold(){
    std::vector<int> inputFold;
    std::ifstream input("data/day13_fold.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    while(s!=end){
        std::string d = *s;
        s++;
        std::string v = *s;
        s++;
        if(d == "x"){
            inputFold.push_back(std::stoi(v));
        }
        else{
            inputFold.push_back(-std::stoi(v));
        }
    }
    return inputFold;
}

void part1(){
    auto inputDot = readInput();
    auto inputFold = readFold();
    int i = inputFold[0];
    inputDot.fold(i / std::abs(i), std::abs(i));
    std::cout << "part1: " << inputDot.countDot() << std::endl;
}

void part2(){
    auto inputDot = readInput();
    auto inputFold = readFold();
    for(auto i : inputFold)
        inputDot.fold(i / std::abs(i), std::abs(i));
    // inputDot.print();
    inputDot.printDot();
}

int main(int argc, char* argv[]){
    // part1();
    part2();
}