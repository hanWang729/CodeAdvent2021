#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <cstring>
#include <sstream>
#include <set>
#include <algorithm>

const int vectorSizeRow = 102;
const int VectorSizeColumn = 102;

struct InputVector{
    std::vector<std::vector<int>> inputVector;
    std::set<int> lowestPointSet;

    InputVector(){
        std::vector<int> initialLine(VectorSizeColumn,9);
        inputVector.push_back(initialLine);
    }

    void push_back(std::string const &s){
        std::vector<int> nextLine(VectorSizeColumn,9);
        std::string str;
        for(int i = 0; i < s.length(); i++){
            str = s[i];
            nextLine[i+1] = std::stoi(str);
        }
        inputVector.push_back(nextLine);
    }

    void push_last_line(){
        std::vector<int> lastLine(VectorSizeColumn,9);
        inputVector.push_back(lastLine);
    }

    void find_lowest_point(){
        for(int i=1; i < vectorSizeRow-1; i++){
            for(int j=1; j<VectorSizeColumn-1; j++){
                int val = inputVector[i][j];
                if(val<inputVector[i+1][j] && val<inputVector[i-1][j] && val<inputVector[i][j+1] && val<inputVector[i][j-1]){
                    lowestPointSet.insert(i*1000+j);
                }
            }
        }
    }

    int calculateRisk(){
        int risk = 0;
        for(int i=1; i < vectorSizeRow-1; i++){
            for(int j=1; j<VectorSizeColumn-1; j++){
                if(lowestPointSet.count(i*1000+j) == 1){
                    risk += (inputVector[i][j] + 1);
                }
            }
        }
        return risk;
    }

    int calBasin(int xy_center){
        std::set<int> set_center;
        std::set<int> set_border;
        std::set<int> set_border_tmp;
        set_border.insert(xy_center);
        while(!set_border.empty()){
            int temp;
            for(std::set<int>::iterator it=set_border.begin(); it!=set_border.end(); it++){
                temp = *it;
                int x = temp / 1000;
                int y = temp % 1000;
                if(inputVector[x+1][y] != 9 && set_center.count(temp) == 0){
                    set_border_tmp.insert((x+1) * 1000 + y);
                }
                if(inputVector[x-1][y] != 9 && set_center.count(temp) == 0){
                    set_border_tmp.insert((x-1) * 1000 + y);
                }
                if(inputVector[x][y+1] != 9 && set_center.count(temp) == 0){
                    set_border_tmp.insert(x * 1000 + y+1);
                }
                if(inputVector[x][y-1] != 9 && set_center.count(temp) == 0){
                    set_border_tmp.insert(x * 1000 + y-1);
                }
                set_center.insert(temp);
            }   
            set_border.erase(temp);
            set_border.insert(set_border_tmp.begin(), set_border_tmp.end());
            set_border_tmp.clear();
        }
        return set_center.size();
    }

    void printInputVector(){
        for(auto line : inputVector){
            for(auto i : line){
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    }

    void printLowestPointVector(){
        for(auto i : lowestPointSet){
            std::cout << i << " ";            
        }
    }
};

InputVector readInput(){
    InputVector inputVector;
    std::ifstream input("data/day9.txt");
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
    inputVector.find_lowest_point();
    auto ans = inputVector.calculateRisk(); 
    std::cout << "part1: " << ans << std::endl;
}

void part2(){
    auto inputVector = readInput();
    inputVector.find_lowest_point();
    std::vector<int> ansv;
    int ans = 1;
    for(auto i : inputVector.lowestPointSet){
        ansv.push_back(inputVector.calBasin(i));
    }
    std::sort(ansv.begin(),ansv.end());

    for(int i = 0; i < 3; i++){
        ans *= ansv.back();
        ansv.pop_back();
    }
    std::cout << "part2: " << ans << std::endl;
}

int main(int argc, char* argv[]){
    part1();
    part2();
}