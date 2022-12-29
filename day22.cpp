#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <cstring>
#include <sstream>
#include <set>
#include <map>
#include <algorithm>
#include <iomanip>

int EXAMPLE = 0;

int MOD = 1000;

int hash(int x, int y){
    return x * MOD + y;
}

void dehash(int h, int &x, int &y){
    x = h / MOD;
    y = h % MOD;
}

void test_hash(){
    int x = 0;
    int y = 8;
    int h = hash(x,y);
    dehash(h,x,y);
    std::cout << "h: " << h << ", x: " << x << ", y: " << y << std::endl;
}

enum Direction{
    Right,
    Down,
    Left,
    Up,
};

struct Map22{
    std::set<int> walls;
    std::set<int> tiles;
    int row;
    int column;

    std::map<int, int> border_horizontal;
    std::map<int, int> border_vertical;

    int start;
    Map22(){};
    Map22(std::vector<std::string> const & inputVector){
        row = inputVector.size();
        column = inputVector[0].size();
        for(int i = 0; i < inputVector.size(); i++){
            for(int j=0; j<inputVector[i].size(); j++){
                auto s = inputVector[i][j];
                if(s == '.'){
                    tiles.insert(hash(i,j));
                }
                else if(s == '#'){
                    walls.insert(hash(i,j));
                }
            }
            if(column < inputVector[i].size())
                column = inputVector[i].size();
        }
        start = *tiles.begin();
        for(int i = 0; i < row; i++){
            int left_border, right_border;
            int j=0;
            while(true){
                if(walls.count(hash(i,j)) == 1 || tiles.count(hash(i,j)) == 1){
                    left_border = j;
                    break;
                }
                else{
                    j++;
                }
            }
            j = 200;
            while(true){
                if(walls.count(hash(i,j)) == 1 || tiles.count(hash(i,j)) == 1){
                    right_border = j;
                    break;
                }
                else{
                    j--;
                }
            }
            border_horizontal.insert(std::make_pair(hash(i,left_border), hash(i,right_border)));
            border_horizontal.insert(std::make_pair(hash(i,right_border), hash(i,left_border)));
        }
        for(int j = 0; j < column; j++){
            int up_border, down_border;
            int i = 0;
            while(true){
                if(walls.count(hash(i,j)) == 1 || tiles.count(hash(i,j)) == 1){
                    up_border = i;
                    break;
                }
                else{
                    i++;
                }
            }
            i = 200;
            while(true){
                if(walls.count(hash(i,j)) == 1 || tiles.count(hash(i,j)) == 1){
                    down_border = i;
                    break;
                }
                else{
                    i--;
                }
            }
            border_vertical.insert(std::make_pair(hash(up_border,j), hash(down_border,j)));
            border_vertical.insert(std::make_pair(hash(down_border,j), hash(up_border,j)));
        }
    }

    void print_border(){
        std::cout << "---------- horizontal -------------" << std::endl;
        for(auto b : border_horizontal){
            int x1,y1,x2,y2;
            dehash(b.first,x1,y1);
            dehash(b.second,x2,y2);
            std::cout << x1 << ", " << y1 << " : " << x2 << ", " << y2 << std::endl;
        }
        std::cout << "---------- vertical   -------------" << std::endl;
        for(auto b : border_vertical){
            int x1,y1,x2,y2;
            dehash(b.first,x1,y1);
            dehash(b.second,x2,y2);
            std::cout << x1 << ", " << y1 << " : " << x2 << ", " << y2 << std::endl;
        }
    }

    void print_start(){
        std::cout << "start: " << start << std::endl;
    }

};

struct NPC{
    int row;
    int column;
    Direction d;
    Map22 myMap;
    std::vector<int> step;
    NPC(Direction di, Map22 const & m, std::vector<int> const& s){
        dehash(m.start,row,column);
        d = di;
        myMap = m;
        step = s;
    }

    void changeDirection(int diff){
        if(diff == -1){
            if(d == Right)
                d = Up;
            else if(d == Up)
                d = Left;
            else if(d == Left)
                d = Down;
            else if(d == Down)
                d = Right;
        }
        if(diff == -2){
            if(d == Right)
                d = Down;
            else if(d == Up)
                d = Right;
            else if(d == Left)
                d = Up;
            else if(d == Down)
                d = Left;
        }
    }

    bool move(){
        int nrow,ncol;
        bool stop = false;
        if(d == Right){
            nrow = row;
            ncol = column+1;
        }
        else if(d == Up){
            nrow = row-1;
            ncol = column;
        }
        else if(d == Left){
            nrow = row;
            ncol = column-1;
        }
        else if(d == Down){
            nrow = row+1;
            ncol = column;
        }
        if(myMap.tiles.count(hash(nrow,ncol)) == 1){
            row = nrow;
            column = ncol;
        }
        else if(myMap.walls.count(hash(nrow,ncol)) == 1){
            stop = true;
            return stop;
        }
        else{
            if(d == Left || d == Right){
                dehash(myMap.border_horizontal[hash(row,column)],nrow,ncol);
                // std::cout << "h: " << row << ", " << column << " : " << nrow << ", " << ncol << std::endl;
            }
            else{
                dehash(myMap.border_vertical[hash(row,column)],nrow,ncol);
                // std::cout << "v: " << row << ", " << column << " : " << nrow << ", " << ncol << std::endl;
            }
            if(myMap.tiles.count(hash(nrow,ncol)) == 1){
            row = nrow;
            column = ncol;
            }
            else if(myMap.walls.count(hash(nrow,ncol)) == 1){
                stop = true;
            }
        }
        return stop;
    }

    void start(){
        int i = 0;
        for(int s : step){
            if(s < 0){
                changeDirection(s);
            }
            else{
                int num = s;
                bool stop = false;
                for(int i = 0; i < num; i++){
                    stop = move();
                    if(stop)
                        break;
                }
            }            
        } 
    }

    void print_ans(){
        int ans;
        int dir;
        if(d == Right)
            dir = 0;
        else if(d == Up)
            dir = 3;
        else if(d == Left)
            dir = 2;
        else if(d == Down)
            dir = 1;
        ans = (row+1) * 1000 + (column+1) * 4 + dir;
        std::cout << "row: " << row << ", column: " << column << ", dir: " << dir << std::endl; 
        std::cout << "ans: " << ans << std::endl;
    }

    void print(){
        std::cout << "row: " << row << ", column: " << column << ", dir: " << d << std::endl; 
    }

    void print_step(){
        for(auto s : step){
            std::cout << s << " ";
        }
        std::cout << std::endl;;
    }
};


Map22 readInputMap(){
    std::string filename;
    if(EXAMPLE == 1)
        filename = "data/day22emap.txt";
    else
        filename = "data/day22map.txt";
    std::ifstream input(filename);
    std::vector<std::string> inputVector;
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    while(s!=end){
        const std::string t = *s;
        s++;
        inputVector.push_back(t);
    }
    Map22 myMap(inputVector);
    return myMap;
}

std::vector<int> readInputStep(){
    std::string filename;
    if(EXAMPLE == 1)
        filename = "data/day22estep.txt";
    else
        filename = "data/day22step.txt";
    std::ifstream input(filename);    
    std::vector<int> inputStep;
    auto start = std::istream_iterator<int>(input);
    auto end = std::istream_iterator<int>();
    auto s = start;
    while(s!=end){
        const int t = *s;
        s++;
        inputStep.push_back(t);
    }
    return inputStep;
}

void part1(){
    Map22 inputMap = readInputMap();
    std::vector<int> inputStep = readInputStep();
    NPC mynpc = NPC(Right,inputMap,inputStep);
    // inputMap.print_border();
    // mynpc.print();
    // mynpc.print_step();
    mynpc.start();
    mynpc.print_ans();

}

int main(int argc, char* argv[]){
    part1();
}