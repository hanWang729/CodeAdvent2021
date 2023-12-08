#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <array>
#include <utility>
#include <set>

struct Map{
    std::vector<long int> dest;
    std::vector<long int> source;
    std::vector<long int> range;

    Map(std::vector<long int> const& d, std::vector<long int> const& s, std::vector<long int> const& r){
        dest = d;
        source = s;
        range = r;
    }

    void print(){
        for(int i=0;i<dest.size();i++){
            std::cout << dest[i] << " " << source[i] << " " << range[i] << std::endl;
        }
    }

    long int translate(long int input){
        for(int i=0;i<dest.size();i++){
            if(input >= source[i] && input < source[i]+range[i]){
                return input - source[i] + dest[i];
                break;
            }
        }
        return input;
    }
    std::vector<std::pair<long int, long int>> translate2(std::pair<long int, long int> input){
        long int s = input.first;
        long int r = input.second;
        long int e = s + r - 1;
        std::pair<long int, long int> p;
        std::vector<std::pair<long int, long int>> returnValue;
        for(int i=0;i<dest.size();i++){
            // std::cout << "i: " << i << std::endl;
            if(s >= source[i] && s < source[i]+range[i]){
                if(e>source[i]&& e < source[i]+range[i]){
                    returnValue.push_back(std::make_pair(s - source[i] + dest[i],r));
                    return returnValue;
                }
                else{
                    long int ea = range[i] + source[i] - 1 - source[i] + dest[i];
                    long int sa = s - source[i] + dest[i];
                    long int ra = ea - sa + 1;
                    long int sn = range[i] + source[i];
                    long int rn = r - ra;
                    returnValue.push_back(std::make_pair(sa, ra));
                    auto rv = translate2(std::make_pair(sn, rn));
                    for(auto rv0 : rv){
                        returnValue.push_back(rv0);
                    }
                }
            }
        }
        if(returnValue.size() == 0)
            returnValue.push_back(input);
        return returnValue;
    }
};

struct Almanac{
    std::vector<long int> seeds;
    std::vector<Map> maps;
    std::vector<long int> loc; // for part 1
    std::vector<std::pair<long int, long int>> loc2; // for part 2

    Almanac(std::vector<long int> const& s, std::vector<Map> const& m){
        seeds = s;
        maps = m;
    }

    void calLoc(){
        long int i;
        for(auto s : seeds){
            i = s;
            for(auto m : maps){
                i = m.translate(i);
            }
            loc.push_back(i);
        }
    }

    void calLoc2(){
        for(int i = 0; i<seeds.size();i+=2){
            std::cout << i << std::endl;
            long int ss = seeds[i];
            long int r = seeds[i+1];
            std::vector<std::pair<long int, long int>> mid_input;
            std::vector<std::pair<long int, long int>> mid_output;
            std::vector<std::pair<long int, long int>> mid;
            mid_input.push_back(std::make_pair(ss,r));
            int testcount = 0;
            for(auto m : maps){
                // m.print();
                // std::cout << testcount << std::endl;
                for(auto mi:mid_input){
                    mid = m.translate2(mi);
                    mid_output.insert(mid_output.end(),mid.begin(),mid.end());
                }
                mid_input = mid_output;
                mid_output.clear();
                testcount++;
            }
            loc2.insert(loc2.end(),mid_input.begin(),mid_input.end());
        }
    }

    // void calLoc2(){
    //     long int mid;
    //     for(int i = 0; i<seeds.size();i+=2){
    //         long int ss = seeds[i];
    //         long int r = seeds[i+1];
    //         for(long int s = ss; s < ss+r; s++){
    //             mid = s;
    //             std::cout << mid << " ";
    //             for(auto m : maps){
    //                 mid = m.translate(mid);
    //             }
    //             std::cout << mid << std::endl;
    //             loc2.push_back(mid);
    //         }
    //     }
    // }

    void print(){
        for(auto s:seeds){
            std::cout << s << " ";
        }
        std::cout << std::endl;
        for(auto m:maps){
            m.print();
            std::cout << std::endl;
        }
    }
};

Almanac readInput(){
    std::vector<long int> seeds;
    std::vector<Map> maps;
    std::ifstream input("data/day5.txt");
    auto start = std::istream_iterator<long int>(input);
    auto end = std::istream_iterator<long int>();
    auto s = start;
    long int t = *s;
    while(t!=-1){
        seeds.push_back(t);
        s++;
        t = *s;
    }
    s++;
    t = *s;
    std::vector<long int> dest;
    std::vector<long int> source;
    std::vector<long int> range;
    while(s!=end){
        t = *s;
        while(t!=-1){
            dest.push_back(t);
            s++;
            t = *s;
            source.push_back(t);
            s++;
            t = *s;
            range.push_back(t);
            s++;
            t = *s;
        }
        s++;
        maps.push_back(Map(dest,source,range));
        dest.clear();
        source.clear();
        range.clear();
    }
    return Almanac(seeds, maps);
}

void part1(Almanac a){
    a.calLoc();
    long int l = a.loc[0];
    for(auto i : a.loc){
        if(i<l){
            l = i;
        }
    }
    std::cout << "ans1: " << l << std::endl;
}

void part2(Almanac a){
    a.calLoc2();
    long int l = a.loc2[0].first;
    for(auto i : a.loc2){
        // std::cout << i.first << std::endl;
        if(i.first<l && i.first!=0){
            l = i.first;
        }
    }
    std::cout << "ans2: " << l << std::endl;
}

void test(Almanac a){
    long int t = 82;
    long int i = t;
    std::cout << i << std::endl;
    for(auto m : a.maps){
        m.print();
        i = m.translate(i);
        std::cout << i << std::endl;
    }
}

int main(int argc, char * argv[]){
    auto input = readInput();
    // input.print();
    // part1(input);
    part2(input);
    // test(input);
}