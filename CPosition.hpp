//
//  CPosition.h
//  sokoban
//
//  Created by 张雨 on 15/8/28.
//  Copyright (c) 2015年 张雨. All rights reserved.
//

#ifndef __sokoban__CPosition__
#define __sokoban__CPosition__

#include <stdio.h>
class CPosition
{
public:
    enum EDirection{
        UP    =0,
        DOWN  =1,
        LEFT  =2,
        RIGHT =3,
        MAX_D =4
    };
public:
    CPosition();
    CPosition(unsigned char _row,unsigned char _line);
    CPosition(const CPosition & _pos);
public:
    unsigned char m_row;
    unsigned char m_line;;
public:
    bool operator ==       (const CPosition & _pos) const;
    bool operator <        (const CPosition & _pos) const;
    CPosition& operator =  (const CPosition & _pos);
    CPosition& opposite    (const CPosition & _pos)const; //以自己为中心  _pos 的对称点
    CPosition& posByDirection         (EDirection _direction)const;
    EDirection directionOfPos(CPosition & _pos);
public:
    CPosition upPosition()const;
    CPosition downPosition()const;
    CPosition leftPosition()const;
    CPosition rightPosition()const;
    void      Go(EDirection _direction);
    size_t HashTableSize()const;
    size_t HashValue()const;
    void PrintLog();
};
#endif /* defined(__sokoban__CPosition__) */
