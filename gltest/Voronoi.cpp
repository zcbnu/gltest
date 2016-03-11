//
//  Voronoi.cpp
//  gltest
//
//  Created by 黄保应 on 16/1/27.
//  Copyright © 2016年 黄保应. All rights reserved.
//

#include "Voronoi.hpp"
#include <iostream>


void printf(const char *s)
{
    while (*s) {
        if (*s == '%') {
            if (*(s + 1) == '%') {
                ++s;
            }
            else {
                throw std::runtime_error("invalid format string: missing arguments");
            }
        }
        std::cout << *s++;
    }
}

template<typename T, typename... Args>
void printf(const char *s, T value, Args... args)
{
    while (*s) {
        if (*s == '%') {
            if (*(s + 1) == '%') {
                ++s;
            }
            else {
                std::cout << value;
                // call even when *s == 0 to detect extra arguments
                printf(s + 1, args...);
                return;
            }
        }
        std::cout << *s++;
    }
    throw std::logic_error("extra arguments provided to printf");
}

BTree create(BTree &tree)
{
    return tree;
}

template<typename ... T, typename Iter>
BTree create(BTree& tree, Iter _iterL, T ...args)
{
    tree.setL(tree.top(), _iterL);
    create(tree, args...);
    return tree;
}
//__is_base_of_imp::_Src<int>::operator __is_base_of_imp::_Dst<float> const&<float>()

//template <class Tp>
//template <class _Up>
//__is_base_of_imp::_Src<Tp>::operator __is_base_of_imp::_Dst<_Up> const&()
//{
//    std::cout << "building" <<std::endl;
//}
