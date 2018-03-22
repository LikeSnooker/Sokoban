//
//  CIteratorVeter.hpp
//  sokoban
//
//  Created by 张雨 on 2016/11/17.
//  Copyright © 2016年 张雨. All rights reserved.
//

#ifndef CIteratorVector_hpp
#define CIteratorVector_hpp

#include <stdio.h>
#include <vector>
#include "common.hpp"
using namespace std;
class CIteratorVector : public vector<SokobanData> //内部自带迭代器的 vector
{
public:
    CIteratorVector(vector<SokobanData> & _vec);
    CIteratorVector();
    
private:
    vector<SokobanData>::iterator it;
public:
    SokobanData & getCurState()const;
    void next();
    void last();
    CIteratorVector & operator = (vector<SokobanData>  _vec);
    unsigned long index();
    void clear();
private:
    void push_back();
    void pop_back();
};
#endif /* CIteratorVeter_hpp */
