#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>

std::vector<std::string> readInput()
{
    std::vector<std::string> returnValue;
    std::ifstream file("data/day1.txt");
    auto start = std::istream_iterator<std::string>(file);
    auto end = std::istream_iterator<std::string>();
    std::vector<std::string> tmpValue(start,end);
    std::string tmpVector;
    for(auto i : tmpValue){
        returnValue.push_back(i);
    }
    return returnValue;
}

int findNumber(std::string input){
    std::vector<int> tmp;
    for(auto i : input){
        if(isdigit(i) != 0){
            // std::cout << i << std::endl;
            tmp.push_back(int(i) - 48);
        }
    }
    // std::cout << "x: " << tmp[0] << "y: " << tmp.back() << std::endl;
    return tmp[0]*10 + tmp.back();
}

int findNumber2(std::string input){
    std::vector<int> tmp;
    char c;
    for(int i = 0; i <= input.length(); i++){
        // std::cout << i << std::endl;
        c = input[i];
        if(isdigit(c) != 0){
            tmp.push_back(int(c) - 48);
        }
        else if(c == 'o'){
            if(i + 3 <= input.size() && input.substr(i,3) == "one"){
                tmp.push_back(1);
            }
        }
        else if(c == 't'){
            if(i + 3 <= input.size() && input.substr(i,3) == "two"){
                tmp.push_back(2);
            }
            else if(i + 5 <= input.size() && input.substr(i,5) == "three"){
                tmp.push_back(3);
            }
        }
        else if(c == 'f'){
            if(i + 4 <= input.size() && input.substr(i,4) == "four"){
                tmp.push_back(4);
            }
            else if(i + 4 <= input.size() && input.substr(i,4) == "five"){
                tmp.push_back(5);
            }
        }
        else if(c == 's'){
            if(i + 3 <= input.size() && input.substr(i,3) == "six"){
                tmp.push_back(6);
            }
            else if(i + 5 <= input.size() && input.substr(i,5) == "seven"){
                tmp.push_back(7);
            }
        }
        else if(c == 'e'){
            if(i + 5 <= input.size() && input.substr(i,5) == "eight"){
                tmp.push_back(8);
            }
        }
        else if(c == 'n'){
            if(i + 4 <= input.size() && input.substr(i,4) == "nine"){
                tmp.push_back(9);
            }
        }
    }
    std::cout << tmp[0]*10 + tmp.back() << std::endl;
    return tmp[0]*10 + tmp.back();
    // return 0;
}

int main(int argc, char * argv[]){
    auto input = readInput();
    int ans1 = 0;
    int ans2 = 0;
    // for(auto i : input){
    //     ans1 += findNumber(i);
    // }
    // std::cout << "ans1: " << ans1 << std::endl;
    for(auto i : input){
        ans2 += findNumber2(i);
        // std::cout << i << std::endl;
    }
    std::cout << "ans2: " << ans2 << std::endl;
}
