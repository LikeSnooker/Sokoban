//
//  CWeltDetector.cpp
//  sokoban
//
//  Created by 张雨 on 15/9/8.
//  Copyright (c) 2015年 张雨. All rights reserved.
//


#include "CWeltDetector.hpp"
extern int g_length;
CWeltDetector::CWeltDetector()
{
    memset(m_mapingTable, 0, sizeof(Edge*[16][16]));
}
bool CWeltDetector::detect(CPosition & _oldBoxPos,CPosition & _newBoxPos)
{
    if(m_mapingTable[_newBoxPos.m_row][_newBoxPos.m_line] == NULL)
        return true;
    Edge * edge_ptr = m_mapingTable[_newBoxPos.m_row][_newBoxPos.m_line];
    vector<CPosition>::iterator it_pos;
    it_pos = edge_ptr->m_positions.begin();
    int boxCount =0;
    while (it_pos != edge_ptr->m_positions.end()) {
        if(CSokoban::getInstance()->beBox(*it_pos))
        {
            boxCount ++ ;
        }
        it_pos++;
    }
    if(boxCount > edge_ptr->m_targetCount)
        return false;
    return true;
}
bool CWeltDetector::detect(CState & _boxState,CPosition &_oldBoxPos,CPosition & _newBoxPos)
{
    if(m_mapingTable[_newBoxPos.m_row][_newBoxPos.m_line] == NULL)
        return true;
    Edge * edge_ptr = m_mapingTable[_newBoxPos.m_row][_newBoxPos.m_line];
    vector<CPosition>::iterator it_pos;
    it_pos = edge_ptr->m_positions.begin();
    int boxCount =0;
    while (it_pos != edge_ptr->m_positions.end()) {
//        if(CSokoban::getInstance()->beBox(*it_pos))
        if(_boxState[it_pos->m_row][it_pos->m_line])
        {
            boxCount ++ ;
        }
        it_pos++;
    }
    if(boxCount > edge_ptr->m_targetCount)
        return false;
    return true;
}
bool CWeltDetector::detect()
{
    vector<Edge>::iterator edge_it  = m_edges.begin();
    vector<CPosition>::iterator         pos_it;
    int box_count   =0;
    while (edge_it != m_edges.end()) {
        pos_it= edge_it->m_positions.begin();
        box_count  =0;
        while (pos_it != edge_it->m_positions.end()) {
            
            if(CSokoban::getInstance()->beBox(pos_it->m_row, pos_it->m_line))
            {
                box_count++;
                if(box_count > (edge_it->m_targetCount))
                {
                    return false;
                }
            }
            pos_it++;
        }
        edge_it++;
    }
    return true;
}
bool CWeltDetector::detect(CState &_state)
{
    vector<Edge>::iterator edge_it  = m_edges.begin();
    vector<CPosition>::iterator         pos_it;
    int box_count   =0;
    while (edge_it != m_edges.end()) {
        pos_it= edge_it->m_positions.begin();
        box_count  =0;
        while (pos_it != edge_it->m_positions.end()) {
            
            if(_state[pos_it->m_row][pos_it->m_line])
            {
                box_count++;
                if(box_count > (edge_it->m_targetCount))
                {
                    return false;
                }
            }
            pos_it++;
        }
        edge_it++;
    }
    return true;
}
void CWeltDetector::init()
{
    m_edges.clear();
    memset(m_mapingTable, 0, sizeof(Edge*[16][16]));
    bool edge_b = false;
    vector<CPosition>  edge;
    int   targetCount = 0;
// *       *
// *********
    for(int row =1;row < g_length ;row++)
    {
        for(int line =0;line < g_length;line++)
        {
            if(CSokoban::getInstance()->beWall(row-1, line))
            {
                edge_b = true;
            }
            if(edge_b)
            {
                if(CSokoban::getInstance()->beWall(row, line) && !CSokoban::getInstance()->beWall(row-1, line))
                {
                    edge.push_back(CPosition(row-1,line));
                }
                if(CSokoban::getInstance()->beTarget(row-1, line))
                {
                    targetCount++;
                }
                if(CSokoban::getInstance()->beWall(row-1, line) && edge.size()>0)
                {
                    m_edges.push_back(Edge(edge,targetCount));
                    edge.clear();
                    targetCount=0;
                }
                if(!CSokoban::getInstance()->beWall(row, line) && !CSokoban::getInstance()->beWall(row-1, line))
                {
                    edge.clear();
                    targetCount  =0;
                    edge_b    =false;
                }
            }
        }
        edge.clear();
        targetCount  =0;
        edge_b    =false;
    }
    edge.clear();
    targetCount  =0;
    edge_b    =false;
// ********
// *      *
    for(int row =0;row<g_length-1;row++)
    {
        for(int line =0;line < g_length;line++)
        {
            if( CSokoban::getInstance()->beWall(row+1, line))
            {
                edge_b = true;
            }
            if(edge_b)
            {
                if(CSokoban::getInstance()->beWall(row, line) && !CSokoban::getInstance()->beWall(row+1, line))
                {
                    edge.push_back(CPosition(row+1,line));
                }
                if(CSokoban::getInstance()->beTarget(row+1, line))
                {
                    targetCount++;
                }
                if(CSokoban::getInstance()->beWall(row+1, line) && edge.size()>0)
                {
                    m_edges.push_back(Edge(edge,targetCount));
                    
                    edge.clear();
                    targetCount=0;
                }
                if(!CSokoban::getInstance()->beWall(row, line) && !CSokoban::getInstance()->beWall(row+1, line))
                {
                    edge.clear();
                    targetCount  =0;
                    edge_b    =false;
                }
            }
        }
        edge.clear();
        targetCount  =0;
        edge_b    =false;
    }
    edge.clear();
    targetCount  =0;
    edge_b    =false;
// **
//  *
//  *
//  *
//  *
// **
    for(int line =1;line < g_length;line++)
    {
        for(int row =0;row < g_length;row++)
        {
            if(CSokoban::getInstance()->beWall(row, line-1))
            {
                edge_b = true;
            }
            if(edge_b)
            {
                if(CSokoban::getInstance()->beWall(row, line) && !CSokoban::getInstance()->beWall(row, line-1))
                {
                    edge.push_back(CPosition(row,line-1));
                }
                if(CSokoban::getInstance()->beTarget(row, line-1))
                {
                    targetCount++;
                }
                if(CSokoban::getInstance()->beWall(row, line-1) && edge.size()>0)
                {
                    m_edges.push_back(Edge(edge,targetCount));                    
                    edge.clear();
                    targetCount=0;
                }
                if(!CSokoban::getInstance()->beWall(row, line) && !CSokoban::getInstance()->beWall(row, line-1))
                {
                    edge.clear();
                    targetCount  =0;
                    edge_b    =false;
                }
            }
        }
        edge.clear();
        targetCount  =0;
        edge_b    =false;
    }
    edge.clear();
    targetCount  =0;
    edge_b    =false;
// **
// *
// *
// *
// *
// **
    for(int line =0;line < g_length-1;line++)
    {
        for(int row =0; row < g_length;row++)
        {
            
            if(CSokoban::getInstance()->beWall(row, line) && CSokoban::getInstance()->beWall(row, line+1))
            {
                edge_b = true;
            }
            if(edge_b)
            {
                if(CSokoban::getInstance()->beWall(row, line) && !CSokoban::getInstance()->beWall(row, line+1))
                {
                    edge.push_back(CPosition(row,line+1));
                }
                if(CSokoban::getInstance()->beTarget(row, line+1))
                {
                    targetCount++;
                }
                if(CSokoban::getInstance()->beWall(row, line+1) && edge.size()>0)
                {
                    m_edges.push_back(Edge(edge,targetCount));                    
                    edge.clear();
                    targetCount=0;
                }
                if(!CSokoban::getInstance()->beWall(row, line) && !CSokoban::getInstance()->beWall(row, line+1))
                {
                    edge.clear();
                    targetCount  =0;
                    edge_b    =false;
                }
            }
        }
        edge.clear();
        targetCount  =0;
        edge_b    =false;
    }
    vector<Edge>::iterator it_edge = m_edges.begin();
    vector<CPosition>::iterator it_pos;
    while (it_edge != m_edges.end()) {
        it_pos= it_edge->m_positions.begin();
        while (it_pos != it_edge->m_positions.end()) {
            
            m_mapingTable[it_pos->m_row][it_pos->m_line] = & (*it_edge);
            it_pos++;
        }
        it_edge++;
    }
}
void CWeltDetector::clearDectector()
{
    m_edges.clear();
}
