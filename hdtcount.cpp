//
// Created by A. Harrison Owen on 9/23/2021.
//
#include "hdtcount.h"
#include <vector>
using std::vector;
#include <utility>
using std::pair;
using std::make_pair;


bool checkDomino(const vector<Domino> & board,
                 const Domino & domino, int collum,
                 pair<int,int> forbid1,pair<int,int> forbid2){

    if(domino.getHead() == forbid1 || domino.getHead() == forbid2
    || domino.getTail() == forbid1 || domino.getTail() == forbid2)
        return false;
    else if(board.empty()){
        return true;
    }
    for (auto i = 0; i < board.size()-1; ++i){
        if(board[i].getTail() == domino.getHead()
        ||board[i+1].getTail() == domino.getTail())
            return false;
    }
    if(board[board.size()].getTail() == domino.getHead()
       ||board[board.size()].getTail() == domino.getTail())
        return false;
    return true;
}

int recursiveDominoCount(const vector<Domino> & board, int dim_x, int dim_y, int forbid1_x, int forbid1_y,
                         int forbid2_x, int forbid2_y) {

    int count = 0;
    // BASE CASE
    if (dim_x == board.size() || dim_y == board.size())
        return 1;
    // RECURSIVE CASE
    int total = 0;
    auto forbid1 = make_pair(forbid1_x,forbid1_y);
    auto forbid2 = make_pair(forbid2_x,forbid2_y);
    Domino domino;
    for(int collum = 0; collum < dim_x; ++collum){
        if(checkDomino(board, domino, collum, forbid1, forbid2)){
            return total++;
        }
    }
    return total;
};

int hdtCount(int dim_x, int dim_y,
             int forbid1_x, int forbid1_y,
             int forbid2_x, int forbid2_y){
    vector<Domino> board;
    return recursiveDominoCount(board, dim_x, dim_y, forbid1_x, forbid1_y, forbid2_x, forbid2_y);
}
