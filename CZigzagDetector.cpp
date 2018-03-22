//
//  CZigzagDetector.cpp
//  sokoban
//
//  Created by 张雨 on 15/12/23.
//  Copyright © 2015年 张雨. All rights reserved.
//

#include "CZigzagDetector.hpp"
bool CZigzagDetector::detect()
{
    vector<pos_pair>::iterator it_pair = pos_pairs.begin();
    while (it_pair != pos_pairs.end()) {
        if(CSokoban::getInstance()->beBox(it_pair->m_second) && CSokoban::getInstance()-> beBox(it_pair->m_first))
        {
            return false;
        }
        it_pair++;
    }
    return true;
}
bool CZigzagDetector::detect(CState &_state)
{
    vector<pos_pair>::iterator it_pair = pos_pairs.begin();
    while (it_pair != pos_pairs.end()) {
        if(_state[it_pair->m_second.m_row][it_pair->m_second.m_line] && _state[it_pair->m_first.m_row][it_pair->m_first.m_line])
        {
            return false;
        }
        it_pair++;
    }
    return true;
}
bool CZigzagDetector::detect(CPosition & _oldBoxPos,CPosition & _newBoxPos)
{
    auto it_pair = pos_pairs.begin();
    while (it_pair != pos_pairs.end()) {
        if(CSokoban::getInstance()->beBox(it_pair->m_second) && CSokoban::getInstance()->beBox(it_pair->m_first))
        {
            return false;
        }
        it_pair++;
    }
    return true;
}
bool CZigzagDetector::detect(CState & _boxState,CPosition &_oldBoxPos,CPosition & _newBoxPos)
{
    auto it_pair = pos_pairs.begin();
    while (it_pair != pos_pairs.end()) {
        if(_boxState[it_pair->m_second.m_row][it_pair->m_second.m_line] && _boxState[it_pair->m_first.m_row][it_pair->m_first.m_line])
        {
            return false;
        }
        it_pair++;
    }
    return true;
}
void CZigzagDetector::init()
{
    pos_pairs.clear();
    for(int row = 0;row<16 ;row++)
    {
        for(int line =0;line<16;line++)
        {
            if(CSokoban::getInstance()->beWall(row,line))
            {
                //   *#
                //  #*
                if(CSokoban::getInstance()->beWall(row+1,line-2))
                {
                    if(!CSokoban::getInstance()->beWall(row,line-1) && ! CSokoban::getInstance()->beWall(row+1,line-1))
                    {
                        if(!CSokoban::getInstance()->beWall(row, line-2) && ! CSokoban::getInstance()->beWall(row+1,line))//增加这一步判断是为了筛掉会被堆// 叠监测器监测到的局面
                        {
                            if(!CSokoban::getInstance()->beWall(row -1, line-1) && ! CSokoban::getInstance()->beWall(row+2,line-1))//筛掉死角
                            {
                                if( !CSokoban::getInstance()->beTarget(row,line-1) || ! CSokoban::getInstance()->beTarget(row+1,line-1) )
                                {
                                    pos_pair a_pair(CPosition(row,line-1),CPosition(row+1,line-1));
                                    pos_pairs.push_back(a_pair);
                                }
                            }
                        }
                    }
                }
                // #*
                //  *#
                if(CSokoban::getInstance()->beWall(row+1,line+2))
                {
                    if( !CSokoban::getInstance()->beWall(row,line+2) && !CSokoban::getInstance()->beWall(row+1,line) )// 堆叠
                    {
                        if( !CSokoban::getInstance()->beWall(row+2,line+1) && !CSokoban::getInstance()->beWall(row-1,line+1) )//死角
                        {
                            if(!CSokoban::getInstance()->beWall(row,line+1) && ! CSokoban::getInstance()->beWall(row+1,line+1))
                            {
                                if( !CSokoban::getInstance()->beTarget(row,line+1) || !CSokoban::getInstance()->beTarget(row+1,line+1) )
                                {
                                    pos_pair a_pair(CPosition(row,line+1),CPosition(row+1,line+1));
                                    pos_pairs.push_back(a_pair);
                                }
                            }
                        }
                    }
                }
                
                //     #
                //     **
                //      #
                if(CSokoban::getInstance()->beWall(row+2,line+1))
                {
                    if( !CSokoban::getInstance()->beWall(row,line+1) && !CSokoban::getInstance()->beWall(row+2,line) )         //堆叠
                    {
                        if( !CSokoban::getInstance()->beWall(row+1,line-1) && !CSokoban::getInstance()->beWall(row+1,line+2) ) //死角
                        {
                            if(!CSokoban::getInstance()->beWall(row+1,line) && ! CSokoban::getInstance()->beWall(row+1,line+1))
                            {
                                if( !CSokoban::getInstance()->beTarget(row+1,line) || !CSokoban::getInstance()->beTarget(row+1,line+1) )
                                {
                                    pos_pair a_pair(CPosition(row+1,line),CPosition(row+1,line+1));
                                    pos_pairs.push_back(a_pair);
                                }
                            }
                        }
                    }
                }
                //      #
                //     **
                //     #
                if(CSokoban::getInstance()->beWall(row+2,line-1))
                {
                    if( !CSokoban::getInstance()->beWall(row,line-1) && !CSokoban::getInstance()->beWall(row+2,line) )      //堆叠
                    {
                        if( !CSokoban::getInstance()->beWall(row+1,line+1) && !CSokoban::getInstance()->beWall(row+1,line-2) )  //死角
                        {
                            if(!CSokoban::getInstance()->beWall(row+1,line-1) && ! CSokoban::getInstance()->beWall(row+1,line))
                            {
                                if( !CSokoban::getInstance()->beTarget(row+1,line-1) || !CSokoban::getInstance()->beTarget(row+1,line) )
                                {
                                    pos_pair a_pair(CPosition(row+1,line-1),CPosition(row+1,line));
                                    pos_pairs.push_back(a_pair);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
void CZigzagDetector::clearDectector ()
{
    
}
