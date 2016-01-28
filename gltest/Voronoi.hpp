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
#include <list>
#include <iterator>

template<typename T>
class Point
{
public:
    T x;
    T y;
    Point(T x_ = 0, T y_ = 0):x(x_),y(y_) {}
    Point(const Point& p): x(p.x),y(p.y) {}
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

struct BTreeNode{
    static const int CHILD_NUM = 2;
    BTreeNode* _c[CHILD_NUM];
    BTreeNode* _p;
    BTreeNode* _n;
};

template<typename T>
class Leaf : public BTreeNode
{
public:
    Point<T> point;
    Leaf(const Leaf& leaf) : point(leaf.point) {}
};

template <class T>
class Branch : public BTreeNode
{
    Point<T> _1;
    Point<T> _2;
public:
    Branch(Point<T> p1, Point<T> p2) :_1(p1), _2(p2) {}
};


class BTree{
public:
    typedef BTreeNode * iterator;
    iterator top() {return _root;}
    iterator _to_iter(BTreeNode * node) {return node;}
    iterator _set(iterator _iter, BTreeNode * node, uint32_t idx)
    {
        
        if (_iter)
        {
            iterator old = _iter->_c[idx];
            _iter->_c[idx] = node;
            if (node)
            {
                node->_p = _iter->_c[idx];
            }
            
            if (old) delete old;
        }
        
        return _to_iter(node);
    }
    iterator setL(iterator _iter, BTreeNode * node)
    {
        return _set(_iter, node, 0);
    }
    iterator setR(iterator _iter, BTreeNode * node)
    {
        return _set(_iter, node, 1);
    }
    
    BTree(BTreeNode* node): _root(node) {}
private:
    BTreeNode* _root;
};

template <class T>
Branch<T> *make_branch(Point<T> p1, Point<T> p2)
{
    return new Branch<T>(p1, p2);
}

template <class T>
BTreeNode * add_new_site(Leaf<T> &_base, Leaf<T> &site)
{
    auto b = make_branch(_base.point, site.point);
    BTree t(b);
    t.setL(t.top(), new Leaf<T>(_base));
    BTree b1(make_branch(site.point, _base.point));
    b1.setL(b1.top(), new Leaf<T>(site));
    b1.setR(b1.top(), new Leaf<T>(_base));
    t.setR(t.top(), b1.top());
}

#endif /* Voronoi_hpp */
