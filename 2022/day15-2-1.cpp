#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <cstring>
#include <cstdint>
#include <set>
#include <sstream>
#include <utility>
#include <algorithm>
#include "time.h"

int COORDINATOR = 4000000;

int cal_distance(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

void add_occupied(std::set<unsigned int64_t>& occupied, int x, int y){
    if(x < 0 || y < 0 || x > COORDINATOR || y > COORDINATOR)
        return;
    occupied.insert(x * COORDINATOR + y);
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



    // void find_occupied(){
    //     for(int y = sensor_y - distance; y <= sensor_y + distance; y++){
    //         int distance_left = abs((distance - abs(distance - y)));
    //         for(int x = sensor_x - distance_left; x <= sensor_x + distance_left; x++){
    //             add_occupied(x,y);
    //         }
    //     }
    // }
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

bool part2(int yt){
    auto pairs = readInput();
    int count;
    for(int i = 0; i <= COORDINATOR; i++){
        count = 0;
        for(auto &p : pairs){
            if(!p.present(i,yt)){
                count = 1;
                break;
            }                               
        }
        if(count == 0){
            std::cout << "ans2: " << i * COORDINATOR + yt << std::endl;
            return true;
        }
    }
    return false;
    
}

int main(int argc, char* argv[]){
    for(int i = COORDINATOR / 2; i <= COORDINATOR; i++){
        clock_t start, finish;
        double duration;
        start = clock();
        bool stop = part2(i);
        if(stop)
            break;
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        std::cout << "i: " << i << " duration: " << duration << std::endl;
    }
}