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
    //cout <<"BOOL CHECK\n";
    // error handle check
    if(board.empty()) {
        //cout << "test1\n";
        return false;
    }
    // test for out of bounds
     //cout << "dom head x: " << domino.getHead().first << " / x: " << dim_x << endl;
    if ((domino.getHead().first >= dim_x)
        || (domino.getHead().second >= dim_y)) {
        //cout << "test2\n";
        return false;
    }
    //cout << "dom tail x: " << domino.getTail().first << " / x: " << dim_x << endl;
    if ((domino.getTail().first >= dim_x)
        || (domino.getTail().second >= dim_y)) {
        //cout << "test2.0\n";
        return false;
    }
        // check for currently placed domino's
    else {
        //cout << "test3\n";
        //cout << board.size() << endl;
        for (auto i = 0; i < board.size() - 1; ++i) {
/*              cout << "test5\n";
            cout << "---------\nboard i: {" << board[i].getHead().first << ", " << board[i].getHead().second << "} | {"
                 << board[i].getTail().first << ", " << board[i].getTail().second << "}\n";
            cout << "domino: {" << domino.getHead().first << ", " << domino.getHead().second << "} | {"
                 << domino.getTail().first << ", " << domino.getTail().second << "}\n";
            cout << "board i+1: {" << board[i+1].getHead().first << ", " << board[i+1].getHead().second << "} | {"
                 << board[i+1].getTail().first << ", " << board[i+1].getTail().second << "}\n";*/
            /*if(i > 1) {
                if (((domino.getHead() < board[i].getHead()) && (domino.getTail() < board[i].getTail()))
                    || ((domino.getHead() < board[i+1].getHead()) && (domino.getTail() < board[i + 1].getTail()))){
                    cout << "test failure\n";
                    return false;
                }
            }*/
            if ((domino.getHead() == board[i].getHead()) || (domino.getHead() == board[i].getTail())
                || (domino.getTail() == board[i].getHead()) || (domino.getTail() == board[i].getTail())) {
                //cout << "test6\n";
                return false;
            }
/*            cout << "---------\nboard i: {" << board[i].getHead().first << ", " << board[i].getHead().second << "} | {"
                 << board[i].getTail().first << ", " << board[i].getTail().second << "}\n";
            cout << "domino: {" << domino.getHead().first << ", " << domino.getHead().second << "} | {"
                 << domino.getTail().first << ", " << domino.getTail().second << "}\n";
            cout << "board i+1: {" << board[i+1].getHead().first << ", " << board[i+1].getHead().second << "} | {"
                 << board[i+1].getTail().first << ", " << board[i+1].getTail().second << "}\n";*/
            if ((domino.getHead() == board[i+1].getHead()) || (domino.getHead() == board[i+1].getTail())
                || (domino.getTail() == board[i+1].getHead()) || (domino.getTail() == board[i+1].getTail())) {
                 //cout << "test7\n";
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

int hdtCount_recurse(vector<Domino> board, int dim_x, int dim_y, int coll1, int roww) {
    //cout << "x: " << dim_x << " | y: " << dim_y << endl;
    int row1 = roww;
    //cout << "yo new recurse\n";
    pair<int, int> head;
    pair<int, int> tail;

    // BASE CASE
    if (dim_y*dim_x == 2*board.size() - 2) {
/*        for (auto i = 0; i < board.size(); ++i) {
            cout << "board i: {" << board[i].getHead().first << ", " << board[i].getHead().second << "} | {"
                 << board[i].getTail().first << ", " << board[i].getTail().second << "}\n";}
        cout << "---------------------------------------NICE----------------------------------\n";*/
        return 1;
    }

    // RECURSIVE CASE
    int total = 0;
    Domino dominoA;
    Domino dominoB;

    bool xCheck = true;
    int row;
    int col;
    for(col = coll1; col < dim_y;++col) {
        for (row = row1; row < dim_x; ++row) {
            if(col > 1 && dim_x ==1){
                pair<int,int> test = make_pair(row,col-1);
                int count = 0;
                for(auto i = 0; i < board.size();++i){
                    if(test == board[i].getHead() || test == board[i].getTail())
                        count++;
                }
                if(count == 0 )
                    return total;
            }
            else if (row > 1 && dim_y ==1){
                pair<int,int> test = make_pair(row-2,col);
                int count = 0;
                for(auto i = 0; i < board.size();++i){
                    if(test == board[i].getHead() || test == board[i].getTail())
                        count++;
                }
                if(count == 0 )
                    return total;
            }
            //cout << "x = " << row << " and y = " << col << endl;

            head.first = row;
            head.second = col;
            tail = make_pair(head.first + 1, head.second);
            dominoA.setHead(head);
            dominoA.setTail(tail);
            tail = make_pair(head.first, head.second + 1);
            dominoB.setHead(head);
            dominoB.setTail(tail);
/*            for (auto i = 0; i < board.size(); ++i) {
                cout << "board i: {" << board[i].getHead().first << ", " << board[i].getHead().second << "} | {"
                     << board[i].getTail().first << ", " << board[i].getTail().second << "}\n";}
            cout << "dominoA: {" << dominoA.getHead().first << ", " << dominoA.getHead().second << "} | {"
                 << dominoA.getTail().first << ", " << dominoA.getTail().second << "}\n----------------\n";*/
            if (checkDomino(board, dominoA, dim_x, dim_y)) {
                //cout << "!!!!!!!!!! DOM A MADE IT !!!!!!!!!!\n";
                board.push_back(dominoA);
                total += hdtCount_recurse(board, dim_x, dim_y,
                                          dominoA.getHead().second, dominoA.getHead().first);
/*                for (auto i = 0; i < board.size(); ++i) {
                    cout << "board i: {" << board[i].getHead().first << ", " << board[i].getHead().second << "} | {"
                         << board[i].getTail().first << ", " << board[i].getTail().second << "}\n";}*/
                board.pop_back();
                //cout << " ````````````````` popping back `````````````````````````\n";
            }
/*            for (auto i = 0; i < board.size(); ++i) {
                cout << "board i: {" << board[i].getHead().first << ", " << board[i].getHead().second << "} | {"
                     << board[i].getTail().first << ", " << board[i].getTail().second << "}\n";}
            cout << "dominoB: {" << dominoB.getHead().first << ", " << dominoB.getHead().second << "} | {"
                 << dominoB.getTail().first << ", " << dominoB.getTail().second << "}\n";*/
            if (checkDomino(board, dominoB, dim_x, dim_y)) {
                //cout << "!!!!!!!!!! DOM B MADE IT !!!!!!!!!!\n";
                board.push_back(dominoB);
                total += hdtCount_recurse(board, dim_x, dim_y,
                                          dominoB.getHead().second, dominoB.getHead().first);
 /*               cout << "total: " << total << endl;
                for (auto i = 0; i < board.size(); ++i) {
                    cout << "board i: {" << board[i].getHead().first << ", " << board[i].getHead().second << "} | {"
                         << board[i].getTail().first << ", " << board[i].getTail().second << "}\n";}
                cout << " ````````````````` popping back `````````````````````````\n";*/
                board.pop_back();
            }
            //cout << "reminder that: x = " << row << " and y = " << col << endl;

        }
        //cout << "row: " << row << " : dim_x: " << dim_x << endl;
        if(xCheck && (row==dim_x) && (row1 > 0)){
            //cout << "fat check\n";
            xCheck = false;
            row1 = 0;

        }
    }
    //cout << "returning total: " << total << endl;
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
    cout << "x: " << dim_x << " y: " << dim_y<<endl;
    return hdtCount_recurse(board, dim_x, dim_y, 0 ,0);
}
