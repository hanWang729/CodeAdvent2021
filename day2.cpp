#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <map>
#include <sstream>
#include <string>

enum COLOR{
    Blue,
    Red,
    Green
};

std::vector<std::string> readInput()
{
    std::vector<std::string> returnValue;
    std::ifstream file("data/day2.txt");
    auto start = std::istream_iterator<std::string>(file);
    auto end = std::istream_iterator<std::string>();
    std::vector<std::string> tmpValue(start,end);
    std::string tmpVector;
    for(auto i : tmpValue){
        returnValue.push_back(i);
    }
    return returnValue;
}

std::vector<std::map<COLOR,int>> translateInput(std::string input){
    std::stringstream inputStringStream(input);
    std::string segment;
    std::vector<std::string> seglist;
    // std::cout << "test0: "<< std::endl;
    while(std::getline(inputStringStream, segment, ':')){
        seglist.push_back(segment);
    }
    std::string games = seglist[1];
    // std::cout << "test1: " << games << std::endl;
    seglist.clear();
    std::stringstream gameStringStream(games);
    while(std::getline(gameStringStream, segment, ';')){
        seglist.push_back(segment);
    }
    std::vector<std::string> gameList = seglist;
    seglist.clear();
    std::map<COLOR,int> colormap;
    std::vector<std::map<COLOR,int>> returnValue;
    for(auto game : gameList){
        std::stringstream gStringStream(game);
        while(std::getline(gStringStream, segment, '_')){
            seglist.push_back(segment);
        }

        for(int i = 1; i < seglist.size(); i+=2){
            if(seglist[i+1][0] == 'b'){
                colormap[Blue] = std::stoi(seglist[i]);
            }
            else if(seglist[i+1][0] == 'g'){
                colormap[Green] = std::stoi(seglist[i]);
            }
            else if(seglist[i+1][0] == 'r'){
                colormap[Red] = std::stoi(seglist[i]);
            }
        }
        returnValue.push_back(colormap);
        colormap.clear();
        seglist.clear();
    }
    return returnValue;
}

void testInput(std::vector<std::vector<std::map<COLOR,int>>> inputVector){
    int c = 1;
    for(auto i : inputVector){
        std::cout << "G " << c << ":";
        for(auto g : i){
            std::cout << "Gr: " << g[Green] << ", Bl: " << g[Blue] << ", Re: " <<g[Red] << ";";
        }
        std::cout << std::endl;
        c++;
    }
}

bool testPossible(std::vector<std::map<COLOR,int>> gameSet){
    for(auto game : gameSet){
        if(game[Red] > 12 || game[Green] > 13 || game[Blue] > 14){
            return false;
        }
    }
    return true;
}

int findLowest(std::vector<std::map<COLOR,int>> gameSet){
    int b = 0;
    int r = 0;
    int g = 0;
    for(auto game : gameSet){
        if(game[Red] > r){
            r = game[Red];
        }
        if(game[Green] > g){
            g = game[Green];
        }
        if(game[Blue] > b){
            b = game[Blue];
        }
    }
    return b * r * g;
}

void part1(std::vector<std::vector<std::map<COLOR,int>>> inputVector){
    int c = 1;
    int ans = 0;
    for(auto i : inputVector){
        if(testPossible(i)){
            ans += c;
        }
        c++;
    }
    std::cout << "ans1: " << ans << std::endl;
}

void part2(std::vector<std::vector<std::map<COLOR,int>>> inputVector){
    int ans = 0;
    for(auto i : inputVector){
        ans += findLowest(i);
    }
    std::cout << "ans2: " << ans << std::endl;
}

int main(int argc, char * argv[]){
    auto input = readInput();
    int ans1 = 0;
    int ans2 = 0;
    std::vector<std::vector<std::map<COLOR,int>>> inputVector;
    for(int i = 0; i < input.size(); i++){
        inputVector.push_back(translateInput(input[i]));
    }
    part1(inputVector);
    part2(inputVector);
}
