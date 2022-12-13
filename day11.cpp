#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <cstring>
#include <set>
#include <sstream>

int divided_worry_level = 1;


enum Operation{
    Add,
    Multiple,
    Square,
};

struct Monkey
{
    int id;
    std::vector<long> items;
    Operation op;
    int op_num;
    int divided;
    int true_id;
    int false_id;
    int inspection;

    Monkey(std::string sid, std::string sitems, std::string sop, std::string sopnum,
            std::string sdivided, std::string strue_id,
            std::string sfalse_id){
        id = std::stoi(sid);
        std::istringstream ss(sitems);
        std::string item;
        size_t pos = sitems.find(",");
        while(pos != sitems.npos){
            item = sitems.substr(0,pos);
            items.push_back(std::stoi(item));
            sitems = sitems.substr(pos+1,sitems.size());
            pos = sitems.find(",");
        }
        if(sop == "x"){
            op = Square;
        }
        else if(sop == "0"){
            op = Add;
            op_num = std::stoi(sopnum);
        }
        else if(sop == "1"){
            op = Multiple;
            op_num = std::stoi(sopnum);
        }
        else{
            std::cout << "Input Error." << std::endl;
        }
        divided = std::stoi(sdivided);
        true_id = std::stoi(strue_id);
        false_id = std::stoi(sfalse_id);
        inspection = 0;
    }

    std::vector<int> inspect(){
        std::vector<int> returnValue;
        std::vector<long> newItems;
        for(long i : items){
            if(op == Square){
                i = i * i;
            }
            else if(op == Add){
                i += op_num;
            }
            else if(op == Multiple){
                i *= op_num;
            }
            i /= divided_worry_level;
            if(i % divided == 0){
                returnValue.push_back(true_id);
            }
            else{
                returnValue.push_back(false_id);
            }
            newItems.push_back(i);
        }
        inspection += returnValue.size();
        items = newItems;
        return returnValue;
    }

    void print(){
        std::cout << "Monkey: " << id << std::endl;
        std::cout << "  Starting items: ";
        for(auto i : items){
            std::cout << i << ", ";
        }
        std::cout << std::endl;
        std::cout << "  Operation: new = old ";
        if(op == Square)
            std::cout << "* old" << std::endl;
        else if(op == Add)
            std::cout << "+ " << op_num << std::endl;
        else if(op == Multiple)
            std::cout << "* " << op_num << std::endl;
        std::cout << "  Test: divisible by " << divided << std::endl;
        std::cout << "    If true: throw to monkey " << true_id << std::endl;
        std::cout << "    If false: throw to monkey " << false_id << std::endl;
    }

    void print_items(){
        std::cout << "Monkey " << id << ": ";
        for(auto i : items){
            std::cout << i << ", ";
        }
        std::cout << std::endl;
    }
    
};


std::vector<Monkey> readInput()
{
    std::ifstream input("data/day11.txt");
    auto start = std::istream_iterator<std::string>(input);
    auto end = std::istream_iterator<std::string>();
    std::vector<Monkey> Monkeys;
    auto s = start;
    while(s!=end){
        const std::string id = *s;
        s++;
        const std::string items = *s;
        s++;
        const std::string op = *s;
        s++;
        const std::string opnum = *s;
        s++;
        const std::string divided = *s;
        s++;
        const std::string true_id = *s;
        s++;
        const std::string false_id = *s;
        s++;
        Monkeys.push_back(Monkey(id,items,op,opnum,divided,true_id,false_id));
        
    }
    return Monkeys;
}

int main(int argc, char* argv[]) {
    auto monkeys = readInput();
    int common_value = 1;
    for(auto m : monkeys){
        common_value*= m.divided;
    }
    std::vector<int> tempVector;
    for(int i = 0; i < 10000; i++){
        for(int id = 0; id < monkeys.size(); id++){
            tempVector = monkeys[id].inspect();
            int v = 0;
            for(int nid: tempVector){
                monkeys[nid].items.push_back(monkeys[id].items[v] % common_value);
                v++;
            }
            monkeys[id].items.clear();
        }
        if(i == 20 || i % 1000 == 0){
            std::cout<< "After round " << i << std::endl;
            for(int id = 0; id < monkeys.size(); id++){
                monkeys[id].print_items();
            }
        }
    }

    for(auto m : monkeys){
        std::cout << "Monkey " << m.id << " inspects "
            << m.inspection << " times" << std::endl;
    }

}