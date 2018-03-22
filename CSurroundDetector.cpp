//
//  CSurroundDetector.cpp
//  sokoban
//
//  Created by 张雨 on 15/10/20.
//  Copyright © 2015年 张雨. All rights reserved.
//

#include "CSurroundDetector.hpp"
// 检测如下情形
// ******** //* = wall
// *      * //# = box
// *######*
extern int g_length;
CSurroundDetector::CSurroundDetector()
{
    memset(m_mapingTable, 0, sizeof(vector<DoublePos> *[16][16]));
}
bool CSurroundDetector::detect()
{
    BOOL  beBox = true;
    vector<vector<DoublePos>>::iterator edge_it = m_edges.begin();
    vector<DoublePos>::iterator it_pos;
    while (edge_it!= m_edges.end()) {
        it_pos = edge_it->begin();
        while (it_pos != edge_it->end()) {
            if(! CSokoban::getInstance()->beBox(it_pos->m_pos2))
            {
                beBox = false;
            }
            it_pos++;
        }
        if(beBox)
        {
            return false;
        }
        beBox = true;
        edge_it++;
    }
    return true;
}
bool CSurroundDetector::detect(CState &_state)
{
    BOOL  beBox = true;
    vector<vector<DoublePos>>::iterator edge_it = m_edges.begin();
    vector<DoublePos>::iterator it_pos;
    while (edge_it!= m_edges.end()) {
        it_pos = edge_it->begin();
        while (it_pos != edge_it->end()) {
            if(! _state[it_pos->m_pos2.m_row][it_pos->m_pos2.m_line])
            {
                beBox = false;
            }
            it_pos++;
        }
        if(beBox)
        {
            return false;
        }
        beBox = true;
        edge_it++;
    }
    return true;

}
bool CSurroundDetector::detect(CPosition & _oldBoxPos,CPosition & _newBoxPos)
{
    if(m_mapingTable[_newBoxPos.m_row][_newBoxPos.m_line]==NULL)
        return true;
    else
    {
        bool beBox = true;
        vector<DoublePos> * edgePtr = m_mapingTable[_newBoxPos.m_row][_newBoxPos.m_line];
        vector<DoublePos>::iterator it_pos;
        it_pos = edgePtr->begin();
        while (it_pos != edgePtr->end()) {
            if(!CSokoban::getInstance()->beBox(it_pos->m_pos2))
            {
                beBox = false;
            }
            it_pos++;
        }
        if(beBox)
        {
            return false;
        }
        return true;
    }
}
bool CSurroundDetector::detect(CState & _boxState,CPosition &_oldBoxPos,CPosition & _newBoxPos)
{
    if(m_mapingTable[_newBoxPos.m_row][_newBoxPos.m_line]==NULL)
        return true;
    else
    {
        bool beBox = true;
        vector<DoublePos> * edgePtr = m_mapingTable[_newBoxPos.m_row][_newBoxPos.m_line];
        vector<DoublePos>::iterator it_pos;
        it_pos = edgePtr->begin();
        while (it_pos != edgePtr->end()) {
            if(!_boxState[it_pos->m_pos2.m_row][it_pos->m_pos2.m_line])
            {
                beBox = false;
            }
            it_pos++;
        }
        if(beBox)
        {
            return false;
        }
        return true;
    }

}
void CSurroundDetector::init()
{
    m_edges.clear();
    memset(m_mapingTable, 0, sizeof(vector<DoublePos> *[16][16]));
    bool edge_b = false;
    vector<DoublePos>  edge;
    int   targetCount = 0;
    // *       *
    // *********
    for(int row =2;row<g_length;row++)
    {
        for(int line =0;line<g_length;line++)
        {
            if(CSokoban::getInstance()->beWall(row-1, line) && CSokoban::getInstance()->beWall(row-2,line) )
            {
                edge_b = true;
            }
            if(edge_b)
            {
                if(CSokoban::getInstance()->beWall(row, line) && !CSokoban::getInstance()->beWall(row-1, line) && !CSokoban::getInstance()->beWall(row-2,line))
                {
                    edge.push_back(DoublePos(CPosition(row-1,line),CPosition(row-2,line)));
                }
                if(CSokoban::getInstance()->beTarget(row-1, line))
                {
                    targetCount++;
                }
                if(CSokoban::getInstance()->beTarget(row-2, line))
                {
                    targetCount++;
                }
                if(CSokoban::getInstance()->beWall(row-1, line) && CSokoban::getInstance()->beWall(row-2,line) && edge.size()>0)
                {
                    if(targetCount < edge.size())
                    {
                        m_edges.push_back(edge);
                        edge.clear();
                        targetCount  =0;
                    }
                }
                if(!CSokoban::getInstance()->beWall(row, line))
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
    // ********
    // *      *
    for(int row =0;row < g_length-2 ;row++)
    {
        for(int line =0;line < g_length;line++)
        {
            if( CSokoban::getInstance()->beWall(row+1, line) && CSokoban::getInstance()->beWall(row+2,line))
            {
                edge_b = true;
            }
            if(edge_b)
            {
                if(CSokoban::getInstance()->beWall(row, line) && !CSokoban::getInstance()->beWall(row+1, line) && !CSokoban::getInstance()->beWall(row+2,line))
                {
                    edge.push_back(DoublePos(CPosition(row+1,line), CPosition(row+2,line)));
                }
                if(CSokoban::getInstance()->beTarget(row+1,line))
                    targetCount++;
                if(CSokoban::getInstance()->beTarget(row+2,line))
                    targetCount++;
                if(CSokoban::getInstance()->beWall(row+1, line) && CSokoban::getInstance()->beWall(row+2,line)&& edge.size()>0 )
                {
                    if(targetCount < edge.size())
                    {
                        m_edges.push_back(edge);
                        edge.clear();
                        targetCount  =0;
                    }
                }
                if(!CSokoban::getInstance()->beWall(row, line))
                {
                    edge.clear();
                    targetCount  =0;
                    edge_b       =false;
                }
            }
        }
        edge.clear();
        targetCount = 0;
        edge_b      = false;
    }
    // **
    //  *
    //  *
    //  *
    //  *
    // **
    for(int line =2;line < g_length;line++)
    {
        for(int row =0;row < g_length ;row++)
        {
            if(CSokoban::getInstance()->beWall(row, line-1) && CSokoban::getInstance()->beWall(row,line-2))
            {
                edge_b = true;
            }
            if(edge_b)
            {
                if(CSokoban::getInstance()->beWall(row, line) && !CSokoban::getInstance()->beWall(row, line-1) && !CSokoban::getInstance()->beWall(row,line-2))
                {
                    edge.push_back( DoublePos(CPosition(row,line-1),CPosition(row,line-2)));
                }
                if(CSokoban::getInstance()->beTarget(row,line-1))
                    targetCount++;
                if(CSokoban::getInstance()->beTarget(row,line-2))
                    targetCount++;
                if(CSokoban::getInstance()->beWall(row, line-1) && edge.size()>0 &&CSokoban::getInstance()->beWall(row, line-2))
                {
                    if(targetCount < edge.size())
                    {
                        m_edges.push_back(edge);
                        edge.clear();
                        targetCount  =0;
                    }
                }
                if(!CSokoban::getInstance()->beWall(row, line))
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
    // **
    // *
    // *
    // *
    // *
    // **
    for(int line =0;line < g_length -2;line++)
    {
        for(int row =0;row < g_length ;row++)
        {
            
            if(CSokoban::getInstance()->beWall(row, line) && CSokoban::getInstance()->beWall(row, line+1))
            {
                edge_b = true;
            }
            if(edge_b)
            {
                if(CSokoban::getInstance()->beWall(row, line) && !CSokoban::getInstance()->beWall(row, line+1) && !CSokoban::getInstance()->beWall(row,line+2))
                {
                    edge.push_back(DoublePos(CPosition(row,line+1),CPosition(row,line+2)));
                }
                if(CSokoban::getInstance()->beTarget(row, line+1))
                    targetCount++;
                if(CSokoban::getInstance()->beTarget(row, line+2))
                    targetCount++;
                if(CSokoban::getInstance()->beWall(row, line+1)&& CSokoban::getInstance()->beWall(row,line+2) && edge.size()>0)
                {
                    if(targetCount < edge.size())
                    {
                        m_edges.push_back(edge);
                        edge.clear();
                        targetCount  =0;
                    }
                }
                if(!CSokoban::getInstance()->beWall(row, line))
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
    
    vector<vector<DoublePos>>::iterator it_edge = m_edges.begin();
    vector<DoublePos>::iterator it_pos;
    while (it_edge != m_edges.end()) {
        it_pos = it_edge->begin();
        while (it_pos != it_edge->end()) {
            m_mapingTable[it_pos->m_pos1.m_row][it_pos->m_pos1.m_line] = &(*it_edge);
            m_mapingTable[it_pos->m_pos2.m_row][it_pos->m_pos2.m_line] = &(*it_edge);
            it_pos++;
        }
        it_edge++;
    }
}
void CSurroundDetector::clearDectector()
{

}
