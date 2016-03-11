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
#include <type_traits>
#include <iostream>
template<typename T>
class Point
{
public:
    T x;
    T y;
    Point(T x_ = 0, T y_ = 0):x(x_),y(y_) { std::cout << "point" << std::endl;}
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

class BTreeNodeBase
{
};

class BTreeNodeNull : public BTreeNodeBase
{
};

class BTreeNode : public BTreeNodeBase
{
public:
    static const int CHILD_NUM = 2;
    BTreeNode* _c[CHILD_NUM] = {nullptr,nullptr};
    BTreeNode* _p = nullptr;
    BTreeNode* _n = nullptr;
    
};

template<typename T>
class Leaf : public BTreeNode
{
public:
    Point<T> point;
    Leaf(Leaf<T>&& rleaf) : point(rleaf.point){std::cout << "rleaf" << std::endl;}
    template<class T2>
    Leaf(Leaf<T2>&& leaf) {std::cout<< "t2" <<std::endl;}
    Leaf(Leaf<T>& leaf) : point(leaf.point) { std::cout << "leaf" << std::endl;}
    Leaf(const Point<T>& tPoint) : point(tPoint) {std::cout << "leaf-p" << std::endl;}
    Leaf(Point<T>&& tPoint = Point<T>()) : point(tPoint) { std::cout << "rleaf-p" << std::endl;}
    Leaf operator +(const Point<T>& p)
    {
        Point<T> tp;
        tp.x = point.x + p.x;
        tp.x = point.y + p.y;
        return Leaf<T>(std::move(tp));
    }
};


template <class T>
void log (T& l) {std::cout << "leaf&" << std::endl;}

template <class T>
void log (T&& l) {std::cout << "leaf&&" << std::endl;}

template <typename T>
void make_leaf(T&& builder) {
    log(std::forward<T>(builder));
    //    return Leaf<T>(std::forward<T>(builder));
}

template <typename T>
void make_leaf(Point<T>&& point) {
    log(std::forward<Point<T>>(point));
}
//
//template <typename T>
//Leaf<T> make_leaf(Point<T>& point) {
//    return Leaf<T>(std::forward<Point<T>>(point));
//}


template<typename T>
class Leaf2 : public BTreeNode, public Point<T>
{
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
    iterator _set(iterator &&_iter, BTreeNode * node, uint32_t idx)
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
    iterator setL(iterator &&_iter, BTreeNode node)
    {
        return _set(std::forward<iterator>(_iter), &node, 0);
    }
    iterator setR(iterator &&_iter, BTreeNode node)
    {
        return _set(std::forward<iterator>(_iter), &node, 1);
    }
    
//    BTree create(BTree& tree);
//    
//    template<class ... T, class Iter >
//    BTree create(BTree& tree, Iter _iterL, T ...);
    
    operator BTreeNode() const {return *_root;}
    
    BTree(BTreeNode* node = nullptr): _root(node) {}
private:
    BTreeNode* _root;
};

template <class T>
Branch<T> *make_branch(Point<T> p1, Point<T> p2)
{
    return new Branch<T>(p1, p2);
}

BTree create(BTree &tree);

template<class ... T, class Iter>
BTree create(BTree& tree, Iter _iterL, T ...args);

void printf(const char *s);

template<typename T, typename... Args>
void printf(const char *s, T value, Args... args);

template <class T>
BTreeNode * add_new_site(Leaf<T> &_base, Leaf<T> &site)
{
    auto b = make_branch(_base.point, site.point);
    BTree t(b);
    t.setL(t.top(), new Leaf<T>(_base));
    BTree b1(make_branch(site.point, _base.point));
    b1.setL(b1.top(), new Leaf<T>(site));
    b1.setR(b1.top(), new Leaf<T>(_base));
    t.setR(t.top(), make_branch(site.point, _base.point));
    BTree B;
    BTreeNode b2 = B;
    return b;
}

template <class T>
void remove_circle(BTree &tree, Branch<T> &branch) {
    
}

template<class _Leaf, class _Node>
class BLTree
{
    
private:
    _Node root;
    BLTree<_Leaf, _Node> left;
    BLTree<_Leaf, _Node> right;
};

namespace __is_base_of_imp
{
    template <class _Tp>
    struct _Dst
    {
        _Dst(const volatile _Tp &) {}
    };
    template <class _Tp>
    struct _Src
    {
        operator const volatile _Tp &();
        template <class _Up> operator const _Dst<_Up> &() {static float s = 1.0f; std::cout << "heel"; return s;}
    };
    template <size_t> struct __one { typedef char type; };
    template <class _Bp, class _Dp> typename __one<sizeof(_Dst<_Bp>(std::declval<_Src<_Dp> >()))>::type __test(int);
    template <class _Bp, class _Dp> std::__two __test(...);
}

#endif /* Voronoi_hpp */
