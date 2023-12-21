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

int findfirst(std::map<std::string, Node> nodeMap, std::string start){
    std::string cur = start;
    int step = 0;
    while(true){
        for(auto i:NAV){
            if(i == 'L'){
                cur = nodeMap[cur].left;
            }
            else{
                cur = nodeMap[cur].right;
            }
            step++;
            if(cur[2] == 'Z'){
                return step;
                // std::cout << "s: " << step <<std::endl;
            }
        }
    }
}

long int GCD(long int a, long int b){
    long int temp = 0;
    while(b!=0){
        temp = a;
        a = b;
        b = temp%b;
    }
    return a;
}

void part2(std::map<std::string, Node> nodeMap){
    auto starts = findStarts(nodeMap);
    int step = 0;
    long int m = 1;
    std::vector<int> firsts;
    for(auto s:starts){
        firsts.push_back(findfirst(nodeMap,s));
    }
    // for(auto f:firsts){
    //     std::cout << f << std::endl;
    // }
    long int a;
    long int b;
    long int temp;
    a = firsts[0];
    for(int i = 1; i < firsts.size();i++){
        b = firsts[i];
        temp = GCD(a,b);
        std::cout << temp << std::endl;
        a = a*b/temp;
    }
    std::cout << "ans2: " << a << std::endl;
}

void test(std::map<std::string, Node> nodeMap){
    auto starts = findStarts(nodeMap);
    int step = 21409 * 2;
    std::string cur = starts[0];
    while(step>0){
        for(auto i:NAV){
            if(i == 'L'){
                cur = nodeMap[cur].left;
            }
            else{
                cur = nodeMap[cur].right;
            }
            step--;
            if(step == 0){
                break;
            }
        }
    }
    std::cout << "test: " << cur << std::endl;
}

int main(int argc, char * argv[]){
    auto input = readInput();
    // part1(input);
    // part2(input);
    test(input);
}
