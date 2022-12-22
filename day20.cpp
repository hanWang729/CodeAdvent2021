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

int MOD = 4999*4;

struct ListNode
{
    int val;
    ListNode *last;
    ListNode *next;
    int index;

    ListNode(){}
};


struct Cycle
{
    std::map<int, ListNode*> mydb;
    std::vector<int> inputVector;
    int length;

    Cycle(std::vector<int> const& input){
        inputVector = input;
        length = inputVector.size();
        for(int i = 0; i < inputVector.size(); i++){
            int v = inputVector[i];
            if(mydb.count(v)){
                while(mydb.count(v))
                    v += v / abs(v) * MOD;
                inputVector[i] = v;
            }
            ListNode *l = nullptr;
            l = new ListNode;
            l->val = v;
            l->next = nullptr;
            l->last = nullptr;
            mydb[v] = l;
        }
        for(int i = 0; i < inputVector.size() -1 ; i++){
            mydb[inputVector[i]]->next = mydb[inputVector[i+1]];
        }
        mydb[inputVector[inputVector.size()-1]]->next = mydb[inputVector[0]];
        for(auto i:inputVector){
            mydb[i]->next->last = mydb[i];
        }
    }

    void swap(int v1,int v2){
        if(v1 == v2)
            return;
        auto node = mydb[v1];
        delete_node(v1);
        insert_node(v2,node);
    }

    void delete_node(int v){
        mydb[v]->last->next = mydb[v]->next;
        mydb[v]->next->last = mydb[v]->last;
        mydb[v] = nullptr;
    }

    void insert_node(int v, ListNode* new_node){
        new_node->last = mydb[v];
        new_node->next = mydb[v]->next;
        mydb[v]->next->last = new_node;
        mydb[v]->next = new_node;
        mydb[new_node->val] = new_node;
    }

    int find_after(int start, int th){
        // th %= MOD;
        ListNode* head = mydb[start];
        if(th>0){
            for(int i = 0; i < th; i++){
                head = head->next;
            }
            return head->val;
        }
        else{
            for(int i = 0; i < -th; i++){
                head = head->last;
            }
            return head->last->val;
        }        
    }

    void print_test(){
        ListNode *head = mydb[0];
        std::cout << head->val << ", ";
        head = head->next;
        while(head->val != 0){
            std::cout << head->val << ", ";
            head = head->next;
        }
        std::cout << std::endl;
    }

    void print(){
        ListNode *head = mydb[0];
        std::cout << head->val << ", ";
        head = head->next;
        while(head->val != 0){
            std::cout << head->val << ", ";
            head = head->next;
        }
        std::cout << std::endl;
    }
    void print_back(){
        ListNode *head = mydb[0];
        std::cout << head->val << ", ";
        head = head->last;
        while(head->val != 0){
            std::cout << head->val << ", ";
            head = head->last;
        }
        std::cout << std::endl;
    }
    void start(){
        int c = 0;
        for(auto i : inputVector){
            // print();
            // std::cout << "i: " << i << std::endl;
            // move(i);
            // std::cout << "c: " << c++ << std::endl;
            int v1 = i;
            int v2 = find_after(v1,v1 % MOD);
            // std::cout << "v1: " << v1 << "v2: " << v2 << std::endl;
            swap(v1,v2);
        }
    }
};


std::vector<int> readInput(){
    std::ifstream input("data/day20.txt");
    auto start = std::istream_iterator<int>(input);
    auto end = std::istream_iterator<int>();
    auto s = start;
    std::vector<int> returnVector;
    while(s!=end){
        const int t = *s;
        s++;
        if(abs(t)>MOD)
            std::cout <<"Error"<<std::endl;
        returnVector.push_back(t);
    }
    return returnVector;
}

void part1(){
    auto inputVector = readInput();
    Cycle my_cycle = Cycle(inputVector);
    // my_cycle.print();
    my_cycle.start();
    // my_cycle.print();
    std::cout<<my_cycle.find_after(0,1000)<<std::endl;
    std::cout<<my_cycle.find_after(0,2000)<<std::endl;
    std::cout<<my_cycle.find_after(0,3000)<<std::endl;
    int ans = my_cycle.find_after(0,1000) % MOD + my_cycle.find_after(0,2000) % MOD + my_cycle.find_after(0,3000) % MOD;
    std::cout<<"ans: " << ans <<std::endl;
}

int main(int argc, char* argv[]){
    part1();
}