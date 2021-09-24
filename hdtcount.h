//
// Created by A. Harrison Owen on 9/23/2021.
//

#ifndef PROJECT5_HDTCOUNT_H
#define PROJECT5_HDTCOUNT_H

int hdtCount(int dim_x, int dim_y,
             int forbid1_x, int forbid1_y,
             int forbid2_x, int forbid2_y);

#include <utility> // std::pair, std::make_pair
class Domino{
public:
    Domino(): _head(0,0), _tail(0,1){};

    Domino(std::pair<int,int> & head, std::pair<int,int> & tail)
            : _head(head), _tail(tail){};

    Domino(int headX, int headY, int tailX, int tailY)
            : _head(headX, headY), _tail(tailX,tailY){};

    std::pair<int,int> setHead(std::pair<int,int> head) {
        _head.first = head.first;
        _head.second = head.second;
    }

    std::pair<int,int> setTail(std::pair<int,int> tail) {
        _tail.first = _tail.first;
        _tail.second = _tail.second;
    }

    [[nodiscard]] std::pair<int,int> getHead() const{
        return _head;
    }

    [[nodiscard]] std::pair<int,int> getTail() const{
        return _tail;
    }

private:
    std::pair<int,int> _head;
    std::pair<int,int> _tail;

};

#endif //PROJECT5_HDTCOUNT_H
