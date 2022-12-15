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

struct Line
{
    int64_t left;
    int64_t right;

    Line(int64_t mid, int64_t distance){
        left = mid - distance;
        right = mid + distance;
        if(left < 0)
            left = 0;
        if(right > COORDINATOR)
            right = COORDINATOR;
    }

    bool combine(Line const & m){
        if((m.left - right) * (left - m.right) < 0 && !((m.left - right == 1) || (left - m.right == 1))){
            return false;
        }
        else{
            left = std::min(left, m.left);
            right = std::max(right, m.right);
            return true;
        }
    }
};

void test_combine(){
    Line line1 = Line(2936277,1063723);
    Line line2 = Line(1363968,1363968);
    std::cout << "test 0 : " << line1.left << "," << line1.right << std::endl;
    std::cout << "test 0 : " << line2.left << "," << line2.right << std::endl;
    line1.combine(line2);
    std::cout << "test: " << line1.left << "," << line1.right << std::endl;
}

struct Line_Set
{
    std::vector<Line> lines;
    int64_t ans;

    Line_Set(){}

    void add(Line const & new_line){
        if(lines.size() == 0)
            lines.push_back(new_line);
        else{
            int count = 0;
            for(auto& line : lines){
                bool b = line.combine(new_line);
                if(!b)
                    count++;
            }
            if(count == lines.size()){
                lines.push_back(new_line);
            }
        }
    }

    bool combine_lines(){
        // print();
        std::vector<Line> line_left;
        if(lines.size() == 1){
            if(lines[0].left == 0 || lines[0].right == COORDINATOR)
                return true;
            else{
                if(lines[0].left == 0)
                    ans = COORDINATOR;
                else
                    ans = 0;
                return false;
            }
                
        }
        while(true){
            for(int i = 1; i < lines.size(); i++){
                if(!lines[0].combine(lines[i])){
                    line_left.push_back(lines[i]);
                }
            }
            if(line_left.size() == 0){
                line_left.push_back(lines[0]);
                lines = line_left;
                break;
            }
            line_left.push_back(lines[0]);
            lines = line_left;
            line_left.clear();
            if(lines.size() == 2){
                if(!lines[0].combine(lines[1])){
                    print();
                    if(lines[0].left == 0)
                        ans = lines[1].left - 1;
                    else
                        ans = lines[0].left - 1;
                    return false;
                }
            }
        }
        // print();
        return true;
    }

    void print(){
        for(auto line: lines){
            std::cout << line.left << "," << line.right << "; ";
        }
        std::cout << std::endl;
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

bool search_one_line(int y){
    auto pairs = readInput();
    Line_Set lines;
    for(auto & p : pairs){
        int mid = p.sensor_x;
        int dis = p.distance - abs(p.sensor_y - y);
        if(dis >= 0){
            lines.add(Line(mid,dis));
        }
    }
    if(lines.combine_lines()){
        return false;
    }
    else{
        std::cout << "part2 ans: " << lines.ans * COORDINATOR + y << std::endl;
        return true;
    }
}

int main(int argc, char* argv[]){
    // test_combine();
    for(int y = 0; y <= COORDINATOR; y++){
        std::cout << "y: " << y << std::endl;
        bool b = search_one_line(y);
        if(b)
            return 0;
    }
}