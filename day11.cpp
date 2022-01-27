#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <set>

const int vectorSize = 10;

struct InputVector{
    std::vector<std::vector<int>> v;
    std::set<int> flashSet;
    std::set<int> flashedSet;
    InputVector(){
        std::vector<int> intialLine(vectorSize+2, 9);
        v.push_back(intialLine);
    }
    void push_back(std::string const &s){
        std::vector<int> nextLine(vectorSize+2,9);
        std::string str;
        for(int i = 0; i < s.length(); i++){
            str = s[i];
            nextLine[i+1] = std::stoi(str);
        }
        v.push_back(nextLine);
    }

    int runUntilFlashSimult(){
        int round = 0;
        while(flashedSet.size()!=vectorSize*vectorSize){
            flashedSet.clear();
            add_one();
            countFlash();
            while(flashSet.size()!=0){
                flashing();
                countFlash();
            }
            setFlashedToZero();
            round++;
        }
        return round;
    }

    int runInRound(int round){
        int count = 0;
        for(int i=0; i<round; i++){
            add_one();
            countFlash();
            while(flashSet.size()!=0){
                flashing();
                countFlash();
            }
            count += flashedSet.size();
            setFlashedToZero();
            flashedSet.clear();
        }
        return count;
    }

    void add_one(){
        for(auto &line : v){
            for(auto &i : line){
                i++;
            }
        }
    }

    void countFlash(){
        flashSet.clear();
        for(int i = 1; i < vectorSize + 1; i ++){
            for(int j = 1; j < vectorSize + 1; j++){
                if(v[i][j] > 9 && flashedSet.count(i*100+j) != 1){
                    flashSet.insert(i*100+j);
                }
            }
        }
    }

    void flashing(){
        
        for(int fs : flashSet){
            int x = fs / 100;
            int y = fs % 100;
            for(int i = x-1; i <= x+1; i++){
                for(int j = y-1; j <= y+1; j++){
                    v[i][j]++;
                }
            }
        }
        flashedSet.insert(flashSet.begin(),flashSet.end());
        flashSet.clear();
    }

    void setFlashedToZero(){
        for(int i : flashedSet){
            v[i/100][i%100] = 0;
        }
    }

    void push_last_line(){
        std::vector<int> lastLine(vectorSize+2,9);
        v.push_back(lastLine);
    }

    void printInputVector(){
        for(auto line : v){
            for(auto i : line){
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    }
};

InputVector readInput(){
    InputVector inputVector;
    std::ifstream input("data/day11.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    while(s!=end){
        const std::string t = *s;
        s++;
        inputVector.push_back(t);
    }
    inputVector.push_last_line();
    return inputVector;
}

void part1(){
    auto inputVector = readInput();
    int ans = inputVector.runInRound(100);
    std::cout << "part1: " << ans << std::endl;
}

void part2(){
    auto inputVector = readInput();
    int ans = inputVector.runUntilFlashSimult();
    std::cout << "part2: " << ans << std::endl;
}

int main(int argc, char* argv[]){
    part1();
    part2();
}