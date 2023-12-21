#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <map>
#include <sstream>
#include <string>

std::string NAV;

struct Node{
    std::string name;
    std::string left;
    std::string right;

    Node(){}

    Node(std::string n, std::string l, std::string r){
        name = n;
        left = l;
        right = r;
    }

    void print(){
        std::cout << name << " " << left << " " << right << std::endl; 
    }
};

std::map<std::string, Node> readInput()
{
    std::map<std::string, Node> nodeMap;
    std::ifstream file("data/day8.txt");
    auto start = std::istream_iterator<std::string>(file);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    auto t = *s;
    NAV = t;
    s++;
    while(s!=end){
        auto n = *s;        
        s++;
        auto l = *s;
        s++;
        auto r = *s;
        s++;
        nodeMap[n] = Node(n,l,r);
    }
    return nodeMap;
}


std::vector<std::string> findStarts(std::map<std::string, Node> const &nodeMap){
    std::vector<std::string> starts;
    for(auto n:nodeMap){
        if(n.first[2] == 'A'){
            starts.push_back(n.first);
        }
    }
    return starts;
}

void part1(std::map<std::string, Node> nodeMap){
    std::string cur = "AAA";
    int step = 0;
    while(cur != "ZZZ"){
        for(auto i:NAV){
            if(i == 'L'){
                cur = nodeMap[cur].left;
            }
            else{
                cur = nodeMap[cur].right;
            }
            step++;
            if(cur == "ZZZ"){
                break;
            }
        }
    }
    std::cout << "ans1: " << step << std::endl;
}

bool checkCur(std::vector<std::string> const &cur){
    for(auto c : cur){
        if(c[2] != 'Z'){
            return false;
        }
    }
    return true;
}

void part2(std::map<std::string, Node> nodeMap){
    auto starts = findStarts(nodeMap);
    int step = 0;
    std::vector<std::string> cur = starts;
    while(true){
        for(auto nav:NAV){
            if(nav == 'L'){
                for(int i = 0; i<cur.size();i++)
                    cur[i] = nodeMap[cur[i]].left;
            }
            else{
                for(int i = 0; i<cur.size();i++)
                    cur[i] = nodeMap[cur[i]].right;
            }
            step++;
            if(checkCur(cur)){
                break;
            }
        }
        std::cout << step << std::endl;
        if(checkCur(cur)){
            break;
        }
    }
    std::cout << "ans2: " << step << std::endl;
}

int main(int argc, char * argv[]){
    auto input = readInput();
    // part1(input);
    part2(input);
}
