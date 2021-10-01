// hdtcount.h
// A. Harrison Owen
// Started: 09/23/2021
// Finished: 09/30/2021
// Uses recursive calls to count
// how many variations of domino can cover board

#ifndef PROJECT5_HDTCOUNT_H
#define PROJECT5_HDTCOUNT_H
#include<vector> // std::vector

// function defined in .cpp
int hdtCount(int dim_x, int dim_y,
             int forbid1_x, int forbid1_y,
             int forbid2_x, int forbid2_y);

// function defined in .cpp
int hdtCount_recurse(std::vector<std::vector<int>> & board,
                     int dim_x, int dim_y, int squaresCovered);

#endif //PROJECT5_HDTCOUNT_H
