#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <array>
#include <utility>
#include <set>

int INPUTSIZE=21;

std::vector<std::vector<int>> readInput(){
    std::vector<int> inputVector;
    std::vector<std::vector<int>> returnValue;
    std::ifstream input("data/day9.txt");
    auto start = std::istream_iterator<int>(input);
    auto end = std::istream_iterator<int>();
    auto s = start;
    while(s!=end){
        int t = *s;
        inputVector.push_back(t);
        s++;
        if(inputVector.size()==INPUTSIZE){
            returnValue.push_back(inputVector);
            inputVector.clear();
        }
    }
    return returnValue;
}

bool check_zero(std::vector<int> const &seq){
    for(auto i : seq){
        if(i!=0){
            return false;
        }
    }
    return true;
}

void dif1(std::vector<int> &seq, std::vector<int> &back_seq){
    std::vector<int> temp_seq;
    for(int i = 0; i < seq.size() - 1; i++){
        temp_seq.push_back(seq[i+1] - seq[i]);
    }
    back_seq.push_back(temp_seq[temp_seq.size()-1]);
    seq = temp_seq;
}

int dif_helper1(std::vector<int> &seq){
    std::vector<int> backseq;
    backseq.push_back(seq[seq.size()-1]);
    while(!check_zero(seq)){
        dif1(seq,backseq);
    }
    return std::accumulate(backseq.begin(),backseq.end(),0);
}

void part1(std::vector<std::vector<int>> input){
    int sum = 0;
    for(auto i:input){
        int n = dif_helper1(i);
        sum+=n;
    }
    std::cout << "part1: " << sum << std::endl;

}

void dif2(std::vector<int> &seq, std::vector<int> &back_seq){
    std::vector<int> temp_seq;
    for(int i = 0; i < seq.size() - 1; i++){
        temp_seq.push_back(seq[i+1] - seq[i]);
    }
    back_seq.push_back(temp_seq[0]);
    seq = temp_seq;
}

int dif_helper2(std::vector<int> &seq){
    std::vector<int> backseq;
    backseq.push_back(seq[0]);
    while(!check_zero(seq)){
        dif2(seq,backseq);
    }
    // for(auto i:backseq){
    //     std::cout << i << " ";
    // }
    // std::cout << std::endl;
    int c = 1;
    int sum = 0;
    for(auto b:backseq){
        sum+=b*c;
        c*=-1;
    }
    return sum;
}

void part2(std::vector<std::vector<int>> input){
    int sum = 0;
    for(auto i:input){
        int n = dif_helper2(i);
        // std::cout << "test: " << n << std::endl;
        sum+=n;
    }
    std::cout << "part2: " << sum << std::endl;

}

void print(std::vector<std::vector<int>> input){
    for(auto i : input){
        for(auto j : i){
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char * argv[]){
    auto input = readInput();
    // print(input);
    // part1(input);
    part2(input);
}