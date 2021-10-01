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


bool checkDomino(const vector<vector<int>> & board,
                 int x1, int y1){

    if(x1 >= board.size()){
        return false;
    }
    if(y1 >= board[0].size()){
        return false;
    }

    if(board[x1][y1] == 0) {
        return true;
    }

    return false;

}

int hdtCount_recurse(vector<vector<int>> board, int dim_x, int dim_y, int & count) {
    int total = 0;
    //count -= 2;

    // BASE CASES
    if(count == 0) {
        return 1;
    }

    if(dim_x*dim_y == 2){
        return 1;
    }

    int emptyXCheck = 0;
    int emptyYCheck = 0;
    bool checkEmptySqaures = true;
    //RECURSIVE CASE
    int x, y;
    for(y=0; y<dim_y;++y){
        for(x=0; x<dim_x; ++x){
            // checks if previous square is 0
            if(checkEmptySqaures){
                if(board[emptyXCheck][emptyYCheck]==0){
                    return 0;
                }
            }

            if(board[x][y]==0) {
                if (checkDomino(board, x + 1, y)) {
                    board[x][y] = 1;
                    board[x + 1][y] = 1;
                    count -= 2;
                    total += hdtCount_recurse(board, dim_x, dim_y, count);
                    count += 2;
                    board[x][y] = 0;
                    board[x + 1][y] = 0;
                }

                if (checkDomino(board, x, y + 1)) {
                    board[x][y] = 1;
                    board[x][y + 1] = 1;
                    count -= 2;
                    total += hdtCount_recurse(board, dim_x, dim_y, count);
                    count += 2;
                    board[x][y] = 0;
                    board[x][y + 1] = 0;
                }
            }
            // look at previous square
            checkEmptySqaures = false;
            emptyXCheck = x;
            emptyYCheck = y;
        }
    }
    return total;
};

int hdtCount(int dim_x, int dim_y, int forbid1_x, int forbid1_y,
             int forbid2_x, int forbid2_y){

    if(forbid1_x < 0 || forbid1_x > dim_x || forbid1_y < 0 || forbid1_y > dim_y
       || forbid2_x < 0 || forbid2_x > dim_x || forbid2_y < 0 || forbid2_y > dim_y)
        return 0;

    vector<vector<int>> board(dim_x, vector<int>(dim_y,0));

    board[forbid1_x][forbid1_y] = 1;
    board[forbid2_x][forbid2_y] = 1;
    int count = dim_x*dim_y-2;
    //cout << "dim_x: " << dim_x << " dim_y: " << dim_y << endl;
    return hdtCount_recurse(board, dim_x, dim_y, count);
}
