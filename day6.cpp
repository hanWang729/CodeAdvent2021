#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <array>
#include <utility>
#include <set>

struct Game
{
    long int time;
    long int distance;

    Game(int t, int d){
        time = t;
        distance = d;
    }

    Game(long int t, long int d){
        time = t;
        distance = d;
    }

    long int play(){
        long int count = 0;
        long int d;
        for(long int i = 0; i <= time; i++){
            d = i * (time - i);
            if (d > distance){
                count++;
            }
        }
        return count;
    }
};


struct GameSet{
    std::vector<Game> games;

    GameSet(std::vector<int> const &input){
        int n;
        n = input.size()/2;
        for(int i = 0; i < n; i++){
            games.push_back(Game(input[i],input[i+n]));
        }
    }

    void print(){
        for(auto g:games){
            std::cout << g.time << " " << g.distance << std::endl;
        }
    }
};

GameSet readInput(){
    std::vector<int> inputVector;
    std::ifstream input("data/day6e.txt");
    auto start = std::istream_iterator<int>(input);
    auto end = std::istream_iterator<int>();
    auto s = start;
    while(s!=end){
        int t = *s;
        inputVector.push_back(t);
        s++;
    }
    return GameSet(inputVector);
}

void part1(GameSet gs){
    int ans = 1;
    for(auto g : gs.games){
        ans*=g.play();
    }
    std::cout <<"ans1: " << ans << std::endl;
}

void part2(){
    long int t = 55999793;
    long int d = 401148522741405;
    Game g = Game(t, d);
    int ans = g.play();
    std::cout <<"ans2: " << ans << std::endl;
}

int main(int argc, char * argv[]){
    auto input = readInput();
    // input.print();
    // part1(input);
    part2();
    // test(input);
}