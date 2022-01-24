#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <map>

struct inputDigits{
    std::vector<std::string> inputs;
    std::vector<std::string> outputs;
    std::map<std::string, int> digitsMap;

    inputDigits(std::vector<std::string> const &combinedInputs){
        std::string s;
        for (int i = 0; i < 10; i++){
            s = combinedInputs[i];
            sort(s.begin(),s.end());
            inputs.push_back(s);
        }
        for (int i = 11; i < 15; i++){
            s = combinedInputs[i];
            sort(s.begin(),s.end());
            outputs.push_back(s);
        }
    }

    int countOutput1478(){
        int count = 0;
        for(auto o : outputs){
            int l = o.length();
            if(l == 2 || l == 3 || l == 4 || l == 7){
                count++;
            }
        }
        return count;
    }

    void print(){
        for(auto i : inputs){
            std::cout << i << " ";
        }
        std::cout << "| ";
        for(auto o : outputs){
            std::cout << o << " ";
        }
        std::cout << std::endl;
    }
};


// std::vector<std::string> readInput(){
//     std::vector<std::string> inputVector;
//     std::ifstream file("data/day8.txt");
//     std::string t;
//     while(!file.eof()){
//         file >> t;
//         inputVector.push_back(t);
//     }
//     return inputVector;
// }

std::vector<inputDigits> readInput(){
    std::vector<inputDigits> inputVector;
    std::vector<std::string> templateVector;
    std::ifstream input("data/day8.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    while(s!=end){
        const std::string t = *s;
        s++;
        templateVector.push_back(t);
        if(templateVector.size() == 15){
            inputVector.push_back(inputDigits(templateVector));
            templateVector.clear();
        }
    }
    return inputVector;
}

void part1(){
    auto inputs = readInput();
    int ans = 0;
    for(auto i : inputs){
        ans += i.countOutput1478();
    }
    std::cout << "Ans1:" << ans <<std::endl;
}

int main(int argc, char * argv[]) {
    // part1();
    auto inputs = readInput();
    for(auto i : inputs){
        i.print();
    }
    
}