#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <cstring>
#include <map>

std::map<std::string, std::vector<std::string>> readMap(){
    std::ifstream input("data/day14.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    std::vector<std::string> outputVector;
    std::map<std::string, std::vector<std::string>> returnMap;
    auto s = start;
    while(s!=end){
        const std::string input = *s;
        s++;
        const std::string output = *s;
        outputVector.push_back(input[0]+output);
        outputVector.push_back(output+input[1]);
        returnMap[input]=outputVector;
        outputVector.clear();
        s++;
    }
    return returnMap;
}

void printMap(std::map<std::string, std::vector<std::string>> readMap){
    for(auto m : readMap){
        std::cout << m.first << "\t" << m.second[0] << m.second[1] << std::endl;
    }
}

void printResult(std::map<std::string, long long> resultMap){
    for(auto m : resultMap){
        std::cout << m.first << "\t" << m.second<< std::endl;
    }
}

std::map<std::string, long long> insert(std::map<std::string, long long> startPoint, std::map<std::string, std::vector<std::string>> inputMap, int n){
    auto returnMap = startPoint;
    std::map<std::string, long long> midMap;
    for(int i=0;i<n;i++){
        for(auto s : returnMap){
            auto input = s.first;
            auto output = inputMap[input];
            if(midMap.count(output[0]) > 0){
                midMap[output[0]] += s.second;
            }
            else{
                midMap[output[0]] = s.second;
            }
            if(midMap.count(output[1]) > 0){
                midMap[output[1]] += s.second;
            }
            else{
                midMap[output[1]] = s.second;
            }
        }
        returnMap = midMap;
        midMap.clear();
    }
    return returnMap;
}

long long countResult(std::map<std::string, long long> resultMap, char begin, char end){
    std::map<char,long long> countMap;
    for(auto rm : resultMap){
        std::string s = rm.first;
        if(countMap.count(s[0]) > 0){
            countMap[s[0]] += rm.second;
        }
        else{
            countMap[s[0]] = rm.second;
        }
        if(countMap.count(s[1]) > 0){
            countMap[s[1]] += rm.second;
        }
        else{
            countMap[s[1]] = rm.second;
        }
    }
    countMap[begin]+=1;
    countMap[end]+=1;
    long long max = countMap[begin];
    long long min = countMap[begin];
    for(auto cm:countMap){
        if(max<cm.second){
            max = cm.second;
        }
        if(min>cm.second){
            min=cm.second;
        }
    }
    return (max - min) / 2;
}

int main(int argc, char* argv[]){
    auto inputMap = readMap();
    std::string startPoint = "HBCHSNFFVOBNOFHFOBNO";
    // std::string startPoint = "NNCB";
    std::map<std::string, long long> startMap;
    for(int i=0;i<startPoint.length()-1;i++){
        std::string s = startPoint.substr(i,2);
        if(startMap.count(s)>0){
            startMap[s]++;
        }
        else{
            startMap[s]=1;
        }
    }
    for(int i = 0;i<=40;i++){
        auto result1 = insert(startMap,inputMap,i);
        long long count1 = countResult(result1,startPoint[0],startPoint[startPoint.length()-1]);
        std::cout << "part1: " << count1 << std::endl;
    }

    // auto result1 = insert(startMap,inputMap,40);
    // long long count1 = countResult(result1,startPoint[0],startPoint[startPoint.length()-1]);
    // std::cout << "part1: " << count1 << std::endl;
    
    // printResult(result);
    // printMap(inputMap);
}