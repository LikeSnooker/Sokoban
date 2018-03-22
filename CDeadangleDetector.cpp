//
//  DeadangleDetector.cpp
//  sokoban
//
//  Created by 张雨 on 15/9/11.
//  Copyright (c) 2015年 张雨. All rights reserved.
//

#include "CDeadangleDetector.hpp"
//  *#  #   #*   #
//  #   *#   #  #*    相邻两面都有墙  说明此处必是死角
extern int g_length;
template <typename pointerType>
void exchangePointer(pointerType * &pt1,pointerType * & pt2)
{
    pt1 = (pointerType*) ( (long)pt1 ^ (long)pt2 );
    pt2 = (pointerType*) ( (long)pt1 ^ (long)pt2 );
    pt1 = (pointerType*) ( (long)pt1 ^ (long)pt2 );
}
bool CDeadangleDetector::detect()
{
    for(auto it = m_deadAngles.begin();it != m_deadAngles.end();it++)
    {
        if(CSokoban::getInstance()->beBox(it->m_row,it->m_line))
        {
            return false;
        }
    }
    return true;
}
bool CDeadangleDetector::detect(CState &_state)
{
    for(auto it = m_deadAngles.begin();it != m_deadAngles.end();it++)
    {
        if(_state[it->m_row][it->m_line])
        {
            return false;
        }
    }
    return true;
}
bool CDeadangleDetector::detect(CPosition & _oldBoxPos,CPosition & _newBoxPos)
{
    return !m_dead[_newBoxPos.m_row][_newBoxPos.m_line];
}
bool CDeadangleDetector::detect(CState & _boxState,CPosition &_oldBoxPos,CPosition & _newBoxPos)
{
    return !m_dead[_newBoxPos.m_row][_newBoxPos.m_line];
}
bool Internal(CPosition _pos)
{
    if( CSokoban::getInstance()->beWall(_pos))
        return false;
    // 检测人的移动是否能够出边界  也就是说是否有个围墙限制人的移动在合理的范围内
    MAN_PATH *wait_list = new  MAN_PATH;
    MAN_PATH * new_list = new  MAN_PATH;
    bool explored[16][16];
    memset(explored, 0, sizeof(bool[16][16]));
    wait_list->push_back(_pos);
    explored[_pos.m_row][_pos.m_line] = true;
    POS_IT list_it;
    while ( wait_list->size() > 0 ) {
        list_it = wait_list->begin();
        while(list_it != wait_list->end())
        {
            for(int dire =0;dire<4;dire++)
            {
                CPosition next = list_it->posByDirection((EDirection)dire);
                if(next.m_row > g_length-1 || next.m_line > g_length-1)
                {
                    delete wait_list;
                    delete new_list;
                    return false;
                }
                else if( !explored[next.m_row][next.m_line] && !CSokoban::getInstance()->beWall(next))
                {
                    explored[next.m_row][next.m_line] = true;
                    new_list->push_back(next);
                }
            }
            list_it++;
        }
        exchangePointer(new_list, wait_list);
        new_list->clear();
    }
    delete wait_list;
    delete new_list;
    return true;
}
void CDeadangleDetector::init()
{
    m_deadAngles.clear();
    memset(m_dead, 0, sizeof(bool[16][16]));
    bool bUp,bDown,bLeft,bRight;
    for(int row =1 ;row < g_length-1 ; row++)
    {
        for(int line = 1 ;line < g_length-1 ; line++)
        {
            bUp   = CSokoban::getInstance()->beWall(row-1,line);
            bDown = CSokoban::getInstance()->beWall(row+1,line);
            bLeft = CSokoban::getInstance()->beWall(row,line-1);
            bRight= CSokoban::getInstance()->beWall(row,line+1);
            
            if(!CSokoban::getInstance()->beTarget(row,line) && !CSokoban::getInstance()->beWall(row,line))
            {
                if((bUp&&bRight) || (bRight&&bDown) || (bDown&&bLeft) || (bLeft&&bUp) )
                {
                    if(Internal(CPosition(row,line)))
                    {
                        m_deadAngles.push_back(CPosition(row,line));
                        m_dead[row][line] = true;
                    }
                }
            }
        }
    }
}
void CDeadangleDetector::clearDectector()
{

}
