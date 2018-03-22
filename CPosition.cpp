//
//  CPosition.cpp
//  sokoban
//
//  Created by 张雨 on 15/8/28.
//  Copyright (c) 2015年 张雨. All rights reserved.
//

#include "CPosition.hpp"
CPosition::CPosition()
{
    m_line = 0;
    m_row  = 0;
}
CPosition::CPosition(unsigned char _row ,unsigned char _line)
{
    m_line = _line;
    m_row  = _row;
}
bool CPosition::operator ==  (const CPosition & _pos) const
{
    return m_row == _pos.m_row && m_line == _pos.m_line;
}
bool CPosition::operator <   (const CPosition & _pos) const
{
    return m_row < _pos.m_row ? true : (m_row > _pos.m_row ? false : m_line < _pos.m_line);
}
CPosition& CPosition::operator =  (const CPosition & _pos)
{
    m_row  = _pos.m_row;
    m_line = _pos.m_line;
    return *this;
}
typedef struct
{
    char row;
    char line;
}Dir;
const Dir dirs[4] =
{
    {-1,0},
    {1,0},
    {0,-1},
    {0,1}
};
CPosition& CPosition::posByDirection(CPosition::EDirection _direction)const
{
    static CPosition pos;
    pos = *this;
    pos.m_row  += dirs[_direction].row;
    pos.m_line += dirs[_direction].line;
    return pos;
}
void CPosition::Go(CPosition::EDirection _direction)
{
    m_row  += dirs[_direction].row;
    m_line += dirs[_direction].line;
}
CPosition::CPosition(const CPosition & _pos)
{
    m_row  = _pos.m_row;
    m_line = _pos.m_line;
    
}
CPosition& CPosition::opposite(const CPosition & _pos)const
{
    static CPosition result;
    result.m_row  = m_row  + (m_row - _pos.m_row);
    result.m_line = m_line + (m_line - _pos.m_line);
    return result;
}

CPosition::EDirection CPosition::directionOfPos(CPosition & _pos)
{
    if( (m_row - _pos.m_row) * (m_row - _pos.m_row) + (m_line - _pos.m_line) * (m_line - _pos.m_line) ==1)
    {
        if(m_row == _pos.m_row)
        {
            return _pos.m_line > m_line ? RIGHT:LEFT;
        }
        else
        {
            return _pos.m_row  > m_row  ?DOWN :UP;
        }
    }
    else
    {
        return MAX_D;
    }
}
CPosition CPosition::upPosition()const
{
    return CPosition(m_row-1,m_line);
}
CPosition CPosition::downPosition()const
{
    return CPosition(m_row+1,m_line);
}
CPosition CPosition::leftPosition()const
{
    return CPosition(m_row,m_line-1);
}
CPosition CPosition::rightPosition()const
{
    return CPosition(m_row,m_line+1);
}
size_t CPosition::HashTableSize()const
{
    return 256;
}
size_t CPosition::HashValue()const
{
    return (m_row << 4) + m_line;
}

void CPosition::PrintLog()
{
    printf("row = %d,line = %d\n",m_row,m_line);
}










