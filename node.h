#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>

class Node{         
private:
    char tiles[3][3];
    int misplaced_num;
    int Manhattan_dist;
    int cost; //cost to get to node. g(n)
    std::string key;
    void set_key();
public:
    Node();
    Node(char, char, char, char, char, char, char, char, char);
    Node(char tile[9]);
    ~Node();
    void print();
    void set_tile(int, int, char);
    char get_tile(int, int);
    bool is_solution(); 
    int find_misplaced();
    int find_man_dist();
    void setCost(int);
    int getManDist();
    int getMisplacedNum();
    int getCost();
    bool isEqual(const Node &);
    bool operator==(const Node &rhs) const;
    std::pair<int, int> get_blank();
    std::string get_key();
    //Operators. Moves blank and creates child node.
    Node* move_left();
    Node* move_right();
    Node* move_up();
    Node* move_down();

};

#endif