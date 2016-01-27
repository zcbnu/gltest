//
//  Voronoi.hpp
//  gltest
//
//  Created by 黄保应 on 16/1/27.
//  Copyright © 2016年 黄保应. All rights reserved.
//

#ifndef Voronoi_hpp
#define Voronoi_hpp

#include <stdio.h>
#include <vector>

template<typename T>
class Point
{
public:
    T x;
    T y;
    Point(T x_ = 0, T y_ = 0):x(x_),y(y_) {}
};

template<typename T>
class HalfEdge{
public:
    bool onEdge(const Point<T>& point) const
    {
        
    }
private:
    Point<T> _p;
    float _k;
    int _nV;
};

class BTree;
struct BTreeNode{
    BTreeNode* _l;
    BTreeNode* _r;
    BTreeNode* _p;
    BTreeNode* _n;
    friend class BTree;
} BTreeNode;

class BTree{
    
};

#endif /* Voronoi_hpp */
