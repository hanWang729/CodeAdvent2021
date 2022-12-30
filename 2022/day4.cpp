#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#include <algorithm>


struct day4
{
    int a1;
    int a2;
    int b1;
    int b2;

    day4(std::vector<int> v){
        a1 = v[0];
        a2 = v[1];
        b1 = v[2];
        b2 = v[3];
    }

    bool contain(){
        return ((a1 <= b1) && (a2 >= b2)) || ((a1 >= b1) && (a2 <= b2));
    }

    bool notoverlap(){
        return !(a2 < b1 || b2 < a1);
    }

    void print(){
        std::cout << a1 << " " << a2 << " " << b1 << " " << b2 << std::endl;
    }
};


std::vector<day4> readInput(){
    std::vector<day4> returnValue;
    std::ifstream input("data/day4.txt");
    auto start = std::istream_iterator<int>(input);
    auto end = std::istream_iterator<int>();
    auto s = start;
    std::vector<int > v;
    while(s!=end){
        for(int i = 0; i < 4; i++){
            int t = *s;
            v.push_back(t);
            s++;
        }
        returnValue.push_back(day4(v));
        v.clear();
    }
    return returnValue;
}

void part1(){
    auto input = readInput();
    int sum = 0;
    for(auto i : input){
        if(i.contain()){
            sum++;
            i.print();
        }
            
    }
    std::cout << sum << std::endl;
}

void part2(){
    auto input = readInput();
    int sum = 0;
    for(auto i : input){
        if(i.notoverlap()){
            sum++;
            i.print();
        }
            
    }
    std::cout << sum << std::endl;
}

int main(int argc, char* argv[]){
    part2();
}