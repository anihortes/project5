// hdtcount.cpp
// A. Harrison Owen
// Started: 09/23/2021
// Finished: 09/30/2021
// Uses recursive calls to count
// how many variations of domino can cover board

#include "hdtcount.h"
#include <vector>
using std::vector;
#include <utility>
using std::pair;
using std::make_pair;
#include <iostream>
using std::cout;
using std::endl;

// checks if tile can be placed on the board
// int x and y are potential coordinates on the board that need to be checked
bool checkDomino(const vector<vector<int>> & board,
                 int x, int y){

    // check for out of bounds
    if(x >= board.size()){
        return false;
    }

    if(y >= board.back().size()){
        return false;
    }

    if(board[x][y] == 0) {
        return true;
    }

    return false;

}


// recursive function,
// counts how many combinations tiles can be placed on board
// dim_x and dim_y are the diminsions and size of board
// vector<vector<int>> board is 2D array representing a grid/tiles
// squaresCovered keeps track of how many tiles have be used for dominos
int hdtCount_recurse(vector<vector<int>> & board,
                     int dim_x, int dim_y, int squaresCovered) {
    int total = 0;

    // BASE CASE
    if(squaresCovered == dim_x*dim_y) {
        return 1;
    }

    // these check for squares that arent covered
    int emptyXCheck = 0;
    int emptyYCheck = 0;
    bool checkEmptySquares = false;

    //RECURSIVE CASE
    int x, y;
    for(y=0; y<dim_y;++y){
        for(x=0; x<dim_x; ++x){

            // checks if previous square is 0
            if(checkEmptySquares){
                if(board[emptyXCheck][emptyYCheck]==0){
                    return total;
                }
            }

            // check if current tile is empty
            if(board[x][y]==0) {
                // horizontal check, if yes, mark tiles as used and try next tiles with recurse
                if (checkDomino(board, x + 1, y)) {
                    board[x][y] = 1;
                    board[x + 1][y] = 1;
                    squaresCovered += 2;
                    total += hdtCount_recurse(board, dim_x, dim_y, squaresCovered);
                    // clean up board when done
                    squaresCovered -= 2;
                    board[x][y] = 0;
                    board[x + 1][y] = 0;
                }

                // vertical check, if yes, mark tiles as used and try next tiles with recurse
                if (checkDomino(board, x, y + 1)) {
                    board[x][y] = 1;
                    board[x][y + 1] = 1;
                    squaresCovered += 2;
                    total += hdtCount_recurse(board, dim_x, dim_y, squaresCovered);
                    // clean up board when done
                    squaresCovered -= 2;
                    board[x][y] = 0;
                    board[x][y + 1] = 0;
                }
            }

            // look at previous square, checks if its marked as used or not
            checkEmptySquares = true;
            emptyXCheck = x;
            emptyYCheck = y;
        }
    }
    return total;
};

// counts how many combinations of tiles can be placed on a grid
int hdtCount(int dim_x, int dim_y, int forbid1_x, int forbid1_y,
             int forbid2_x, int forbid2_y){
    // check for bad forbidden tiles
    if(forbid1_x < 0 || forbid1_x > dim_x || forbid1_y < 0 || forbid1_y > dim_y
       || forbid2_x < 0 || forbid2_x > dim_x || forbid2_y < 0 || forbid2_y > dim_y) {
        return 0;
    }

    // 2D array representing a grid
    vector<vector<int>> board(dim_x, vector<int>(dim_y,0));
    // mark the boards forbidden tiles as used
    board[forbid1_x][forbid1_y] = 1;
    board[forbid2_x][forbid2_y] = 1;
    // two tiles are covered by forbidden squares
    // so start with squaresCovered = 2
    int squaresCovered = 2;
    //cout << "dim_x: " << dim_x << " dim_y: " << dim_y << endl;
    return hdtCount_recurse(board, dim_x, dim_y, squaresCovered);
}
