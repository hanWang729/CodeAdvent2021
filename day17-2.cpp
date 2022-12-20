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
int64_t TARGET = 1000000000000;

enum Step{
    Left,
    Right,
};

int64_t hash(int64_t x, int64_t y){
    return x + y * 10;
}

void dehash(int64_t& x, int64_t& y, int64_t h){
    x = h % MOD;
    y = (h - x) / MOD; 
}

void test_hash(){
    int x = 3;
    int y = 2;
    int h = hash(x,y);
    int64_t xn, yn;
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
    int64_t ground;
    std::set<int64_t> occupied;
    int left_unit;
    int right_unit;
    Action actions;
    std::vector<int64_t> high_point_column;

    Map(Action& a){
        height = 0;
        ground = 1;
        left_unit = 1;
        right_unit = 7;
        occupied.clear();
        actions = a;
        for(int i = left_unit; i <= right_unit; i++){
            high_point_column.push_back(0);
        }
    }

    std::set<int64_t> rocks(int64_t ops){
        std::set<int64_t> rock;
        int64_t y = height+4;
        int64_t op = ops % 5;
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

    void move_horizental(std::set<int64_t>& rock, Step step){
        int i;
        if(step == Left){
            i = -1;
        }
        else if(step == Right){
            i = 1;
        }
        std::set<int64_t> new_rock;
        for(auto r : rock){
            int64_t x,y;
            dehash(x,y,r);
            int64_t xn = x + i;
            int64_t rn = hash(xn,y);
            if(xn < left_unit || xn > right_unit || occupied.count(rn))
                return;
            new_rock.insert(rn);
        }
        rock = new_rock;
    }

    bool move_down(std::set<int64_t>& rock){
        bool stop = false;
        std::set<int64_t> new_rock;
        for(auto r : rock){
            int64_t x,y;
            dehash(x,y,r);
            int64_t yn = y - 1;
            int64_t rn = hash(x,yn);
            if(occupied.count(rn) || yn < ground){
                stop = true;
                return stop;
            }
            new_rock.insert(rn);
        }
        rock = new_rock;
        return stop;
    }

    void print_rock(std::set<int64_t> rock){
        for(auto o:rock){
            int64_t x,y;
            dehash(x,y,o);
            std::cout << "x : " << x << ", y : " << y <<std::endl;
        }
        std::cout << std::endl;
    }

    void insertRock(std::set<int64_t>& rock){
        for(auto ir : rock){
            int64_t x,y;
            dehash(x,y,ir);
            occupied.insert(ir);
            if(y > height){
                height = y;
            }
            if(y > high_point_column[x-1]){
                high_point_column[x-1] = y;
            }
        }
    }

    void updateGround(){
        int min_high = high_point_column[0];
        for(auto h : high_point_column){
            if(h < min_high)
                min_high = h;
        }

        std::set<int64_t> new_occupied;
        for(auto& i : occupied){
            if(i > min_high * MOD){
                new_occupied.insert(i);
            }
        }
        occupied = new_occupied;
        ground = min_high;

    }

    void simulator(){
        std::set<int64_t> rock;
        bool stop = false;
        std::vector<Step>::iterator it;
        it = actions.steps.begin();
        Step s;
        for(int64_t r = 1; r <= TARGET; r++){
            rock = rocks(r);
            while(!stop){
                s = *it;
                it++;
                if(it == actions.steps.end())
                    it = actions.steps.begin();
                move_horizental(rock,s);
                stop = move_down(rock);
            }
            stop = false;
            insertRock(rock);
            if(r % 10000 == 0){
                std::cout << "r: " << r << std::endl;
                updateGround();
            }
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
    int64_t times;
    int64_t reminds;
    
    times = (TARGET - 1730) / 1740;
    reminds = (TARGET - 1730) % 1740;
    std::cout << "times: " << times << std::endl;
    std::cout << "reminds: " << reminds << std::endl;

    int64_t ans2 = 4480 + 2681 * times;
    std::cout << "ans2: " << ans2 << std::endl;
}