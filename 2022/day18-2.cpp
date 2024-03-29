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
    std::set<int> lava_hash_set;
    std::set<int> air_hash_set;

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
        lava_hash_set.insert(hash(new_cube.x, new_cube.y, new_cube.z));
        if(max_x < new_cube.x)
            max_x = new_cube.x;
        if(max_y < new_cube.y)
            max_y = new_cube.y;
        if(max_z < new_cube.z)
            max_z = new_cube.z;
    }

    void findAir(){
        for(int x = 0; x <= max_x + 1; x++){
            for(int y = 0; y <= max_y + 1; y++){
                for(int z = 0; z <= max_z + 1; z++){
                    if(lava_hash_set.count(hash(x,y,z)) == 0)
                        air_hash_set.insert(hash(x,y,z));
                }
            }
        }
    }

    void removeAir(int x, int y, int z){
        if(air_hash_set.count(hash(x+1,y,z)))
            removeAir(x+1,y,z);
        if(air_hash_set.count(hash(x,y+1,z)))
            removeAir(x,y+1,z);
        if(air_hash_set.count(hash(x,y,z+1)))
            removeAir(x,y,z+1);
        if(air_hash_set.count(hash(x,y,z)))
            air_hash_set.erase(hash(x,y,z));
        if(air_hash_set.count(hash(x-1,y,z)))
            removeAir(x-1,y,z);
        if(air_hash_set.count(hash(x,y-1,z)))
            removeAir(x,y-1,z);
        if(air_hash_set.count(hash(x,y,z-1)))
            removeAir(x,y,z-1);
        
    }

    void removeAir_helper(){
        std::set<int> tmp_hash_set;
        removeAir(0,0,0);
    }

    void print_max(){
        std::cout<< "x_max: " << max_x << std::endl;
        std::cout<< "y_max: " << max_y << std::endl;
        std::cout<< "z_max: " << max_z << std::endl;
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
    lava.findAir();
    lava.removeAir_helper();
    Lava airLava;
    for(auto ahs : lava.air_hash_set){
        int x = ahs / (MOD * MOD);
        int y = (ahs - x * MOD * MOD) / MOD;
        int z = ahs % (MOD);
        Cube cube = Cube(x,y,z);
        airLava.addCube(cube);
    }
    std::cout << "ans2: " << lava.sides - airLava.sides << std::endl;
}