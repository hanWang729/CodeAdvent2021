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
#include <map>

enum Resource{
    Ore,
    Clay,
    Obsidian,
    Geode,
};

std::map<Resource, std::string> ResourceString {{Ore,"Ore"},{Clay,"Clay"},{Obsidian,"Obsidian"},{Geode,"Geode"}};

struct Robot{
    Resource type;
    std::map<Resource, int> price;

    Robot(){}
    Robot(Resource t, std::map<Resource,int> const & p){
        type = t;
        price = p;
    }

    bool affordable(std::map<Resource, int> stock){
        for(auto s : stock){
            if(price.count(s.first) != 0){
                if(s.second < price[s.first])
                    return false;
            }
        }
        return true;
    }
};

struct Blueprint
{
    std::map<Resource, Robot> price_table;
    std::map<Resource, int> robot;
    std::map<Resource, int> stock;

    Blueprint(std::vector<Robot> const& robot_price_vector){
        for(auto r:robot_price_vector){
            price_table[r.type] = r;
        }
        robot[Ore] = 1;
        robot[Clay] = 0;
        robot[Obsidian] = 0;
        robot[Geode] = 0;
        stock[Ore] = 0;
        stock[Clay] = 0;
        stock[Obsidian] = 0;
        stock[Geode] = 0;
    }
    

    void print_price(){
        for(auto p : price_table){
            std::cout << "Each " << ResourceString[p.first] << " cost ";
            for(auto p0 : p.second.price){
                if(p.first == Ore || p.first == Clay){
                    std::cout << p0.second << " " << ResourceString[p0.first] << ". ";
                }
                else{
                    std::cout << p0.second << " " << ResourceString[p0.first] << " and, ";
                }
            }
        }
        std::cout << std::endl;
    }
};


std::vector<Blueprint> readInput()
{
    std::ifstream input("data/day19.txt");
    auto start = std::istream_iterator<int>(input);
    auto end = std::istream_iterator<int>();
    auto s = start;
    std::map<int, Resource> translate_table;
    translate_table[-1] = Ore;
    translate_table[-2] = Clay;
    translate_table[-3] = Obsidian;
    translate_table[-4] = Geode;
    std::map<Resource,int> tmp_price_map;
    std::vector<Robot> robotVector;
    std::vector<Blueprint> blueprintVector;
    while(s!=end){
        int ore_price_num = *s;
        s++;
        int ore_price_type = *s;
        s++;
        tmp_price_map[translate_table[ore_price_type]] = ore_price_num;
        robotVector.push_back(Robot(Ore,tmp_price_map));
        tmp_price_map.clear();
        int clay_price_num = *s;
        s++;
        int clay_price_type = *s;
        s++;
        tmp_price_map[translate_table[clay_price_type]] = clay_price_num;
        robotVector.push_back(Robot(Clay, tmp_price_map));
        tmp_price_map.clear();
        int obsdian_price_num1 = *s;
        s++;
        int obsdian_price_type1 = *s;
        s++;
        int obsdian_price_num2 = *s;
        s++;
        int obsdian_price_type2 = *s;
        s++;
        tmp_price_map[translate_table[obsdian_price_type1]] = obsdian_price_num1;
        tmp_price_map[translate_table[obsdian_price_type2]] = obsdian_price_num2;
        robotVector.push_back(Robot(Obsidian, tmp_price_map));
        tmp_price_map.clear();
        int geode_price_num1 = *s;
        s++;
        int geode_price_type1 = *s;
        s++;
        int geode_price_num2 = *s;
        s++;
        int geode_price_type2 = *s;
        s++;
        tmp_price_map[translate_table[geode_price_type1]] = geode_price_num1;
        tmp_price_map[translate_table[geode_price_type2]] = geode_price_num2;
        robotVector.push_back(Robot(Geode, tmp_price_map));
        tmp_price_map.clear();
        blueprintVector.push_back(Blueprint(robotVector));
        robotVector.clear();
    }
    return blueprintVector;
}

void test_affordable(){
    auto blueprints = readInput();
    for(auto b : blueprints){
        for(auto p : b.price_table){
            b.stock[Ore]+=5;
            b.stock[Clay]+=10;
            bool t = p.second.affordable(b.stock);
            std::cout << ResourceString[p.second.type] << ": " << t << std::endl;
        }
    }
}

int main(int argc, char* argv[]){
    auto blueprints = readInput();
}