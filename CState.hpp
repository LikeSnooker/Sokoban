//
//  CState.h
//  sokoban
//
//  Created by 张雨 on 15/9/1.
//  Copyright (c) 2 15年 张雨. All rights reserved.
//

#ifndef __sokoban__CState__
#define __sokoban__CState__

#include <stdio.h>
#include "CPosition.hpp"
#include "common.hpp"
#include <vector>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;
//以bit位的方式表示一个2维数组，节省内存

class CSokoban;
class OutsideException{};
class CState
{
public:
    CState();
public:
    CPosition        m_manP;
public:
    bool operator ==(const CState & _state)const;//表明布局完全相同
private:
    char        m_matrix[32];
public:
    bool existAt(unsigned char _row,unsigned char _line) const;
    bool existAt(const CPosition& _pos) const;
private:
    friend class CSokoban;
    void setAt  (unsigned char _row,unsigned char _line);
    void setAt  (const CPosition& _pos);
    bool existAndSetAt(const CPosition &_pos); //设置一个点同时判断这点
    void unsetAt(unsigned char _row,unsigned char _line);
    void unsetAt(const CPosition& _pos);
public:
    CState & operator = (const CState & _another);
    friend class CSokoban;
    CState deference(const CState &_state);      //获得和指定状态之间的差异 对每一位进行 亦或操作
    bool sameLayout(const CState &_state)const;  //判断布局是否相同，此时不考虑人的位置
    vector<CPosition> allExistPosions();
    //
//        1 1 1 1 1 1                
//        1         1                
//    1 1 1 1 1 1   1                
//    1         1   1                
//    1   1       1 1                
//    1 1 1 1     1                  
//          1 1 1 1
    /// fillFrom函数的作用就是进行填充
//        1 1 1 1 1 1
//        1         1  
//    1 1 1 1 1 1   1  
//    1 1 1 1 1 1   1  
//    1 1 1 1 1 1 1 1  
//    1 1 1 1 1 1 1    
//          1 1 1 1
//                     

    void fillFrom(const CPosition & _pos1,const Crossroads & _cro);
    void fillFromEX(const CPosition & _pos1,CState & _result);
    void clear();
    EdgeInsets getInsets();
    int count();
public:
    size_t hash_value()const;
public:
    static CState EMPTY_STATE;
public:
    void printState();
public: //重载操作符
    CState & operator |= (const CState & _state);
    CState & operator &= (const CState & _state);
    CState & operator ^= (const CState & _state);
    CState & operator ~  ();
    bool*    operator [](int row)const;
};
#endif
