//
// Created by A. Harrison Owen on 9/23/2021.
//
#include "hdtcount.h"
#include <vector>
using std::vector;
#include <utility>
using std::pair;
using std::make_pair;
#include <iostream>
using std::cout;
using std::endl;


bool checkDomino(const vector<Domino> & board,
                 const Domino & domino,
                 int dim_x, int dim_y){

    // error handle check
    if(board.empty()) {
        //cout << "test1\n";
        return false;
    }

    // test for out of bounds
    // cout << "dom head x: " << domino.getHead().first << " / x: " << dim_x << endl;
    if ((domino.getHead().first > dim_x-1)
        || (domino.getHead().second > dim_y-1)) {
        //cout << "test2\n";
        return false;
    }
    //cout << "dom tail x: " << domino.getTail().first << " / x: " << dim_x << endl;

    if ((domino.getTail().first > dim_x-1)
        || (domino.getTail().second > dim_y-1)) {
        //cout << "test2.0\n";
        return false;
    }


        // check for currently placed domino's
    else {
        //cout << "test3\n";
        //cout << board.size() << endl;
        for (auto i = 0; i < board.size() - 1; ++i) {

            if ((domino.getHead() == board[i].getHead()) || (domino.getHead() == board[i].getTail())
                || (domino.getTail() == board[i].getHead()) || (domino.getTail() == board[i].getTail())) {
                //cout << "test6\n";

                return false;
            }

            if ((domino.getHead() == board[i+1].getHead()) || (domino.getHead() == board[i+1].getTail())
                || (domino.getTail() == board[i+1].getHead()) || (domino.getTail() == board[i+1].getTail())) {
                // cout << "test7\n";

                return false;
            }
        }
    }


    if (board.back().getTail() == domino.getHead()
        || board.back().getTail() == domino.getTail()) {
        //cout << "test9\n";
        return false;
    }
    //cout << "test10\n";
    return true;
}

int hdtCount_recurse(vector<Domino> & board, int dim_x, int dim_y, pair<int,int> forbid1,
                     pair<int,int> forbid2, int & totalSquares, int coll1, int row1) {
    pair<int, int> head;
    pair<int, int> tail;
    // BASE CASE
    if (totalSquares == 0) {
        // reset number of tiles to count
        for(auto i = 1; i < board.size(); ++i) {
            totalSquares = totalSquares + 2;
        }
        return 1;
    }

    // RECURSIVE CASE
    int total = 0;
    head = make_pair(row1, coll1);
    tail = make_pair(head.first + 1, head.second);
    Domino dominoA(head, tail);
    Domino dominoB(head, tail);
    for (int col = coll1; col < dim_y; ++col) {
        for (int row = row1; row < dim_x; ++row) {
            for(auto i = 0; i < board.size(); ++i) {
                head.first = row;
                head.second = col;
                tail = make_pair(head.first + 1, head.second);
                dominoA.setHead(head);
                dominoA.setTail(tail);
                tail = make_pair(head.first, head.second + 1);
                dominoB.setHead(head);
                dominoB.setTail(tail);

                if (checkDomino(board, dominoA, dim_x, dim_y)) {
                    board.push_back(dominoA);
                    //auto temp = board;
                    totalSquares = totalSquares - 2;
                    total += hdtCount_recurse(board, dim_x, dim_y, forbid1, forbid2,
                                              totalSquares, dominoA.getHead().second, dominoA.getHead().first);
                    board.pop_back();
                }
                
                if (checkDomino(board, dominoB, dim_x, dim_y)) {
                    board.push_back(dominoB);
                    // auto tempB = board;
                    totalSquares = totalSquares - 2;
                    total += hdtCount_recurse(board, dim_x, dim_y, forbid1, forbid2,
                                              totalSquares, dominoB.getHead().second, dominoB.getHead().first);
                    board.pop_back();
                }
            }
        }
    }
    return total;
};

int hdtCount(int dim_x, int dim_y,
             int forbid1_x, int forbid1_y,
             int forbid2_x, int forbid2_y){
    if(forbid1_x < 0 || forbid1_x > dim_x || forbid1_y < 0 || forbid1_y > dim_y
       || forbid2_x < 0 || forbid2_x > dim_x || forbid2_y < 0 || forbid2_y > dim_y)
        return 0;
    vector<Domino> board;
    auto forbid1 = make_pair(forbid1_x,forbid1_y);
    auto forbid2 = make_pair(forbid2_x,forbid2_y);
    Domino forbidden1(forbid1,forbid2);
    Domino forbidden2(forbid1,forbid2);
    board.push_back(forbidden1);
    board.push_back(forbidden2);
    int totalSquares = (dim_x*dim_y)-2;
    return hdtCount_recurse(board, dim_x, dim_y, forbid1, forbid2, totalSquares, 0 ,0);
}
