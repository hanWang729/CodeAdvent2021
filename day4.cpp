#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <array>
#include <utility>
#include <set>

struct Card{
    std::vector<int> wins;
    std::vector<int> items;
    int point;
    int winner;
    int num = 1;

    Card(std::vector<int> const &w, std::vector<int> const&i){
        wins = w;
        items = i;
        calPoint();
    }

    void calPoint(){
        int p = 0;
        for(auto i:items){
            if(std::find(wins.begin(), wins.end(), i) != wins.end()){
                p++;
            }
        }
        winner = p;
        if(p==0)
            point = 0;
        else{
            int c = 1;
            for(int i = 0; i < p-1; i++){
                c*=2;
            }
            point = c;
        }
    }

    void print(){
        std::cout << "Card: ";
        for(auto w : wins){
            std::cout << w << " ";
        }
        std::cout << "| ";
        for(auto i : items){
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
};


std::vector<Card> readInput(){
    std::vector<Card> returnValue;
    std::ifstream input("data/day4.txt");
    auto start = std::istream_iterator<int>(input);
    auto end = std::istream_iterator<int>();
    auto s = start;
    std::vector<int> wins;
    std::vector<int> items;
    s++;
    while(s!=end){
        int t = *s;
        while(t!=-2){
            wins.push_back(t);
            s++;
            t = *s;
        }
        s++;
        t = *s;
        while(t!=-1){
            items.push_back(t);
            s++;
            t = *s;
        }
        s++;
        returnValue.push_back(Card(wins,items));
        wins.clear();
        items.clear();
    }
    return returnValue;
}

void part1(std::vector<Card> inputCard){
    int ans1 = 0;
    for(auto i : inputCard){
        // std::cout << i.point << std::endl;
        ans1 += i.point;
    }
    std::cout << "ans1: " << ans1 << std::endl;
}

void part2(std::vector<Card> inputCard){
    int ans2 = 0;
    for(int i=0; i<inputCard.size();i++){
        int wins = inputCard[i].winner;
        for(int w = 0; w < wins; w++){
            // std::cout<< "i:" << i << " w:" << w<< std::endl;
            inputCard[i+w+1].num += inputCard[i].num;
        }
    }
    for(auto i : inputCard){
        // std::cout << i.num << std::endl;
        ans2 += i.num;
    }
    std::cout << "ans2: " << ans2 << std::endl;
}

int main(int argc, char * argv[]){
    auto input = readInput();
    part2(input);
}