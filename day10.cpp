#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <array>
#include <utility>
#include <map>

enum PIPE{
    VERTICAL,
    HORIZONTAL,
    NORTHWEST,
    NORTHEAST,
    SOUTHWEST,
    SOUTHEAST,
    GROUND,
    START
};

int loc(int x, int y){
    return x * 1000 + y;
}

void deloc(int loc, int &x, int &y){
    x = loc / 1000;
    y = loc % 1000;
}

void test(){
    int x = 17;
    int y = 161;
    int l = loc(x,y);
    std::cout << "loc: " << l << ", x: " << x << ", y: " << y << std::endl;
    int x1, y1;
    deloc(l,x1,y1);
    std::cout << "loc: " << l << ", x1: " << x1 << ", y1: " << y1 << std::endl;
}

struct node{
    PIPE type;
    int location;
    int n1;
    int n2;
    // bool start;

    node(){}
    node(char c, int x, int y){
        if(c == '|'){
            type = VERTICAL;
            location = loc(x,y);
            n1 = loc(x-1,y);
            n2 = loc(x+1,y);
        }
        else if(c == '-'){
            type = HORIZONTAL;
            location = loc(x,y);
            n1 = loc(x,y-1);
            n2 = loc(x,y+1);
        }
        else if(c == 'L'){
            type = NORTHEAST;
            location = loc(x,y);
            n1 = loc(x-1,y);
            n2 = loc(x,y+1);
        }
        else if(c == 'J'){
            type = NORTHWEST;
            location = loc(x,y);
            n1 = loc(x-1,y);
            n2 = loc(x,y-1);
        }
        else if(c == '7'){
            type = SOUTHWEST;
            location = loc(x,y);
            n1 = loc(x,y-1);
            n2 = loc(x+1,y);
        }
        else if(c == 'F'){
            type = NORTHEAST;
            location = loc(x,y);
            n1 = loc(x+1,y);
            n2 = loc(x,y+1);
        }
        else if(c == '.'){
            type = GROUND;
            location = loc(x,y);
        }
        else if(c == 'S'){
            type = START;
            location = loc(x,y);
        }
    }
    int enter(int x){
        if(x==n1){
            return n2;
        }
        else if(x==n2){
            return n1;
        }
        else{
            std::cout << "ERROR" << std::endl;
            return -1;
        }
    }
};

struct Maze{
    std::map<int,node> mazeMap;
    int start;

    Maze(std::vector<std::string> &inputVector){
        for(int i=0;i<inputVector.size();i++){
            for(int j=0;j<inputVector[i].length();j++){
                mazeMap.insert({loc(i,j),node(inputVector[i][j],i,j)});
            }
        }
        findStartNeigh();
    }

    void findStartNeigh(){
        for(auto m : mazeMap){
            if(m.second.type==START){
                start = m.second.location;
                int loc_start = m.second.location;
                int x_s, y_s;
                deloc(loc_start,x_s,y_s);
                std::vector<int> neigh;
                if(mazeMap[loc(x_s+1,y_s)].n1 == loc_start || mazeMap[loc(x_s+1,y_s)].n2 == loc_start){
                    neigh.push_back(loc(x_s+1,y_s));
                }
                if(mazeMap[loc(x_s-1,y_s)].n1 == loc_start || mazeMap[loc(x_s-1,y_s)].n2 == loc_start){
                    neigh.push_back(loc(x_s-1,y_s));
                }
                if(mazeMap[loc(x_s,y_s+1)].n1 == loc_start || mazeMap[loc(x_s,y_s+1)].n2 == loc_start){
                    neigh.push_back(loc(x_s,y_s+1));
                }
                if(mazeMap[loc(x_s,y_s-1)].n1 == loc_start || mazeMap[loc(x_s,y_s-1)].n2 == loc_start){
                    neigh.push_back(loc(x_s,y_s-1));
                }
                mazeMap[start].n1 = neigh[0];
                mazeMap[start].n2 = neigh[1];
                break;
            }
        }
    }

    void test(){
        std::cout << "Start neighbors: " << mazeMap[start].n1 << ", " << mazeMap[start].n2 << std::endl;
    }
};

std::vector<std::string> readInput()
{
    std::vector<std::string> returnValue;
    std::ifstream file("data/day10.txt");
    auto start = std::istream_iterator<std::string>(file);
    auto end = std::istream_iterator<std::string>();
    std::vector<std::string> tmpValue(start,end);
    std::string tmpVector;
    for(auto i : tmpValue){
        returnValue.push_back(i);
    }
    return returnValue;
}

void part1(std::vector<std::string> input){
    Maze maze = Maze(input);
    // maze.test();
    int count = 1;
    node node_start = maze.mazeMap[maze.start];
    int loc_start = node_start.location;
    int loc_next = node_start.n1;
    int loc_cur = loc_start;
    while(loc_next!=loc_start){
        node node_cur = maze.mazeMap[loc_next];
        int loc_temp = loc_cur;
        loc_cur = loc_next;
        loc_next = node_cur.enter(loc_temp);
        count++;
    }
    std::cout << "ans1: " << count / 2 <<std::endl;
}

int main(int argc, char * argv[]){
    auto input = readInput();
    part1(input);
}
