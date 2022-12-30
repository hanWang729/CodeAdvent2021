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

bool part2 = true;

enum Direction{
    Right,
    Up,
    Left,
    Down,
};

int hash(int x, int y){
    return x * MOD + y;
}

void dehash(int h, int &x, int &y){
    x = h / MOD;
    y = h % MOD;
}

int hash1(int x, int y, Direction d){
    int di;
    if(d == Right)
        di = 0;
    else if(d == Up)
        di = 1;
    else if(d == Left)
        di = 2;
    else if(d == Down)
        di = 3;

    return x * MOD + y + di * MOD * MOD;
}

void dehash1(int h, int &x, int &y, Direction & d){
    int di = h / MOD / MOD;
    x = (h - di * MOD * MOD) / MOD;
    y = h % MOD;
    
    if(di == 0)
        d = Right;
    else if(di == 1)
        d = Up;
    else if(di == 2)
        d = Left;
    else if(di == 3)
        d = Down;
    else
        std::cout << "Error" << std::endl;
}

void test_hash(){
    int x = 0;
    int y = 8;
    int h = hash(x,y);
    dehash(h,x,y);
    std::cout << "h: " << h << ", x: " << x << ", y: " << y << std::endl;
}

void test_hash1(){
    int x = 0;
    int y = 5;
    Direction d = Down;
    int h = hash1(x,y,d);
    dehash1(h,x,y,d);
    std::cout << "h: " << h << ", x: " << x << ", y: " << y << ", d: " << d << std::endl;
}



struct Map22{
    std::set<int> walls;
    std::set<int> tiles;
    int row;
    int column;

    std::map<int, int> border_horizontal;
    std::map<int, int> border_vertical;
    std::map<int, int> border_2;

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
        if(part2)
            border2();
        else
            border1();
    }
        
    void border1(){
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

    void border2(){
        for(int i = 100; i < 150; i++){
            border_2.insert(std::make_pair(hash1(49,i,Down),hash1(i-50,99,Left)));
            border_2.insert(std::make_pair(hash1(i-50,99,Right), hash1(49,i,Up)));
        }
        for(int i = 0; i < 50; i++){
            border_2.insert(std::make_pair(hash1(100,i,Up), hash1(i+50,50,Right)));
            border_2.insert(std::make_pair(hash1(i+50,50,Left), hash1(100,i,Down)));
        }
        for(int i = 50; i < 100; i++){
            border_2.insert(std::make_pair(hash1(149,i,Down), hash1(i+100,49,Left)));
            border_2.insert(std::make_pair(hash1(i+100,49,Right), hash1(149,i,Up)));
        }
        for(int i = 50; i < 100; i++){
            border_2.insert(std::make_pair(hash1(0,i,Up), hash1(i+100,0,Right)));
            border_2.insert(std::make_pair(hash1(i+100,0,Left), hash1(0,i,Down)));
        }
        for(int i = 100; i < 150; i++){
            border_2.insert(std::make_pair(hash1(0,i,Up), hash1(199,i-100,Up)));
            border_2.insert(std::make_pair(hash1(199,i-100,Down), hash1(0,i,Down)));
        }
        for(int i = 0; i < 50; i++){
            border_2.insert(std::make_pair(hash1(i,149,Right), hash1(149-i,99,Left)));
            border_2.insert(std::make_pair(hash1(149-i,99,Right), hash1(i,149,Left)));
        }
        for(int i = 0; i < 50; i++){
            border_2.insert(std::make_pair(hash1(i,50,Left), hash1(149-i,0,Right)));
            border_2.insert(std::make_pair(hash1(149-i,0,Left), hash1(i,50,Right)));
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
            Direction nd;
            if(part2){ 
                dehash1(myMap.border_2[hash1(row,column,d)],nrow,ncol,nd);
                std::cout << "v: " << row << ", " << column << ", " << d << " : " << nrow << ", " << ncol  << ", " << nd << std::endl;

            }
            else{
                if(d == Left || d == Right){
                    dehash(myMap.border_horizontal[hash(row,column)],nrow,ncol);
                }
                else{
                    dehash(myMap.border_vertical[hash(row,column)],nrow,ncol);
                }
            }
            if(myMap.tiles.count(hash(nrow,ncol)) == 1){
                row = nrow;
                column = ncol;
                if(part2)
                    d = nd;
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
    // test_hash1();
}