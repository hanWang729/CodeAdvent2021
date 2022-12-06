#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <cstring>
#include <map>

struct Game1{
    int oppo;
    int my;
    int winScore;
    int inputScore;
    int totalScore;

    Game1(std::string const & oppoInput, std::string const & myInput){
        if(oppoInput == "A")
            oppo = 1;
        else if(oppoInput == "B")
            oppo = 2;
        else if(oppoInput == "C")
            oppo = 3;

        if(myInput == "X")
            my = 1;
        else if(myInput == "Y")
            my = 2;
        else if(myInput == "Z")
            my = 3;
        inputScore = my;

        if(my - oppo == 0)
            winScore = 3;
        else if(my - oppo == 1 || my - oppo == -2)
            winScore = 6;
        else
            winScore = 0;

        totalScore = inputScore + winScore;
    }
};

struct Game2{
    int oppo;
    int my;
    int winScore;
    int inputScore;
    int totalScore;

    Game2(std::string const & oppoInput, std::string const & myInput){
        if(oppoInput == "A")
            oppo = 1;
        else if(oppoInput == "B")
            oppo = 2;
        else if(oppoInput == "C")
            oppo = 3;

        if(myInput == "X")
            my = oppo - 1;
        else if(myInput == "Y")
            my = oppo;
        else if(myInput == "Z")
            my = oppo + 1;
        if(my == 0)
            my = 3;
        if(my == 4)
            my = 1;
        inputScore = my;

        if(my - oppo == 0)
            winScore = 3;
        else if(my - oppo == 1 || my - oppo == -2)
            winScore = 6;
        else
            winScore = 0;

        totalScore = inputScore + winScore;
    }
};

std::vector<Game1> readInput_1()
{
    std::ifstream input("data/day2.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    std::vector<Game1> returnValue;
    auto s = start;
    while(s!=end){
        const std::string Oppo = *s;
        s++;
        const std::string My = *s;
        returnValue.push_back(Game1(Oppo,My));
        s++;
    }
    return returnValue;
}

std::vector<Game2> readInput_2()
{
    std::ifstream input("data/day2.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    std::vector<Game2> returnValue;
    auto s = start;
    while(s!=end){
        const std::string Oppo = *s;
        s++;
        const std::string My = *s;
        returnValue.push_back(Game2(Oppo,My));
        s++;
    }
    return returnValue;
}

int main(int argc, char * argv[]){
    auto input = readInput_1();
    int sum = 0;
    for(Game1 g : input){
        sum+= g.totalScore;
    }
    std::cout << sum << std::endl;

    auto input2 = readInput_2();
    sum = 0;
    for(Game2 g : input2){
        sum+= g.totalScore;
    }
    std::cout << sum << std::endl;
}
