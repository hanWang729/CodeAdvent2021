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

int MOD = 100;

int hash(int x, int y, int z){
    return x * MOD * MOD + y * MOD + z;
}

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
    int max_x;
    int max_y;
    int max_z;
    std::set<int> occupied_hash_set;
    std::set<int> lava_hash_set;

    Lava(){
        sides = 0;
        cubes.clear();
        max_x = 0;
        max_y = 0;
        max_z = 0;
    }

    void addCube(Cube& new_cube){
        for(auto c:cubes){
            if(c.adjacent(new_cube)){
                sides -= 2;
            }
        }
        cubes.push_back(new_cube);
        sides += 6;        
        occupied_hash_set.insert(hash(new_cube.x, new_cube.y, new_cube.z));
        lava_hash_set.insert(hash(new_cube.x, new_cube.y, new_cube.z));
        if(max_x < new_cube.x)
            max_x == new_cube.x;
        if(max_y < new_cube.y)
            max_y = new_cube.y;
        if(max_z < new_cube.z)
            max_z = new_cube.z;
    }

    void removeAir(){
        for(int x = 0; x <= max_x; x++){
            for(int y = 0; y <= max_y; y++){
                for(int z = 0; z <= max_z; z++){
                    if(occupied_hash_set.count(hash(x,y,z)) == 0){
                        if(isAir(x,y,z)){
                            int s = expandAir(x,y,z);
                            sides -= s;
                        }
                    }
                    
                }
            }
        }
    }

    bool isAir(int x, int y, int z){
        // int h = hash(x,y,z);
        int max_x, max_y, max_z;
        int min_x, min_y, min_z;
        for(auto i : lava_hash_set){
            
        }

    }

    int expandAir(int x, int y, int z){

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