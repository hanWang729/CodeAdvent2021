#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <cstring>
#include <set>
#include <sstream>
#include <utility>
#include <algorithm>

int cal_distance(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

struct Pair
{
    int sensor_x;
    int sensor_y;
    int beacon_x;
    int beacon_y;

    int distance;

    Pair(int const& sx, int const& sy, int const& bx, int const& by){
        sensor_x = sx;
        sensor_y = sy;
        beacon_x = bx;
        beacon_y = by;

        distance = cal_distance(sensor_x,sensor_y,beacon_x,beacon_y);
    }

    bool present(int x, int y){
        if(cal_distance(sensor_x, sensor_y,x,y) <= distance)
            return false;
        else
            return true;
    }
};


std::vector<Pair> readInput()
{
    std::ifstream input("data/day15.txt");
    auto start = std::istream_iterator<int>(input);
    auto end = std::istream_iterator<int>();
    auto s = start;
    std::vector<Pair> returnValue;
    while(s!=end){
        const int sx = *s;
        s++;
        const int sy = *s;
        s++;
        const int bx = *s;
        s++;
        const int by = *s;
        s++;
        returnValue.push_back(Pair(sx,sy,bx,by));
    }
    return returnValue;
}

void part1(){
    auto pairs = readInput();
    std::set<std::pair<int, int>> occupied;
    int yt = 2000000;
    // int yt = 10;
    for(auto &p : pairs){
        int y = yt;
        int x = p.sensor_x;
        while(true){
            if(!p.present(x,y)){
                occupied.insert(std::make_pair(x,y));
                x++;
            }
            else{
                break;
            }
        }
        x = p.sensor_x - 1;
        while(true){
            if(!p.present(x,y)){
                occupied.insert(std::make_pair(x,y));
                x--;
            }
            else{
                break;
            }
        }
    }
    for(auto &p : pairs){
        if(p.beacon_y == yt)
            occupied.erase(std::make_pair(p.beacon_x,p.beacon_y));
    }
    std::cout << "ans1: " << occupied.size() << std::endl;
}

int main(int argc, char* argv[]){
    part1();
}