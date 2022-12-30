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


struct ListNode
{
    int val;
    ListNode *last;
    ListNode *next;
    int index;
    ListNode *initial_next;
    ListNode *initial_last;

    ListNode(){}
};


struct Cycle
{
    std::map<int, ListNode*> mydb;
    int length;

    Cycle(std::vector<int> const& input){
        length = input.size();
        for(int i = 0; i < input.size(); i++){
            int v = input[i];
            ListNode *l = nullptr;
            l = new ListNode;
            l->val = v;
            l->index = i;
            l->initial_next = nullptr;
            l->initial_last = nullptr;
            l->next = nullptr;
            l->last = nullptr;
            mydb[i] = l;
        }
        for(int i = 0; i < input.size() - 1 ; i++){
            mydb[i]->next = mydb[i+1];
        }
        mydb[input.size()-1]->next = mydb[0];
        for(int i = 0; i < input.size(); i++){
            mydb[i]->next->last = mydb[i];
        }
        for(int i = 0; i < input.size(); i++){
            mydb[i]->initial_next = mydb[i]->next;
            mydb[i]->initial_last = mydb[i]->last;
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
        mydb[new_node->index] = new_node;
    }

    int find_after(int start, int th, int op){
        // if(op==0)
        //     th = th % (length);
        if(op==1)
            th = th % (length - 1);
        ListNode* head = mydb[start];
        if(th>0){
            for(int i = 0; i < th; i++){
                head = head->next;
            }
            return head->index;
        }
        else{
            for(int i = 0; i < -th; i++){
                head = head->last;
            }
            return head->last->index;
        }        
    }

    void print(){
        ListNode *head = mydb[0];
        std::cout << head->val << ", ";
        head = head->next;
        while(head->index != 0){
            std::cout << head->val << ", ";
            head = head->next;
        }
        std::cout << std::endl;
    }
    void print_back(){
        ListNode *head = mydb[0];
        std::cout << head->val << ", ";
        head = head->last;
        while(head->index != 0){
            std::cout << head->val << ", ";
            head = head->last;
        }
        std::cout << std::endl;
    }
    void print_inital(){
        ListNode *head = mydb[0];
        std::cout << head->val << ", ";
        head = head->initial_next;
        while(head->index != 0){
            std::cout << head->val << ", ";
            head = head->initial_next;
        }
        std::cout << std::endl;
    }
    void print_intial_back(){
        ListNode *head = mydb[0];
        std::cout << head->val << ", ";
        head = head->initial_last;
        while(head->index != 0){
            std::cout << head->val << ", ";
            head = head->initial_last;
        }
        std::cout << std::endl;
    }

    int index_of_zero(){
        for(int i = 0; i < length; i++){
            if(mydb[i]->val == 0)
                return mydb[i]->index;
        }
        return -1;
    }

    void start(){
        int c = 0;
        for(int i=0;i<length;i++){
            // std::cout << "i: " << i << std::endl;
            int v1 = i;
            int v2 = find_after(v1,mydb[i]->val,1);
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
    int zero_index = my_cycle.index_of_zero();
    int i1 = my_cycle.find_after(zero_index,1000,0);
    int i2 = my_cycle.find_after(zero_index,2000,0);
    int i3 = my_cycle.find_after(zero_index,3000,0);
    std::cout<<my_cycle.mydb[i1]->val<<std::endl;
    std::cout<<my_cycle.mydb[i2]->val<<std::endl;
    std::cout<<my_cycle.mydb[i3]->val<<std::endl;
    int ans = my_cycle.mydb[i1]->val + my_cycle.mydb[i2]->val + my_cycle.mydb[i3]->val;
    std::cout<<"ans: " << ans <<std::endl;
}

int main(int argc, char* argv[]){
    part1();
}