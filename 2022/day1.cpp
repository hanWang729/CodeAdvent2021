#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>

std::vector<std::vector<int>> readInput()
{
    std::vector<std::vector<int>> returnValue;
    std::ifstream file("data/day1.txt");
    auto start = std::istream_iterator<int>(file);
    auto end = std::istream_iterator<int>();
    std::vector<int> tmpValue(start,end);
    std::vector<int> tmpVector;
    for(auto i : tmpValue){
        if(i!=-1){
            tmpVector.push_back(i);
        }
        else{
            returnValue.push_back(tmpVector);
            tmpVector.clear();
        }
    }
    return returnValue;
}

std::vector<int> sum(std::vector<std::vector<int>> inputVector){
    std::vector<int> returnVector;
    int sum;
    for(auto i : inputVector){
        sum = std::accumulate(i.begin(),i.end(),0);
        returnVector.push_back(sum);
    }
    return returnVector;
}

int main(int argc, char * argv[]){
    auto input = readInput();
    auto sumVector = sum(input);

    std::sort(sumVector.begin(), sumVector.end());
    std::cout << sumVector[sumVector.size() - 1] << std::endl;

    std::cout << std::accumulate(sumVector.end()-3,sumVector.end(),0) << std::endl;

}
