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

int MOD = 10;

enum Step{
    Left,
    Right,
};

int hash(int x, int y){
    return x + y * 10;
}

void dehash(int& x, int& y, int h){
    x = h % MOD;
    y = (h - x) / MOD; 
}

void test_hash(){
    int x = 3;
    int y = 2;
    int h = hash(x,y);
    int xn, yn;
    dehash(xn,yn,h);
    std::cout << "x : " << x << ", y : " << y <<std::endl;
    std::cout << "xn : " << xn << ", yn : " << yn <<std::endl;
}

struct Action{
    std::vector<Step> steps;

    Action(){}

    Action(std::string const& inputString){
        for(auto s : inputString){
            if(s == '<'){
                steps.push_back(Left);
            }
            else if(s== '>'){
                steps.push_back(Right);
            }
        }
    }
};

struct Map
{
    int64_t height;
    std::set<int> occupied;
    int left_unit;
    int right_unit;
    Action actions;

    Map(Action& a){
        height = 0;
        left_unit = 1;
        right_unit = 7;
        occupied.clear();
        actions = a;
    }

    std::set<int> rocks(int ops){
        std::set<int> rock;
        int y = height+4;
        int op = ops % 5;
        switch (op){
            case 1:
                for(int x = 3; x <=6; x++){
                    rock.insert(hash(x,y));
                }
                break;
            case 2:
                rock.insert(hash(4,y));
                rock.insert(hash(3,y+1));
                rock.insert(hash(4,y+1));
                rock.insert(hash(5,y+1));
                rock.insert(hash(4,y+2));
                break;
            case 3:
                rock.insert(hash(3,y));
                rock.insert(hash(4,y));
                rock.insert(hash(5,y));
                rock.insert(hash(5,y+1));
                rock.insert(hash(5,y+2));
                break;
            case 4:
                rock.insert(hash(3,y));
                rock.insert(hash(3,y+1));
                rock.insert(hash(3,y+2));
                rock.insert(hash(3,y+3));
                break;
            case 0:
                rock.insert(hash(3,y));
                rock.insert(hash(4,y));
                rock.insert(hash(3,y+1));
                rock.insert(hash(4,y+1));
                break;
        }
        return rock;
    }

    void move_horizental(std::set<int>& rock, Step step){
        int i;
        if(step == Left){
            i = -1;
        }
        else if(step == Right){
            i = 1;
        }
        std::set<int> new_rock;
        for(auto r : rock){
            int x,y;
            dehash(x,y,r);
            int xn = x + i;
            int rn = hash(xn,y);
            if(xn < left_unit || xn > right_unit || occupied.count(rn))
                return;
            new_rock.insert(rn);
        }
        rock = new_rock;
    }

    bool move_down(std::set<int>& rock){
        bool stop = false;
        std::set<int> new_rock;
        for(auto r : rock){
            int x,y;
            dehash(x,y,r);
            int yn = y - 1;
            int rn = hash(x,yn);
            if(occupied.count(rn) || yn < 1){
                stop = true;
                return stop;
            }
            new_rock.insert(rn);
        }
        rock = new_rock;
        return stop;
    }

    void print_rock(std::set<int> rock){
        for(auto o:rock){
            int x,y;
            dehash(x,y,o);
            std::cout << "x : " << x << ", y : " << y <<std::endl;
        }
        std::cout << std::endl;
    }

    void simulator(){
        std::set<int> rock;
        bool stop = false;
        std::vector<Step>::iterator it;
        it = actions.steps.begin();
        Step s;
        for(int r = 1; r <= 1730+1190; r++){
            rock = rocks(r);
            while(!stop){
                s = *it;
                // std::cout << s << std::endl;
                it++;
                if(it == actions.steps.end())
                    it = actions.steps.begin();
                move_horizental(rock,s);
                stop = move_down(rock);
                // if(r == 9){
                //     std::cout << s << std::endl;
                //     print_rock(rock);
                // }
                    // print_rock(rock);
            }
            stop = false;
            for(auto ir : rock){
                occupied.insert(ir);
                if(ir / MOD > height){
                    height = ir/MOD;
                }
            }
            std::cout << height << std::endl;
            // if(r == 8)
            //     print_rock(occupied);
        }
    }
    


};


Action readInput(){
    std::ifstream input("data/day17.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    const std::string t = *s;
    s++;
    Action myAction(t);
    return myAction;
}

int main(int argc, char* argv[]){
    // test_hash();
    Action inputAction = readInput();
    // for(auto i : inputAction.steps){
    //     std::cout << i << std::endl;
    // }
    Map myMap(inputAction);
    myMap.simulator();
    std::cout << "ans2: " << myMap.height << std::endl;
}