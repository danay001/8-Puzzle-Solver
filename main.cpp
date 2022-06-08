#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <functional>
#include "node.h"

struct NodeHash{
    size_t operator()(Node* const& n) const{
        return std::hash<std::string>()(n->get_key());
    }
};

struct NodeCompare{
    bool operator()(Node* const& n1, Node* const& n2) const{
        return *n1 == *n2;
    }
};

struct LeastCost{
    bool operator()(Node* lhs, Node* rhs) const{
        return lhs->getCost() > rhs->getCost();    }
};

struct LeastMismatch{
    bool operator()(Node* lhs, Node* rhs) const {
        int fn1 = lhs->getMisplacedNum() + lhs->getCost();
        int fn2 = rhs->getMisplacedNum() + rhs->getCost();
        return fn1 > fn2;
    }
};

struct LeastManDistance{
    bool operator()(Node* lhs, Node* rhs) const {
        int fn1 = lhs->getManDist() + lhs->getCost();
        int fn2 = rhs->getManDist() + rhs->getCost();
        return fn1 > fn2;
    }
};

Node* Uniform_Cost_Search(Node* puzzle){
    std::priority_queue<Node*, std::vector<Node*>, LeastCost> nodes;
    std::unordered_set<Node*, NodeHash, NodeCompare> seen_nodes;
    nodes.push(puzzle);
    Node* cur_node = puzzle;

    int g_n = 0;
    int h_n = 0;
    int totalNodes = 0;
    unsigned int maxQNodes = 0;

    if(nodes.empty()){
        return nullptr;
    }

    std::cout << "Expanding current node: " << std::endl;
    cur_node->print();

    //past_nodes.push_back(cur_node);
    seen_nodes.insert(cur_node);

    while(!nodes.empty()){
        cur_node = nodes.top();
        nodes.pop();

        g_n = cur_node->getCost(); 
        ++totalNodes;

        if(maxQNodes < nodes.size()){
            maxQNodes = nodes.size();
        }

        if(cur_node->is_solution()){
            std::cout << "Goal!!!" << std::endl;
            std::cout << "To solve this problem the search algorithm expanded a total of " << totalNodes << " nodes." << std::endl;
            std::cout << "The maximum number of nodes in the queue at any one time was " << maxQNodes << std::endl;
            std::cout << "The depth of the goal node was " << g_n << std::endl;
            return cur_node;
        }

        std::cout << "The best state to expand with a g(n) = " << g_n << " and h(n) = " << h_n << " is: \n";
        cur_node->print();
        std::cout << "Expanding this node \n \n";

        Node* child1 = cur_node->move_left();
        Node* child2 = cur_node->move_right();
        Node* child3 = cur_node->move_up();
        Node* child4 = cur_node->move_down();

        if(child1 != nullptr){
            if(seen_nodes.find(child1) == seen_nodes.end()){ //Only add unseen states to queue
                child1->setCost(g_n + 1);
                nodes.push(child1);
                seen_nodes.insert(child1);
            }
        }
        if(child2 != nullptr){
            if(seen_nodes.find(child2) == seen_nodes.end()){ //Only add unseen states to queue
                child2->setCost(g_n + 1);
                nodes.push(child2);
                seen_nodes.insert(child2);
            }
        }
        if(child3 != nullptr){
            if(seen_nodes.find(child3) == seen_nodes.end()){ //Only add unseen states to queue
                child3->setCost(g_n + 1);
                nodes.push(child3);
                seen_nodes.insert(child3);
            }
        }
        if(child4 != nullptr){
            if(seen_nodes.find(child4) == seen_nodes.end()){ //Only add unseen states to queue
                child4->setCost(g_n + 1);
                nodes.push(child4);
                seen_nodes.insert(child4);
            }
        }
    }
    return nullptr;
}

Node* A_Star_ManDist(Node* puzzle){
    std::priority_queue<Node*, std::vector<Node*>, LeastManDistance> nodes;
    //std::vector<Node*> past_nodes;
    std::unordered_set<Node*, NodeHash, NodeCompare> seen_nodes;
    nodes.push(puzzle);
    Node* cur_node = puzzle;
    int g_n = 0;
    int h_n = 0;
    int totalNodes = 0;
    unsigned int maxQNodes = 0;

    if(nodes.empty()){
        return nullptr;  
    }

    seen_nodes.insert(cur_node);

    std::cout << "Expanding state: " << std::endl;
    cur_node->print();

    while(!nodes.empty()){
        cur_node = nodes.top();
        g_n = cur_node->getCost(); 
        h_n = cur_node->getManDist();
        nodes.pop();
        ++totalNodes;   //Keeps track of total nodes expanded

        if(maxQNodes < nodes.size()){
            maxQNodes = nodes.size();
        }

        if(cur_node->is_solution()){
            std::cout << "Goal!!!" << std::endl;
            std::cout << "To solve this problem the search algorithm expanded a total of " << totalNodes << " nodes." << std::endl;
            std::cout << "The maximum number of nodes in the queue at any one time was " << maxQNodes << std::endl;
            std::cout << "The depth of the goal node was " << g_n << std::endl;
            
            return cur_node;
        }

        std::cout << "The best state to expand with a g(n) = " << g_n << " and h(n) = " << h_n << " is: " << std::endl;
        cur_node->print();
        std::cout << "Expanding this node" << std::endl << std::endl; 

        Node* child1 = cur_node->move_left();
        Node* child2 = cur_node->move_right();
        Node* child3 = cur_node->move_up();
        Node* child4 = cur_node->move_down();

        if(child1 != nullptr){
            if(seen_nodes.find(child1) == seen_nodes.end()){ //Only add unseen states to queue
                child1->setCost(g_n + 1);
                nodes.push(child1);
                seen_nodes.insert(child1);
            }
        }
        if(child2 != nullptr){
            if(seen_nodes.find(child2) == seen_nodes.end()){ //Only add unseen states to queue
                child2->setCost(g_n + 1);
                nodes.push(child2);
                seen_nodes.insert(child2);
            }
        }
        if(child3 != nullptr){
            if(seen_nodes.find(child3) == seen_nodes.end()){ //Only add unseen states to queue
                child3->setCost(g_n + 1);
                nodes.push(child3);
                seen_nodes.insert(child3);
            }
        }
        if(child4 != nullptr){
            if(seen_nodes.find(child4) == seen_nodes.end()){ //Only add unseen states to queue
                child4->setCost(g_n + 1);
                nodes.push(child4);
                seen_nodes.insert(child4);
            }
        }
    }
    return nullptr;
}

Node* A_Star_Misplaced(Node* puzzle){
    std::priority_queue<Node*, std::vector<Node*>, LeastMismatch> nodes;
    //std::vector<Node*> past_nodes;
    std::unordered_set<Node*, NodeHash, NodeCompare> seen_nodes;
    nodes.push(puzzle);
    Node* cur_node = puzzle;
    int g_n = 0;
    int h_n = 0;
    int totalNodes = 0;
    unsigned int maxQNodes = 0;

    if(nodes.empty()){
        return nullptr;  
    }
    seen_nodes.insert(cur_node);

    std::cout << "Expanding state: " << std::endl;
    cur_node->print();

    while(!nodes.empty()){
        cur_node = nodes.top();
        g_n = cur_node->getCost(); 
        h_n = cur_node->getMisplacedNum();
        nodes.pop();
        ++totalNodes;   //Keeps track of total nodes expanded

        if(maxQNodes < nodes.size()){
            maxQNodes = nodes.size();
        }

        if(cur_node->is_solution()){
            std::cout << "Goal!!!" << std::endl;
            std::cout << "To solve this problem the search algorithm expanded a total of " << totalNodes << " nodes." << std::endl;
            std::cout << "The maximum number of nodes in the queue at any one time was " << maxQNodes << std::endl;
            std::cout << "The depth of the goal node was " << g_n << std::endl;
            
            return cur_node;
        }

        std::cout << "The best state to expand with a g(n) = " << g_n << " and h(n) = " << h_n << " is: " << std::endl;
        cur_node->print();
        std::cout << "Expanding this node" << std::endl << std::endl; 

        Node* child1 = cur_node->move_left();
        Node* child2 = cur_node->move_right();
        Node* child3 = cur_node->move_up();
        Node* child4 = cur_node->move_down();

        if(child1 != nullptr){
            if(seen_nodes.find(child1) == seen_nodes.end()){ //Only add unseen states to queue
                child1->setCost(g_n + 1);
                nodes.push(child1);
                seen_nodes.insert(child1);
            }
        }
        if(child2 != nullptr){
            if(seen_nodes.find(child2) == seen_nodes.end()){ //Only add unseen states to queue
                child2->setCost(g_n + 1);
                nodes.push(child2);
                seen_nodes.insert(child2);
            }
        }
        if(child3 != nullptr){
            if(seen_nodes.find(child3) == seen_nodes.end()){ //Only add unseen states to queue
                child3->setCost(g_n + 1);
                nodes.push(child3);
                seen_nodes.insert(child3);
            }
        }
        if(child4 != nullptr){
            if(seen_nodes.find(child4) == seen_nodes.end()){ //Only add unseen states to queue
                child4->setCost(g_n + 1);
                nodes.push(child4);
                seen_nodes.insert(child4);
            }
        }
    }
    return nullptr;
}


void menu(){
    int choice = 0;
    int a, b, c = 0;  //Used to set tiles

    std::cout << "Type '1' to use a default puzzle, type '2' to enter your own puzzle." << std::endl;

    do{
        std::cin >> choice;
        if(!(choice == 1 || choice == 2)){
            std::cout << "Not a valid choice." << std::endl;
            std::cout << "Type '1' to use a default puzzle, type '2' to enter your own puzzle." << std::endl;
        }
    }while(!(choice == 1 || choice == 2));

    Node* init_state = new Node();

    if(choice == 2){
        std::cout << "Enter your puzzle, use a zero to represent the blank." << std::endl;
        std::cout << "Enter the first row. Use spaces between numbers." << std::endl;
        std::cin >> a >> b >> c;
        init_state->set_tile(0, 0, (a + '0')); // +'0' to convert int value to char
        init_state->set_tile(0, 1, (b + '0'));
        init_state->set_tile(0, 2, (c + '0'));

        std::cout << "Enter the second row. Use spaces between numbers." << std::endl;
        std::cin >> a >> b >> c;
        init_state->set_tile(1, 0, (a + '0'));
        init_state->set_tile(1, 1, (b + '0'));
        init_state->set_tile(1, 2, (c + '0'));

        std::cout << "Enter the third row. Use spaces between numbers." << std::endl; 
        std::cin >> a >> b >> c;
        init_state->set_tile(2, 0, (a + '0'));
        init_state->set_tile(2, 1, (b + '0'));
        init_state->set_tile(2, 2, (c + '0'));
    }

    std::cout << "Enter your choice of algorithm." << std::endl;
    std::cout << "  1. Uniform Cost Search" << std::endl;
    std::cout << "  2. A* with the Misplaced Tile heuristic." << std::endl;
    std::cout << "  3. A* with Manhattan Distance heuristic." << std::endl;

    do{
        std::cin >> choice;
        if(choice < 1 || choice > 3){
            std::cout << "Not a valid choice." << std::endl;
            std::cout << "Enter your choice of algorithm." << std::endl;
        }
    }while(choice < 1 || choice > 3);

    if(choice == 1){
        Node* soln = Uniform_Cost_Search(init_state);
        if(soln == nullptr){
            std::cout << "Unsolvable Puzzle\n";
        }
    }
    else if(choice == 2){
        Node* soln = A_Star_Misplaced(init_state);
        if(soln == nullptr){
            std::cout << "Unsolvable Puzzle\n";
        }
    }
    else if(choice == 3){
        Node* soln = A_Star_ManDist(init_state);
        if(soln == nullptr){
            std::cout << "Unsolvable Puzzle\n";
        }
    }

}

int main(){
    char command = ' ';

    std::cout << "Welcome to 8 Puzzle Solver" << std::endl;

    do{
        menu();
        std::cout << std::endl << "Press any key to input new puzzle. Type q to quit." << std::endl;
        std::cin >> command; 
    }while(command != 'q' && command != 'Q');

    std::cout << "Exiting Program" << std::endl;

    return 0;
}