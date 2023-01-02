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

std::vector<std::pair<int,int>> const ALLDIRECTION{std::make_pair(1,0),std::make_pair(-1,0),
                                                    std::make_pair(0,1),std::make_pair(0,-1),
                                                    std::make_pair(1,1),std::make_pair(1,-1),
                                                    std::make_pair(-1,1),std::make_pair(-1,-1)};
std::vector<std::pair<int,int>> const North{std::make_pair(-1,0),std::make_pair(-1,1),std::make_pair(-1,-1)};
std::vector<std::pair<int,int>> const South{std::make_pair(1,0),std::make_pair(1,1),std::make_pair(1,-1)};
std::vector<std::pair<int,int>> const West{std::make_pair(0,-1),std::make_pair(1,-1),std::make_pair(-1,-1)};
std::vector<std::pair<int,int>> const East{std::make_pair(0,1),std::make_pair(1,1),std::make_pair(-1,1)};

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}

struct Elf{
    std::pair<int,int> position;

    Elf(int x, int y){
        position = std::make_pair(x,y);
    }

    Elf(std::pair<int,int> p){
        position = p;
    }

    bool operator==(Elf const & e){
        return (e.position.first == position.first && e.position.second == position.second);
    }

    bool need_move(std::set<std::pair<int,int>> const& old_position){
        for(auto d : ALLDIRECTION){
            if(old_position.count(position + d) != 0){
                return true;
            }
        }
        return false;
    }
    
    std::pair<int,int> find_new_postion(std::set<std::pair<int,int>> const& old_position, int const& order){
        if(!need_move(old_position)){
            return position;
        }
        std::vector<std::pair<int,int>> d;
        for(int i = 0; i < 4; i++){
            switch((i + order) % 4){
                case 0:
                    d = North;
                    break;
                case 1:
                    d = South;
                    break;
                case 2:
                    d = West;
                    break;
                case 3:
                    d = East;
            }
            if(old_position.count(position + d[0]) == 0 &&
                    old_position.count(position + d[1]) == 0 &&
                    old_position.count(position + d[2]) == 0){
                return position + d[0];
            }
            d.clear();
        }
        return position;
    }
};

bool operator==(Elf const & le, Elf const & re)
{
    return (le.position.first == re.position.first && le.position.second == re.position.second);
}

struct Map{
    std::vector<Elf> Elves;
    int up;
    int down;
    int left;
    int right;
    int order;

    Map(std::vector<Elf> e){
        Elves = e;
        order = 0;
        find_border();
    }

    void find_border(){
        up = Elves[0].position.first;
        down = Elves[0].position.first;
        left = Elves[0].position.second;
        right = Elves[0].position.second;

        for(auto& e : Elves){
            if(e.position.first < up){
                up = e.position.first;
            }
            if(e.position.first > down){
                down = e.position.first;
            }
            if(e.position.second < left){
                left = e.position.second;
            }
            if(e.position.second > right) {
                right = e.position.second;
            }
        }
    }

    void move_next_postion(std::set<std::pair<int,int>>const & old_position){
        std::map<int, std::pair<int,int>> next_postion;
        std::set<std::pair<int,int>> uniSet;
        std::set<std::pair<int,int>> dupSet;
        for(int i = 0; i < Elves.size(); i++){
            auto e = Elves[i];
            auto np = e.find_new_postion(old_position,order);
            // std::cout << "old: " << e.position.first << "," << e.position.second << ", new: " << np.first << "," << np.second << std::endl;
            if(np != e.position)
                next_postion[i] = np;
            if(uniSet.count(np) == 0){
                uniSet.insert(np);
            }
            else{
                dupSet.insert(np);
            }
        }
        for(auto n : next_postion){
            if(dupSet.count(n.second) == 0){
                Elves[n.first].position = n.second;
            }
        }
    }

    void start_part1(){
        while(order < 10){
            bool stop = true;
            std::set<std::pair<int,int>> old_position;
            for(int i = 0; i < Elves.size(); i++){
                old_position.insert(Elves[i].position);
            }
            for(auto e : Elves){
                if(e.need_move(old_position)){
                    stop = false;
                    break;
                }
            }
            if(stop){
                break;
            }
            move_next_postion(old_position);
            order++;
        }
        std::cout << "ans1: " << count_ans() << std::endl;
    }

    void start_part2(){
        while(true){
            bool stop = true;
            std::set<std::pair<int,int>> old_position;
            for(int i = 0; i < Elves.size(); i++){
                old_position.insert(Elves[i].position);
            }
            for(auto e : Elves){
                if(e.need_move(old_position)){
                    stop = false;
                    break;
                }
            }
            if(stop){
                break;
            }
            move_next_postion(old_position);
            order++;
            std::cout << order << ":" << count_ans() << ", " << up << "," << down << "," << left << "," << right << std::endl;

        }
        std::cout << "ans1: " << order + 1 << std::endl;

    }

    int count_ans(){
        find_border();
        int c = 0;
        for(int i = up; i <= down; i++){
            for(int j = left; j <=right; j++){
                if(std::count(Elves.begin(), Elves.end(), Elf(i,j))==0){
                    c++;
                }
            }
        }
        return c;
    }

    void print(){
        find_border();
        std::cout << "---------------" << order << "---------------" << std::endl;
        for(int i = up; i <= down; i++){
            for(int j = left; j <=right; j++){
                if(std::count(Elves.begin(), Elves.end(), Elf(i,j))!=0){
                    std::cout << "#";
                }
                else{
                    std::cout << ".";
                }
            }
            std::cout << std::endl;
        }
    }
};

std::vector<Elf> readInput(){
    std::string filename;
    if(EXAMPLE == 1)
        filename = "data/day23e.txt";
    else
        filename = "data/day23.txt";
    std::ifstream input(filename);    
    std::vector<std::string> inputString;
    std::vector<Elf> ElfVector;
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
            if(inputString[i][j] == '#'){
                ElfVector.push_back(Elf(i,j));
            }
        }
    }
    return ElfVector;
}

void part1(){
    auto ElfVector = readInput();
    Map myMap = Map(ElfVector);
    myMap.start_part1();
}
void part2(){
    auto ElfVector = readInput();
    Map myMap = Map(ElfVector);
    myMap.start_part2();
}

int main(int argc, char* argv[]){
    part2();
}