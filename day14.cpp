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

using Pair = std::pair<int,int>;

class Cave{
public:
std::vector<Pair> rocks;
std::vector<Pair> sands;
std::set<int> occupied;
Pair source;
int bottom;

Cave(){
    source = std::make_pair(500,0);
    bottom = 0;
}

void add_rock(std::string inputString){
    inputString += "-";
    size_t pos = inputString.find("-");
    std::string s;
    std::vector<Pair> ends;
    while(pos != inputString.npos){
        s = inputString.substr(0,pos);
        size_t pos2 = s.find(",");
        int first = std::stoi(s.substr(0,pos2));
        int second = std::stoi(s.substr(pos2+1,s.size()));
        ends.push_back(std::make_pair(first,second));
        inputString = inputString.substr(pos+1,inputString.size());
        pos = inputString.find("-");
    }

    for(int i = 0; i < ends.size() - 1; i++){
        Pair rock1 = ends[i];
        Pair rock2 = ends[i+1];

        if(rock1.first == rock2.first){
            int it = (rock2.second - rock1.second) / abs(rock2.second - rock1.second);
            int y = rock1.second;
            while(y!=rock2.second){
                rocks.push_back(std::make_pair(rock1.first, y));
                y+=it;
            }
        }
        if(rock1.second == rock2.second){
            int it = (rock2.first - rock1.first) / abs(rock2.first - rock1.first);
            int x = rock1.first;
            while(x!=rock2.first){
                rocks.push_back(std::make_pair(x,rock1.second));
                x+=it;
            }
        }
    }
    rocks.push_back(ends[ends.size()-1]);

    for(auto r: rocks){
        occupied.insert(r.first * 1000 + r.second);
    }
    // std::sort(rocks.begin(),rocks.end());
}

void update_bottom(){
    for(auto r : rocks){
        if (r.second > bottom){
            bottom = r.second;
        }
    }
}

// void update_border(){
//     border_left = rocks[0].first;
//     border_right = rocks[0].first;
//     for(auto r : rocks){
//         if (r.first < border_left){
//             border_left= r.first;
//         }
//         if (r.first > border_right){
//             border_right= r.first;
//         }
//     }
//     border_left += ;
//     border_right += 3;
// }

// void add_floor(){
//     update_border();
//     update_bottom();

//     std::cout << "floor: " << bottom+2 << std::endl;
//     std::cout << "border_left : " << border_left << std::endl;
//     std::cout << "border_right: " << border_right << std::endl;

//     for(int i = border_left; i <= border_right; i++){
//         floor.push_back(std::make_pair(i,bottom+2));
//     }
//     for(auto f: floor){
//         occupied.insert(f.first * 1000 + f.second);
//     }

// }

void add_sand_part1(){
    update_bottom();
    Pair start_point = source;
    Pair end_point = start_point;
    int i = 0;
    while(true){
        if(end_point.second > bottom){
            return;
        }
        else if(occupied.count(end_point.first * 1000 + end_point.second+1) == 0){
            end_point.second+=1;
        }
        else if(occupied.count((end_point.first - 1) * 1000 + end_point.second+1) == 0){
            end_point.second+=1;
            end_point.first-=1;
        }
        else if(occupied.count((end_point.first + 1) * 1000 + end_point.second+1) == 0){
            end_point.second+=1;
            end_point.first+=1;
        }  

        else{
            sands.push_back(end_point);
            occupied.insert(end_point.first * 1000 + end_point.second);
            end_point = start_point;
        }
    }
}


void add_sand_part2(){
    update_bottom();
    std::cout << "bottom: " << bottom << std::endl;
    Pair start_point = source;
    Pair end_point = start_point;
    int i = 0;
    while(true){
        if(occupied.count(start_point.first * 1000 + start_point.second) == 1){
            return;
        }
        else if(end_point.second == bottom + 1){
            sands.push_back(end_point);
            occupied.insert(end_point.first * 1000 + end_point.second);
            end_point = start_point;
        }
        else if(occupied.count(end_point.first * 1000 + end_point.second+1) == 0){
            end_point.second+=1;
        }
        else if(occupied.count((end_point.first - 1) * 1000 + end_point.second+1) == 0){
            end_point.second+=1;
            end_point.first-=1;
        }
        else if(occupied.count((end_point.first + 1) * 1000 + end_point.second+1) == 0){
            end_point.second+=1;
            end_point.first+=1;
        }  

        else{
            sands.push_back(end_point);
            occupied.insert(end_point.first * 1000 + end_point.second);
            end_point = start_point;
        }
    }
}

void print_rocks(){
    std::sort(rocks.begin(),rocks.end());
    for(auto s : rocks){
        std::cout << s.first << "," << s.second << std::endl;
    }
}
void print_sands(){
    std::sort(sands.begin(),sands.end());
    for(auto s : sands){
        std::cout << s.first << "," << s.second << std::endl;
    }
}
};

Cave readInput()
{
    std::ifstream input("data/day14.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    Cave cave;
    while(s!=end){
        const std::string t = *s;
        s++;
        cave.add_rock(t);
    }
    return cave;
}

int main(int argc, char* argv[]){
    Cave cave = readInput();
    // cave.add_sand_part1();
    // std::cout << "ans1: " << cave.sands.size() << std::endl;
    cave.add_sand_part2();
    std::cout << "ans2: " << cave.sands.size() << std::endl;
}