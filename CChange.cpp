//
//  CChange.cpp
//  sokoban
//
//  Created by 张雨 on 16/7/6.
//  Copyright © 2016年 张雨. All rights reserved.
//

#include "CChange.hpp"
CChange CChange::EMPTY_CHANGE = CChange(CPosition(-1,-1), CPosition(-1,-1),CPosition(-1,-1));
CChange::CChange (const CPosition & _manOldPosition,const CPosition & _boxNewPosition,const CPosition & _boxOldPosition)
{
    m_boxNewPosition = _boxNewPosition;
    m_boxOldPosition = _boxOldPosition;
    m_manOldPosition = _manOldPosition;
}
bool CChange::operator == (const CChange & _change)const
{
    return m_boxNewPosition == _change.m_boxNewPosition && m_boxOldPosition == m_boxOldPosition && m_manOldPosition == _change.m_manOldPosition;
}
bool CChange::operator != (const CChange & _change)const
{
    return !(m_boxNewPosition == _change.m_boxNewPosition && m_boxOldPosition == m_boxOldPosition && m_manOldPosition == _change.m_manOldPosition);
}