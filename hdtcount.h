//
// Created by A. Harrison Owen on 9/23/2021.
//

#ifndef PROJECT5_HDTCOUNT_H
#define PROJECT5_HDTCOUNT_H

class Board{
public:
    Board(): _dim_x(0), _dim_y(0){};

    Board(int dim_x, int dim_y) : _dim_x(dim_x), _dim_y(dim_y){};

    int getX(){
        return _dim_x;
    }

    int getY(){
        return _dim_y;
    }

private:
    int _dim_x;
    int _dim_y;
};

#endif //PROJECT5_HDTCOUNT_H
