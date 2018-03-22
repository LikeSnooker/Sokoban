//
//  CLongBool.cpp
//  sokoban
//
//  Created by 张雨 on 15/10/19.
//  Copyright © 2015年 张雨. All rights reserved.
//

#include "CLongBool.hpp"
CLongBool::~CLongBool()
{
    delete m_data;
}
CLongBool::CLongBool(long _maxValue)
{
    if(_maxValue <0)
        return;
    
    long size   = _maxValue % (sizeof(int)*8) ==0 ?_maxValue/(sizeof(int)*8):_maxValue/(sizeof(int)*8)+1;
    m_data     = new int[size];
    memset(m_data, 0, size);
    m_maxValue = _maxValue;
}

void CLongBool::setBoolOnSet(long _set)
{
    if(_set > m_maxValue)
        throw _set;
    int section_set = _set % (sizeof(int) *8);
    int section     = _set / (sizeof(int) *8);
    
    m_data[section] ^= (1<<section_set);
}
bool CLongBool::beBoolOnSet (long _set)
{
    if(_set > m_maxValue)
        throw _set;
    int section_set = _set % (sizeof(int) *8);
    int section     = _set / (sizeof(int) *8);
    
    return m_data[section] & (1<<section_set);
}