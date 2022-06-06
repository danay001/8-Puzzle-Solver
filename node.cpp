#include <iostream>
#include <cmath>
#include "node.h"

Node::Node(){
    tiles[0][0] = '1';
    tiles[0][1] = '2';
    tiles[0][2] = '3';
    tiles[1][0] = '4';
    tiles[1][1] = '8';
    tiles[1][2] = '-';
    tiles[2][0] = '7';
    tiles[2][1] = '6';
    tiles[2][2] = '5';

    misplaced_num = find_misplaced();
    Manhattan_dist = find_man_dist();
}

Node::Node(char a, char b, char c, char d, char e, char f, char g, char h, char i){
    tiles[0][0] = a;
    tiles[0][1] = b;
    tiles[0][2] = c;
    tiles[1][0] = d;
    tiles[1][1] = e;
    tiles[1][2] = f;
    tiles[2][0] = g;
    tiles[2][1] = h;
    tiles[2][2] = i;

    misplaced_num = find_misplaced();
    Manhattan_dist = find_man_dist();
}

Node::Node(char tile[9]){
    tiles[0][0] = tile[0];
    tiles[0][1] = tile[1];
    tiles[0][2] = tile[2];
    tiles[1][0] = tile[3];
    tiles[1][1] = tile[4];
    tiles[1][2] = tile[5];
    tiles[2][0] = tile[6];
    tiles[2][1] = tile[7];
    tiles[2][2] = tile[8];

    misplaced_num = find_misplaced();
    Manhattan_dist = find_man_dist();
}

Node::~Node(){

}

bool Node::operator==(const Node &rhs) const{
    for(int i =0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(tiles[i][j] != rhs.tiles[i][j]){
                return false;
            }
        }
    }

    return true;
}

int Node::find_misplaced(){
    const char soln[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '-'}
    };

    int numMisplaced = 0;

    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(this->tiles[i][j] != soln[i][j]){
                ++numMisplaced;
            }
        }
    }

    return numMisplaced;
}

int Node::find_man_dist(){
    const char soln[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '-'}
    };

    int xPos[9] = {0, 1, 2, 0, 1, 2, 0, 1, 2};
    int yPos[9] = {0, 0, 0, 1, 1, 1, 2, 2, 2};

    int dist = 0;
    char tmp = 0;
    int val = 0;

    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(this->tiles[i][j] != soln[i][j]){
                tmp = tiles[i][j];
                if(tmp == '-'){
                    break;
                }
                val = tmp - '0' - 1;


                dist += abs(i - yPos[val]) + abs(j - xPos[val]);

            }
        }
    }

    return dist;
}

void Node::setCost(int g){
    this->cost = g;
}

int Node::getCost(){
    return this->cost;
}

void Node::print(){
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            std::cout << tiles[i][j] << ' '; 
        }
        std::cout << std::endl;
    }
    return;
}

void Node::set_tile(int row, int col, char tile){
    if(tile == '0'){
        tiles[row][col] = '-';
    }
    else{
        tiles[row][col] = tile;
    }
}

bool Node::is_solution(){
    int tmp[] = {1, 3, 5};
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(tiles[i][j] == '-' && i == 2 && j == 2){
                break;
            }
            if(tiles[i][j] != (i + j + tmp[i] + '0')){
                return false;
            }
        }
    }

    return true;
}

std::pair<int, int> Node::get_blank(){
    for(int i =0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(this->tiles[i][j] == '-'){
                return std::make_pair(i, j);
            }
        }
    }
    return std::make_pair(-1, -1);  //Error if this gets returned.
}

int Node::getManDist(){
    return Manhattan_dist;
}

int Node::getMisplacedNum(){
    return misplaced_num;
}


Node* Node::move_left(){
    std::pair<int, int> pos = this->get_blank();
    char tile_array [9];
    int k = 0;

    if(pos.second == 0){ //Invalid move
        return nullptr;
    }
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            tile_array[k] = this->tiles[i][j];
            ++k;
        }
    }

    Node* child_node = new Node(tile_array);

    char tmp = this->tiles[pos.first][pos.second - 1];

    child_node->set_tile(pos.first, pos.second, tmp);
    child_node->set_tile(pos.first, pos.second - 1, '-');

    return child_node;

}
Node* Node::move_right(){
    std::pair<int, int> pos = this->get_blank();
    char tile_array[9];
    int k = 0;

    if(pos.second == 2){ //Invalid move
        return nullptr;
    }
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            tile_array[k] = this->tiles[i][j];
            ++k;
        }
    }

    Node* child_node = new Node(tile_array);

    char tmp = this->tiles[pos.first][pos.second + 1];

    child_node->set_tile(pos.first, pos.second, tmp);
    child_node->set_tile(pos.first, pos.second + 1, '-');

   return child_node;

}
Node* Node::move_up(){
    std::pair<int, int> pos = this->get_blank();
    char tile_array[9];
    int k = 0;

    if(pos.first == 0){ //Invalid move
        return nullptr;
    }
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            tile_array[k] = this->tiles[i][j];
            ++k;
        }
    }

    Node* child_node = new Node(tile_array);

    char tmp = this->tiles[pos.first - 1][pos.second];

    child_node->set_tile(pos.first, pos.second, tmp);
    child_node->set_tile(pos.first - 1, pos.second, '-');

   return child_node;
}
Node* Node::move_down(){
    std::pair<int, int> pos = this->get_blank();
    char tile_array[9];
    int k = 0;

    if(pos.first == 2){ //Invalid move
        return nullptr;
    }
    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            tile_array[k] = this->tiles[i][j];
            ++k;
        }
    }

    Node* child_node = new Node(tile_array);

    char tmp = this->tiles[pos.first + 1][pos.second];

    child_node->set_tile(pos.first, pos.second, tmp);
    child_node->set_tile(pos.first + 1, pos.second, '-');

   return child_node;
}

bool Node::isEqual(const Node &node2){
    if(node2 == nullptr){
        return false;
    }

    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            if(tiles[i][j] != node2.tiles[i][j]){
                return false;
            }
        }
    }

    return true;
}

char Node::get_tile(int row, int col){
    return tiles[row][col];
}