#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <cstring>
#include <sstream>
#include <set>
#include <map>
#include <algorithm>
#include <iomanip>
#include <list>
#include <stack>

struct Pair
{
    std::string left;
    std::string right;
    int right_order;

    Pair(std::string l, std::string r){
        left = l;
        right = r;
    }

    void print(){
        std::cout << "left pair : " << left << std::endl;
        std::cout << "right pair: " << right << std::endl;
    }


};


std::vector<int> findChar(std::string s, std::string t){
    std::size_t index = 0;
    std::vector<int> returnValue;
    while ((index = s.find(t, index)) != std::string::npos) {
        returnValue.push_back(index);
        index += t.length();
    }
    return returnValue;
}

void test_findChar(){
    std::string s = "[[6,[4,[4,10,7]],[[0,8,6],2],[[],8,[7,10,6,4,2],[10,10],6],4]]";
    std::string t = "[";

    auto index = findChar(s,t);

    for(int i : index){
        std::cout << i << std::endl;
    }
}

std::map<int, int> mapSquare(std::vector<int> left_index,
                                         std::vector<int> right_index){
    std::stack<int> waitingList;
    std::map<int, int> returnValue;
    for(auto l : left_index){
        if (l < right_index[0]){
            waitingList.push(l);
        }
        else{
            while(l > right_index[0]){
                returnValue[waitingList.top()] = right_index[0];
                right_index.erase(right_index.begin());
                waitingList.pop();
            }
            waitingList.push(l);
        }
    }
    while(!waitingList.empty()){
        int l = waitingList.top();
        returnValue[l] = right_index[0];
        right_index.erase(right_index.begin());
        waitingList.pop();
    }

    // for(auto i : returnValue){
    //     std::cout << i.first << ": " << i.second << std::endl;
    // }

    return returnValue;
}

std::vector<std::string> splitString(std::string s){
    std::vector<std::string> returnVector;
    std::vector<int> left_index = findChar(s,"[");
    std::vector<int> right_index = findChar(s,"]");
    std::map<int,int> mapList = mapSquare(left_index,right_index);
    int len = 1;
    int i1 = 0,i2 = 0;
    for(int i = 1; i < s.length() - 1; i++){
        // std::cout << "i: " << i << std::endl;
        if(s.substr(i,len) == "["){
            i1 = i;
            i2 = mapList[i1];
            // std::cout << "i2: " << i2 << std::endl;
            // for(auto lll : left_index){
            //     std::cout << "lll: " << lll << std::endl;
            // }
            // for(auto lll : right_index){
            //     std::cout << "rrr: " << lll << std::endl;
            // }
            // std::cout << "i2: " << i2 << std::endl;
            len = i2-i1+1;
            returnVector.push_back(s.substr(i1,len));
            i = i1+len;
        }
        else if(std::isdigit(s[i])){
            i1 = i;
            while(std::isdigit(s[i+1])){
                len++;
                i++;
            }
            returnVector.push_back(s.substr(i1,len));
        }
        len = 1;
    } 
    return returnVector;
}

void testSplitString(){
    std::string s = "[[[9,6,2,5,[4,6,6,8,2]],1,4,10],[[[2,10,9,8],6,1,[0]],[[],[8]]],[[9,[0,7,8],6],[[],9,[5,5],[3]]],[6,3,[7,[1],[0,10,10,2,1],[7]],6,[4,2,3,[]]],[[0,4,[5,4,2,9,5],[2,10],4],5,6,[5,8,4],[[4],5]]]";
    auto stringVector = splitString(s);
    // stringVector = splitString(stringVector[0]);
    std::cout << "test result" << std::endl;
    for(auto i : stringVector){
        std::cout << i << std::endl;
    }
}

std::vector<Pair> readInput(){
    std::vector<Pair> inputVector;
    std::ifstream input("data/day13.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    while(s!=end){
        const std::string p1 = *s;
        s++;
        const std::string p2 = *s;
        s++;
        inputVector.push_back(Pair(p1,p2));
    }
    return inputVector;
}

int Compare(std::string left, std::string right){

    // std::cout << "left : " << left << std::endl;
    // std::cout << "right: " << right << std::endl;

    std::vector<std::string> leftItems = splitString(left);
    std::vector<std::string> rightItems = splitString(right);

    std::string compareL;
    std::string compareR;

    int result;

    //1. Empty or not
    if(leftItems.empty() && rightItems.empty()){
        return 0;
    }
    else if(leftItems.empty() || rightItems.empty()){
        if(leftItems.empty())
            return 1;
        else
            return -1;
    }
    //2. Take element one by one
    while(!(leftItems.empty() || rightItems.empty())){
        compareL = leftItems[0];
        compareR = rightItems[0];
        // std::cout << "compareL: " << compareL << std::endl;
        // std::cout << "compareR: " << compareR << std::endl;
        if(std::all_of(begin(compareL), end(compareL), isdigit) && std::all_of(begin(compareR), end(compareR), isdigit)){
            if(std::stoi(compareL) < std::stoi(compareR))
                return 1;
            else if(std::stoi(compareL) > std::stoi(compareR))
                return -1;
            else{
                leftItems.erase(leftItems.begin());
                rightItems.erase(rightItems.begin());
            }   
        }
        else{
            if(std::all_of(begin(compareL), end(compareL), isdigit)){
                compareL = "[" + compareL + "]";
            }
            if(std::all_of(begin(compareR), end(compareR), isdigit)){
                compareR = "[" + compareR + "]";
            }
            result = Compare(compareL,compareR);
            if(result == 0){
                leftItems.erase(leftItems.begin());
                rightItems.erase(rightItems.begin());
            }
            else{
                return result;
            }
        }

    }
    if(leftItems.empty() && rightItems.empty()){
        return 0;
    }
    else if(leftItems.empty() || rightItems.empty()){
        if(leftItems.empty())
            return 1;
        else
            return -1;
    }
    return 9;
}

void testCompare(){
    std::string left = "[[[9,6,2,5,[4,6,6,8,2]],1,4,10],[[[2,10,9,8],6,1,[0]],[[],[8]]],[[9,[0,7,8],6],[[],9,[5,5],[3]]],[6,3,[7,[1],[0,10,10,2,1],[7]],6,[4,2,3,[]]],[[0,4,[5,4,2,9,5],[2,10],4],5,6,[5,8,4],[[4],5]]]";
    std::string right = "[[4,0,7,[1,[2,7,2],5,[6]],5],[3,[1,10,[10,4,5,9],8]],[7],[[0],[],6,8],[[[1,2],10,3,8,[]],0,7]]";
    int result = Compare(left,right);
    std::cout << "compare results: " << result << std::endl;
}

int main(int argc, char * argv[]){
    // testSplitString();
    // testCompare();
    auto input = readInput();
    int sum  = 0;
    int index = 1;
    for(auto i : input){
        // i.print();
        i.right_order = Compare(i.left,i.right);
        if(i.right_order == 1)
            sum+=index;
        index++;
    }
    std::cout << "part1: " << sum << std::endl;
    
}