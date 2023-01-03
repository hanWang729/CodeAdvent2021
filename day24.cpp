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

int EXAMPLE = 1;

int MOD = 1000;

bool part2 = true;

enum Direction{
    Right,
    Up,
    Left,
    Down,
};

enum Action{
    RightAction,
    UpAction,
    LeftAction,
    DownAction,
    Wait,
};

std::map<Direction, std::pair<int,int>> const directionPair{std::make_pair(Up, std::make_pair(-1,0)),
                                                    std::make_pair(Down, std::make_pair(1,0)),
                                                    std::make_pair(Left, std::make_pair(0,-1)),
                                                    std::make_pair(Right, std::make_pair(0,1)),};

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}

int hash(int x, int y){
    return x * MOD + y;
}

void dehash(int h, int &x, int &y){
    x = h / MOD;
    y = h % MOD;
}

struct Wind{
    int x;
    int y;
    Direction d;

    Wind(){};

    Wind(int& xi, int& yi, char& c){
        x = xi;
        y = yi;
        if(c == '>'){
            d = Right;
        }
        else if(c == '<'){
            d = Left;
        }
        else if(c == '^'){
            d = Up;
        }
        else if(c == 'v'){
            d = Down;
        }
    }

    void move_one_step(int up, int down, int left, int right){
        switch (d){
            case Up:
                x--;
                if(x == up){
                    x = down - 1;
                }
                break;
            case Down:
                x++;
                if(x == down){
                    x = up + 1;
                }
                break;
            case Left:
                y--;
                if(y == Left){
                    y = down -1;
                }
                break;
            case Right:
                y++;
                if(y == Right){
                    y = left + 1;
                }
                break;
        }
    }
};

bool operator<(Wind const & lw, Wind const & rw){
        if(lw.x < rw.x)
            return true;
        else if(lw.x == rw.x && lw.y < rw.y)
            return true;
        return false;
    }

struct Valley{
    std::set<Wind> windSetInital;
    int upborder;
    int downborder;
    int leftborder;
    int rightborder;
    std::pair<int,int> start;
    std::pair<int,int> end;

    Valley(std::set<Wind>  ws, int db, int rb){
        windSetInital = ws;
        upborder = 0;
        downborder = db;
        leftborder = 0;
        rightborder = rb;
        start = std::make_pair(upborder,leftborder+1);
        end = std::make_pair(downborder,rightborder-1);    
    }

    void wind_move(std::set<Wind>& windSet){
        for(auto w : windSet){
            w.move_one_step(upborder,downborder,leftborder,rightborder);
        }
    }

    bool existWind(std::pair<int,int> p, std::set<Wind>& windSet){
        for(auto w : windSet){
            if(w.x == p.first && w.y == p.second){
                return true;
            }
        }
        return false;
    }

    std::vector<Action> find_available_action(std::pair<int,int> humn, std::set<Wind>& windSet){
        std::vector<Action> returnAction;
        if(humn == start){
            if(existWind(start + directionPair.at(Down),windSet)){
                returnAction.push_back(DownAction);
            }
        }
        else{
            if(humn.first - 1 != upborder && !existWind(start + directionPair.at(Up),windSet)){
                returnAction.push_back(UpAction);
            }
            if(humn.first + 1 != downborder && !existWind(start + directionPair.at(Down),windSet)){
                returnAction.push_back(DownAction);
            }
            if(humn.second - 1 != leftborder && !existWind(start + directionPair.at(Left),windSet)){
                returnAction.push_back(LeftAction);
            }
            if(humn.second + 1 != rightborder && !existWind(start + directionPair.at(Right),windSet)){
                returnAction.push_back(RightAction);
            }
        }
        if(returnAction.size()==0){
            returnAction.push_back(Wait);
        }
        return returnAction;
    }

    void find_smallest_step(std::set<Wind> windSet, std::pair<int,int> humn, int step, std::vector<int>& resultVector){
        std::cout << step << ":" << humn.first << "," << humn.second << std::endl;
        if(humn == end){
            resultVector.push_back(step);
            return;
        }
        wind_move(windSet);
        std::vector<Action> actionVector = find_available_action(humn,windSet);
        if(actionVector.size() == 0){
            return;
        }
        for(auto& next_action : actionVector){
            switch(next_action){
                case Wait:
                    find_smallest_step(windSet, humn, step + 1, resultVector);
                    break;
                case LeftAction:
                    find_smallest_step(windSet, humn + directionPair.at(Left), step + 1, resultVector);
                    break;
                case RightAction:
                    find_smallest_step(windSet, humn + directionPair.at(Right), step + 1, resultVector);
                    break;
                case UpAction:
                    find_smallest_step(windSet, humn + directionPair.at(Up), step + 1, resultVector);
                    break;
                case DownAction:
                    find_smallest_step(windSet, humn + directionPair.at(Down), step + 1, resultVector);
                    break;
            }
        }
    }

    void start_helper(){
        std::vector<int> resultVector;
        find_smallest_step(windSetInital, start, 0, resultVector);

        int min = resultVector[0];
        for(auto r : resultVector){
            if (r<min){
                min = r;
            }
        }
        std::cout << "ans1: " << min << std::endl;
    }

    void printMap(){
        std::map<int,Direction> uniMap;
        std::map<int,int> dupMap;
        for(auto ws : windSetInital){
            if(dupMap.count(hash(ws.x,ws.y)) == 1){
                dupMap[hash(ws.x,ws.y)]+=1;
            }
            else if(uniMap.count(hash(ws.x,ws.y)) == 0){
                uniMap[hash(ws.x,ws.y)] = ws.d;
            }
            else{
                uniMap.erase(hash(ws.x,ws.y));
                dupMap[hash(ws.x,ws.y)] = 2;
            }
        }
        for(int i = upborder; i <= downborder; i++){
            for(int j = leftborder; j <= rightborder; j++){
                if(std::make_pair(i,j) == start || std::make_pair(i,j) == end){
                    std::cout << ".";
                }
                else{
                    if(i == upborder || i == downborder || j == leftborder || j == rightborder){
                        std::cout << "#";
                    }
                    else if(uniMap.count(hash(i,j)) == 1){
                        switch (uniMap.at(hash(i,j))){
                            case Right:
                                std::cout << ">";
                                break;
                            case Left:
                                std::cout << "<";
                                break;
                            case Up:
                                std::cout << "^";
                                break;
                            case Down:
                                std::cout << "v";
                                break;
                        }
                    }
                    else if(dupMap.count(hash(i,j)) == 1){
                        std::cout << dupMap.at(hash(i,j));
                    }
                    else{
                        std::cout << ".";
                    }
                }
            }
            std::cout << std::endl;
        }
    }
};

Valley readInput(){
    std::string filename;
    if(EXAMPLE == 1)
        filename = "data/day24e.txt";
    else
        filename = "data/day24.txt";
    std::ifstream input(filename);    
    std::vector<std::string> inputString;
    std::set<Wind> WindSet;
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    while(s!=end){
        const std::string t = *s;
        s++;
        inputString.push_back(t);
    }
    for(int i = 0; i < inputString.size(); i++){
        for(int j =0; j < inputString[i].size(); j++){
            if(inputString[i][j] != '#' && inputString[i][j] != '.'){
                WindSet.insert(Wind(i,j,inputString[i][j]));
            }
        }
    }
    Valley myValley = Valley(WindSet, inputString.size()-1, inputString[0].size()-1);

    return myValley;
}

int main(int argc, char* argv[]){
    auto myValley = readInput();
    myValley.printMap();
    myValley.start_helper();
}