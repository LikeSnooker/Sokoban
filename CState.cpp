//
//  CState.cpp
//  sokoban
//
//  Created by 张雨 on 15/9/1.
//  Copyright (c) 2015年 张雨. All rights reserved.
//

#include "CState.hpp"
#include "CSokoban.hpp"
///此源文件中的代码都是基于 char [32]保存数据的假设 因此 保存数据发生改变时  代码将出现大的改动
CState CState::EMPTY_STATE = CState();
CState::CState()
{
    memset(m_matrix, 0, sizeof(unsigned char[32]));
    m_manP        = CPosition(0,0);
}

int my_memcmp(char *s1,char * s2)
{
    const long *p1, *q1;
    int off = sizeof(void*) == 8?4:8;
    p1      = (const long *)s1;
    q1      = (const long *)s2;
    while (off --) {
        if (*p1 ++ != *q1 ++) {
            return p1[-1] > q1[-1] ? 1 : -1;
        }
    }
    return 0;
}
void my_memcpy(char *s1,char* s2)
{
    long *p1, *q1;
    int off = sizeof(void*) == 8?4:8;
    p1      = (long *)s1;
    q1      = (long *)s2;
    while (off --) {
        p1++;
        q1++;
        p1[-1] = q1[-1];
    }
}
bool CState::operator == (const CState & _state)const
{
    return (my_memcmp((char*)m_matrix,(char*)_state.m_matrix ) == 0) && m_manP == _state.m_manP;
}
bool CState::sameLayout(const CState &_state)const
{
    return my_memcmp((char*)m_matrix,(char*)_state.m_matrix ) == 0;
}
bool CState::existAt(unsigned char _row,unsigned char _line) const
{
    if(_row > 15 || _line > 15)
    {
        throw OutsideException();
        return false;
    }
    bool   beRunoff      = _line > 7;
    unsigned char offset = beRunoff ?_line-8:_line;
    unsigned char filter = 128 >> offset;
    return filter & m_matrix[(_row <<1 ) + beRunoff];
}
bool CState::existAt(const CPosition& _pos) const
{
    if(_pos.m_row > 15 || _pos.m_line > 15)
    {
        throw OutsideException();
        return false;
    }
    bool   beRunoff      = _pos.m_line > 7;
    unsigned char offset = beRunoff?_pos.m_line-8:_pos.m_line;
    unsigned char filter = 128 >> offset;
    return filter & m_matrix[(_pos.m_row <<1 ) + beRunoff];
}
void CState::setAt  (unsigned char _row,unsigned char _line)
{
    bool   beRunoff      = _line > 7;
    unsigned char offset = beRunoff ?_line-8:_line;
    unsigned char filter = 128 >> offset;
    m_matrix[(_row << 1) + beRunoff] |= filter;
}
void CState::setAt  (const CPosition & _pos)
{
    bool   beRunoff      = _pos.m_line > 7;
    unsigned char offset = beRunoff ?_pos.m_line-8:_pos.m_line;
    unsigned char filter = 128 >> offset;
    m_matrix[(_pos.m_row << 1) + beRunoff] |= filter;
}
bool CState::existAndSetAt(const CPosition &_pos)
{
    bool   beRunoff      = _pos.m_line > 7;
    unsigned char offset = beRunoff ?_pos.m_line-8:_pos.m_line;
    unsigned char filter = 128 >> offset;
    if( filter & m_matrix[(_pos.m_row <<1 ) + beRunoff] )
    {
        return true;
    }
    else
    {
        m_matrix[(_pos.m_row << 1) + beRunoff] |= filter;
        return false;
    }
}
void CState::unsetAt(unsigned char _row,unsigned char _line)
{
    bool   beRunoff      = _line > 7;
    unsigned char offset = beRunoff ?_line-8:_line;
    unsigned char filter = ~(128 >> offset);
    m_matrix[(_row<<1) + beRunoff] &= filter;
}
void CState::unsetAt(const CPosition& _pos)
{
    bool   beRunoff      = _pos.m_line > 7;
    unsigned char offset = beRunoff ?_pos.m_line-8:_pos.m_line;
    unsigned char filter = ~(128 >> offset);
    m_matrix[(_pos.m_row<<1) + beRunoff] &= filter;

}
void CState::clear()
{
    memset(m_matrix, 0, sizeof(unsigned char[32]));
}
CState & CState::operator = (const CState & _another)
{
    my_memcpy((char*)m_matrix, (char*)_another.m_matrix );
    m_manP        = _another.m_manP;
    return *this;
}
size_t CState::hash_value()const
{
    unsigned long res = 0;
    for (int step = 0 ; step <32; step++)
        res = 5 * res + m_matrix[step];
    return size_t(res);
}
CState CState::deference(const CState &_state)
{
    CState result;
    long *p1;
    const long *q1;
    int off;
    off = sizeof(void *)==8?4:8;
    p1  =       (long *)result.m_matrix;
    q1  = (const long *)_state.m_matrix;
    for(int section =0 ;section < off;section ++)
    {
        p1[section] ^= q1[section];
    }
    return result;
}
vector<CPosition> CState::allExistPosions()
{
    vector<CPosition> result;
    for(int row = 0 ;row <16;row ++)
    {
        for(int line = 0;line < 16;line++)
        {
            bool   beRunoff      = line > 7;
            unsigned int index = (row<<1) +beRunoff;
            unsigned char offset = beRunoff ?line-8:line;
            unsigned char filter = 128 >> offset;
            if( filter & m_matrix[index])
            {
                result.push_back(CPosition(row,line));
            }
        }
    }
    return result;
}
void CState::fillFrom(const CPosition & _pos1,const Crossroads & _cro)
{
    static const Crossroads CRO_NOT_UP    = {false,true,true,true};
    static const Crossroads CRO_NOT_DOWN  = {true,false,true,true};
    static const Crossroads CRO_NOT_LEFT  = {true,true,false,true};
    static const Crossroads CRO_NOT_RIGHT = {true,true,true,false};
    if(_cro.Up)
    {
        if(!existAndSetAt(_pos1.upPosition()))
        {
            fillFrom(_pos1.upPosition(),CRO_NOT_DOWN);
        }
    }
    if(_cro.Down)
    {
        if(!existAndSetAt(_pos1.downPosition()))
        {
            fillFrom(_pos1.downPosition(),CRO_NOT_UP);
        }
    }
    if(_cro.Left)
    {
        if(!existAndSetAt(_pos1.leftPosition()))
        {
            fillFrom(_pos1.leftPosition(),CRO_NOT_RIGHT);
        }
    }
    if(_cro.Right)
    {
        if(!existAndSetAt(_pos1.rightPosition()))
        {
            fillFrom(_pos1.rightPosition(),CRO_NOT_LEFT);
        }
    }
}
void CState::fillFromEX(const CPosition & _pos1,CState & _result)
{
    _result.setAt(_pos1);
    if(!existAndSetAt(_pos1.upPosition()))
    {
        fillFromEX(_pos1.upPosition(),_result);
    }
    else
    {
        _result.setAt(_pos1.upPosition());
    }
    //
    if(!existAndSetAt(_pos1.downPosition()))
    {
        fillFromEX(_pos1.downPosition(),_result);
    }
    else
    {
        _result.setAt(_pos1.downPosition());
    }
    //
    if(!existAndSetAt(_pos1.leftPosition()))
    {
        fillFromEX(_pos1.leftPosition(),_result);
    }
    else
    {
        _result.setAt(_pos1.leftPosition());
    }
    //
    if(!existAndSetAt(_pos1.rightPosition()))
    {
        fillFromEX(_pos1.rightPosition(),_result);
    }
    else
    {
        _result.setAt(_pos1.rightPosition());
    }
}
EdgeInsets CState::getInsets()
{
    EdgeInsets edge_insets;
    edge_insets.left  = 15;
    edge_insets.right = 0;
    edge_insets.up    = 15;
    edge_insets.down  = 0;
    for(int row =0; row < 16;row++)
    {
        for(int line = 0 ; line < 16; line ++)
        {
            if(existAt(row, line))
            {
                edge_insets.left  = MIN(edge_insets.left,line);
                edge_insets.right = MAX(edge_insets.right,line);
                edge_insets.up    = MIN(edge_insets.up, row);
                edge_insets.down  = MAX(edge_insets.down,row);
            }
        }
    }
    return edge_insets;
}
int CState::count()
{
    int count =0 ;
    for(int row =0;row <16;row++)
    {
        for(int line = 0;line <16;line++)
        {
            count += existAt(row,line)?1:0;
        }
    }
    return count;
}
void CState::printState()
{
    cout <<endl;
    for(int row =0; row <16;row++)
    {
        for(int line =0;line <16;line++)
        {
            if(existAt(row, line))
                cout<<"1 ";
            else
                cout<<"0 ";
        }
        cout <<endl;
    }
}
//重载操作符
CState & CState::operator |= (const CState & _state)
{
    long *p1;
    const long *q1;
    int off;
    off = sizeof(void *)==8?4:8;
    p1  =       (long *)m_matrix;
    q1  = (const long *)_state.m_matrix;
    for(int section =0 ;section < off;section ++)
    {
        p1[section] |= q1[section];
    }
    return *this;
}
CState & CState::operator &= (const CState & _state)
{
    long *p1;
    const long *q1;
    int off;
    off = sizeof(void *)==8?4:8;
    p1  =       (long *)m_matrix;
    q1  = (const long *)_state.m_matrix;
    for(int section =0 ;section < off;section ++)
    {
        p1[section] &= q1[section];
    }
    return *this;
}
CState & CState::operator ^= (const CState & _state)
{
    long *p1;
    const long *q1;
    int off;
    off = sizeof(void *)==8?4:8;
    p1  =       (long *)m_matrix;
    q1  = (const long *)_state.m_matrix;
    for(int section =0 ;section < off;section ++)
    {
        p1[section] ^= q1[section];
    }
    return *this;
}
CState & CState::operator ~  ()
{
    long *p1;
    int off;
    off = sizeof(void *)==8?4:8;
    p1  = (long*)m_matrix;
    for(int section =0;section<off;section++)
    {
        p1[section] = ~(p1[section]);
    }
    return *this;
}
bool* CState::operator [](int row)const
{
    static bool * temp = new bool[16];
    for(int line =0;line <16;line++)
    {
        temp[line] = existAt(row, line);
    }
    return temp;
}
