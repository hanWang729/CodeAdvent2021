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

enum Operator{
    Add,
    Minus,
    Multi,
    Divide,
};

bool isNumber(const std::string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}


struct Monkey
{
    std::string name;
    bool has_value;
    int64_t value;
    std::string first_monkey;
    Operator op;
    std::string second_monkey;

    Monkey(){}
    Monkey(std::string const& n, int const& v){
        name = n;
        value = v;
        has_value = true;
    }
    Monkey(std::string const& n, std::string const& fm, std::string const& o, std::string const& sm){
        name = n;
        first_monkey = fm;
        if(o == "+")
            op = Add;
        else if(o == "-")
            op = Minus;
        else if(o == "*")
            op = Multi;
        else if(o == "/")
            op = Divide;
        second_monkey = sm;
        has_value = false;
    }

};

struct MonkeyGroup
{
    std::map<std::string,Monkey> MonkeyMap;
    MonkeyGroup(){}

    void addMonkey(Monkey m){
        MonkeyMap[m.name] = m;
    }

    int64_t look_up_ans(std::string const& monkey_name){
        int64_t ans;
        if(MonkeyMap[monkey_name].has_value)
            return MonkeyMap[monkey_name].value;
        else{
            int64_t ans1 = look_up_ans(MonkeyMap[monkey_name].first_monkey);
            int64_t ans2 = look_up_ans(MonkeyMap[monkey_name].second_monkey);
            switch (MonkeyMap[monkey_name].op){
                case Add:
                    ans = ans1 + ans2;
                    break;
                case Minus:
                    ans = ans1 - ans2;
                    break;
                case Multi:
                    ans = ans1 * ans2;
                    break;
                case Divide:
                    ans = ans1 / ans2;
                    if(ans1 % ans2 != 0)
                        std::cout << "Error" << std::endl;
                    break;
            }
            MonkeyMap[monkey_name].value = ans;
            MonkeyMap[monkey_name].has_value = true;
            return ans;
        }
    }

    void update_value(){
        for(auto m : MonkeyMap){
            if(!m.second.has_value){
                look_up_ans(m.first);
            }
        }
    }

    void print_monkey(){
        for(auto m : MonkeyMap){
            if(m.second.has_value){
                std::cout << m.first << ": " << m.second.value << std::endl;
            }
            else{
                std::cout << m.first << ": " << m.second.first_monkey << " " << m.second.op << " " << m.second.second_monkey << std::endl;
            }
        }
    }

};



MonkeyGroup readInput(){
    MonkeyGroup inputGroup;
    std::ifstream input("data/day21.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    auto s = start;
    while(s!=end){
        const std::string n1 = *s;
        s++;
        const std::string n2 = *s;
        s++;
        if(isNumber(n2)){
            inputGroup.addMonkey(Monkey(n1,std::stoi(n2)));
        }
        else{
            const std::string n3 = *s;
            s++;
            const std::string n4 = *s;
            s++;
            inputGroup.addMonkey(Monkey(n1,n2,n3,n4));
        }
    }
    return inputGroup;
}

void part1(){
    auto monkey_group = readInput();
    // monkey_group.print_monkey();
    monkey_group.update_value();
    // std::cout << "------new value----------" << std::endl;
    // monkey_group.print_monkey();
    std::cout << "ans1: " << monkey_group.MonkeyMap["root"].value << std::endl;
}

int main(int argc, char* argv[]){
    part1();

}