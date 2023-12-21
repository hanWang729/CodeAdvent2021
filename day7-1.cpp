#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <map>
#include <sstream>
#include <string>

enum TYPE{
    HIGH,
    ONEPAIR,
    TWPPAIR,
    THREE,
    FULL,
    FOUR,
    FIVE
};

std::map<char, int> label_weight = {
    {'A',14},{'K',13},{'Q',12},
    {'J',11},{'T',10},{'9',9},
    {'8',8},{'7',7},{'6',6},
    {'5',5},{'4',4},{'3',3},
    {'2',2}
    };

struct Hand{
    TYPE type;
    std::string card;
    int bid;

    Hand(std::string c, std::string b){
        card = c;
        bid = std::stoi(b);
        calType();
    }

    void calType(){
        std::map<char,int> lable_map;
        for(auto c : card){
            if(lable_map.count(c) == 0){
                lable_map.insert({c,1});
            }
            else{
                lable_map[c]++;
            }
        }
        if(lable_map.size() == 1){
            type = FIVE;
        }
        else if(lable_map.size() == 5){
            type = HIGH;
        }
        else if(lable_map.size() == 4){
            type = ONEPAIR;
        }
        else if(lable_map.size() == 2){
            type = FULL;
            for(auto lp: lable_map){
                if(lp.second == 4){
                    type = FOUR;
                    break;
                }
            }
        }
        else if(lable_map.size() == 3){
            type = TWPPAIR;
            for(auto lp: lable_map){
                if(lp.second == 3){
                    type = THREE;
                    break;
                }
            }
        }
    }

    void print(){
        std::cout << card << " " << bid << " " << type << std::endl;
    }

    bool operator < (const Hand& h){
        if(type != h.type){
            return type < h.type;
        }
        else{
            for(int i = 0; i < card.length();i++){
                if(card[i] != h.card[i]){
                    return label_weight[card[i]] < label_weight[h.card[i]];
                }
            }
        }
        return false;
    }
};

std::vector<Hand> readInput()
{
    std::vector<Hand> returnValue;
    std::ifstream file("data/day7.txt");
    auto start = std::istream_iterator<std::string>(file);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    while(s!=end){
        auto t1 = *s;
        s++;
        auto t2 = *s;
        s++;
        returnValue.push_back(Hand(t1,t2));
    }
    return returnValue;
}

void part1(std::vector<Hand> input){
    std::sort(input.begin(),input.end());
    int c = 1;
    int ans = 0;
    for(auto i : input){
        ans += c * i.bid;
        c++;
    }
    std::cout << "part1: " << ans << std::endl;
}

int main(int argc, char * argv[]){
    auto input = readInput();
    part1(input);
}
