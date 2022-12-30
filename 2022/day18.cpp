#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <cstring>
#include <set>
#include <sstream>
#include <utility>
#include <algorithm>

struct Cube
{
    int x;
    int y;
    int z;

    Cube(int const& xi, int const& yi, int const& zi){
        x = xi;
        y = yi;
        z = zi;
    }

    bool adjacent(Cube c){
        int count = 0;
        if(c.x == x)
            count++;
        if(c.y == y)
            count++;
        if(c.z == z)
            count++;
        if(count == 2){
            if(abs(x+y+z-c.x-c.y-c.z) == 1){
                return true;
            }
        }
        if(count == 3)
            std::cout << "Error." << std::endl;
        return false;
    }
};

struct Lava
{
    std::vector<Cube> cubes;
    int sides;

    Lava(){
        sides = 0;
        cubes.clear();
    }

    void addCube(Cube& new_cube){
        for(auto c:cubes){
            if(c.adjacent(new_cube)){
                sides -= 2;
            }
        }
        cubes.push_back(new_cube);
        sides += 6;        
    }
};



Lava readInput()
{
    std::ifstream input("data/day18.txt");
    auto start = std::istream_iterator<int>(input);
    auto end = std::istream_iterator<int>();
    auto s = start;
    Lava lava;
    while(s!=end){
        int x = *s;
        s++;
        int y = *s;
        s++;
        int z = *s;
        s++;
        Cube cube = Cube(x,y,z);
        lava.addCube(cube);
    }
    return lava;
}

int main(int argc, char* argv[]){
    auto lava = readInput();
    std::cout << "ans1: " << lava.sides << std::endl;
}