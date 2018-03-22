//
//  CChange.hpp
//  sokoban
//
//  Created by 张雨 on 16/7/6.
//  Copyright © 2016年 张雨. All rights reserved.
//

#ifndef CChange_hpp
#define CChange_hpp
#include "CPosition.hpp"
#include <stdio.h>
class CChange
{
public:
    CPosition m_boxNewPosition;
    CPosition m_boxOldPosition;
    CPosition m_manOldPosition;
public:
    CChange (const CPosition & _manOldPosition, const CPosition & _boxNewPosition,const CPosition & _boxOldPosition);
public:
    static CChange EMPTY_CHANGE;
public:
    bool operator == (const CChange & _change)const;
    bool operator != (const CChange & _change)const;
};
#endif /* CChange_hpp */
