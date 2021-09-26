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
    if ((domino.getHead().first >= dim_x)
    || (domino.getHead().second >= dim_y)) {
        cout << "test2\n";
        return false;
    }
    //cout << "dom tail x: " << domino.getTail().first << " / x: " << dim_x << endl;

    if ((domino.getTail().first >= dim_x)
    || (domino.getTail().second >= dim_y)) {
        cout << "test2.0\n";
        return false;
    }


    // check for currently placed domino's
    else {
        cout << "test3\n";
        cout << board.size() << endl;
        for (auto i = 0; i < board.size() - 1; ++i) {
            cout << "test5\n";
            cout << "board i: {" << board[i].getHead().first << ", " << board[i].getHead().second << "} | {"
                 << board[i].getTail().first << ", " << board[i].getTail().second << "}\n";
            cout << "domino: {" << domino.getHead().first << ", " << domino.getHead().second << "} | {"
                 << domino.getTail().first << ", " << domino.getTail().second << "}\n";
            if ((domino.getHead() < board[i].getHead())||(domino.getHead() < board[i+1].getHead())){
                cout << "test failure\n";
                return false;
            }
            if ((domino.getHead() == board[i].getHead()) || (domino.getHead() == board[i].getTail())
            || (domino.getTail() == board[i].getHead()) || (domino.getTail() == board[i].getTail())) {
                cout << "test6\n";

                return false;
            }
            cout << "---------\nboard i: {" << board[i].getHead().first << ", " << board[i].getHead().second << "} | {"
                 << board[i].getTail().first << ", " << board[i].getTail().second << "}\n";
            cout << "domino: {" << domino.getHead().first << ", " << domino.getHead().second << "} | {"
                 << domino.getTail().first << ", " << domino.getTail().second << "}\n";
            cout << "board i+1: {" << board[i+1].getHead().first << ", " << board[i+1].getHead().second << "} | {"
                 << board[i+1].getTail().first << ", " << board[i+1].getTail().second << "}\n";

            if ((domino.getHead() == board[i+1].getHead()) || (domino.getHead() == board[i+1].getTail())
                || (domino.getTail() == board[i+1].getHead()) || (domino.getTail() == board[i+1].getTail())) {
                cout << "test7\n";

                return false;
            }
        }
    }


    if (board.back().getTail() == domino.getHead()
        || board.back().getTail() == domino.getTail()) {
        cout << "test9\n";
        return false;
    }
    cout << "test10\n";
    return true;
}

int hdtCount_recurse(vector<Domino> & board, int dim_x, int dim_y, pair<int,int> forbid1,
                         pair<int,int> forbid2, int & totalSquares, int coll1, int row1) {
    cout << "\nSTART size check: " << board.size() << endl;
    cout << "totalSquares: " << totalSquares <<"\n";


    pair<int, int> head;
    pair<int, int> tail;
    // BASE CASE
    if (totalSquares == 0) {
        for(auto i = 0; i < board.size(); ++i){
            cout << "board[" << i << "]: {" << board[i].getHead().first << ", " << board[i].getHead().second << "} | {"
                 << board[i].getTail().first << ", " << board[i].getTail().second << "}\n";}
        cout << "y*x: " << dim_x*dim_y << endl;
        cout << "NEXT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        //std::fill(board.begin()+2,board.end(),board[1]);
        //board.erase(board.begin()+2,board.end());
        for(auto i = 1; i < board.size(); ++i) {
            totalSquares = totalSquares + 2;
           //board.pop_back();
        }

        return 1;
    }

    // RECURSIVE CASE
    int total = 0;
    head = make_pair(row1, coll1);
    tail = make_pair(head.first+1, head.second);
    Domino dominoA(head, tail);
    tail = make_pair(head.first, head.second+1);
    Domino dominoB(head, tail);
    cout << "row x: " << row1 << ", col y: " << coll1 << endl;

    for (int col = coll1; col < dim_y; ++col) {
        for (int row = row1; row < dim_x; ++row) {
            cout << "row: " << row << ", col: " << col << endl;
            head.first = row;
            head.second = col;
            tail = make_pair(head.first + 1, head.second);
            Domino dominoA(head, tail);
            tail = make_pair(head.first, head.second + 1);
            Domino dominoB(head, tail);

            cout << dim_x << " " << dim_y << endl;
            cout << "bad coords: {" << forbid1.first << ", " << forbid1.second
                 << "} | {" << forbid2.first << ", " << forbid2.second << "}" << endl;
            cout << "domino A coords: {" << dominoA.getHead().first << ", " << dominoA.getHead().second
                 << "} | {" << dominoA.getTail().first << ", " << dominoA.getTail().second << "}" << endl;
           cout << "A\n";
            cout << "\n****size check: " << board.size() << endl;
            cout << "totalSquares: " << totalSquares <<"\n";

            for(auto i = 0; i < board.size(); ++i){
                cout << "board[" << i << "]: {" << board[i].getHead().first << ", " << board[i].getHead().second << "} | {"
                     << board[i].getTail().first << ", " << board[i].getTail().second << "}\n";}
            cout << "y*x: " << dim_x*dim_y << endl;
            if (checkDomino(board, dominoA, dim_x, dim_y)) {
               cout << "@@@@@@@@@@@@@@@@@ test A passed @@@@@@@@@@@\n";

                cout << dim_x << " " << dim_y << endl;
                cout << "test1\n";
                cout << dim_x << " " << dim_y << endl;
                cout << "bad coords: {" << forbid1.first << ", " << forbid1.second
                     << "} | {" << forbid2.first << ", " << forbid2.second << "}" << endl;
                cout << "domino A coords: {" << dominoA.getHead().first << ", " << dominoA.getHead().second
                     << "} | {" << dominoA.getTail().first << ", " << dominoA.getTail().second << "}" << endl;
                board.push_back(dominoA);
                auto temp = board;
                totalSquares = totalSquares - 2;
                cout << "NEST DEEPER A\n";

                total += hdtCount_recurse(temp, dim_x, dim_y, forbid1, forbid2,
                                          totalSquares, dominoA.getHead().second, dominoA.getHead().first+1);
                //board = temp;
                //board.erase(board.begin()+2,board.end());
                //board.pop_back();
            }
            cout << "\n****size check: " << board.size() << endl;
            cout << "totalSquares: " << totalSquares <<"\n";

            for(auto i = 0; i < board.size(); ++i){
                cout << "board[" << i << "]: {" << board[i].getHead().first << ", " << board[i].getHead().second << "} | {"
                     << board[i].getTail().first << ", " << board[i].getTail().second << "}\n";}
            cout << "y*x: " << dim_x*dim_y << endl;
            cout << dim_x << " " << dim_y << endl;
            cout << "\nbad coords: {" << forbid1.first << ", " << forbid1.second
                 << "} | {" << forbid2.first << ", " << forbid2.second << "}" << endl;
            cout << "domino B coords: {" << dominoB.getHead().first << ", " << dominoB.getHead().second
                 << "} | {" << dominoB.getTail().first << ", " << dominoB.getTail().second << "}" << endl;
            if (checkDomino(board, dominoB, dim_x, dim_y)) {
            cout << "@@@@@@@@@@@@@@@@@ test B passed @@@@@@@@@@@\n";

                cout << dim_x << " " << dim_y << endl;
                cout << "\npass bad coords: {" << forbid1.first << ", " << forbid1.second
                     << "} | {" << forbid2.first << ", " << forbid2.second << "}" << endl;
                cout << "domino B coords: {" << dominoB.getHead().first << ", " << dominoB.getHead().second
                     << "} | {" << dominoB.getTail().first << ", " << dominoB.getTail().second << "}" << endl;
                board.push_back(dominoB);
                auto tempB = board;
                totalSquares = totalSquares - 2;
                cout << "NEST DEEPER B\n";
                total += hdtCount_recurse(tempB, dim_x, dim_y, forbid1, forbid2,
                                          totalSquares,dominoB.getHead().second, dominoB.getHead().first+1);
                //board = tempB;
                //board.erase(board.begin()+1,board.end());
                //board.pop_back();
            }
        }
    }
    cout << "\nreturning the pi bayebyyyy\n";
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
