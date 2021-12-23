#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

std::vector<int> readInput()
{
    std::ifstream input("data/day1.txt");
    auto start = std::istream_iterator<int>(input);
    auto end = std::istream_iterator<int>();
    std::vector<int> returnValue(start,end);
    return returnValue;
}

int increase_or_not(std::vector<int> const &input){
    
    int count = 0;
    
    for (int i = 0; i < input.size() - 1; i++) {
        if (input[i] < input[i+1])
            count++;
    }
    return count;
}

std::vector<int> window_sum(std::vector<int> const &input, int window_size){
    
    std::vector<int> returnValue;
    for (int i = 0; i < input.size() - window_size + 1; i++) {
        int n = input[i] + input[i+1] + input[i+2];
        returnValue.push_back(n);
    }
    return returnValue;
}

int main(int argc, char * argv[])
{
    auto input = readInput();
    auto ans1 = increase_or_not(input);
    std::cout << "Answer of part 1: " << ans1 << std::endl;

    auto windowedInput = window_sum(input,3);
    auto ans2 = increase_or_not(windowedInput);
    std::cout << "Answer of part 2: " << ans2 << std::endl;

}
