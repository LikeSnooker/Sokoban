//
//  common.h
//  sokoban
//
//  Created by 张雨 on 16/5/6.
//  Copyright © 2016年 张雨. All rights reserved.
//

#ifndef common_h
#define common_h
#include <iostream>
#include "CPosition.hpp"
struct EdgeInsets //表示一个布局中上下左右的间隙
{
    int up;
    int left;
    int down;
    int right;
    int width();
    int height();
};
struct Crossroads
{
    bool Up;
    bool Down;
    bool Left;
    bool Right;
    Crossroads (bool _up,bool _down,bool _left,bool _right)
    {
        Up    = _up;
        Down  = _down;
        Left  = _left;
        Right = _right;
    }
};
enum SokobanObject
{
    WALL,
    BOX,
    TARGET,
    BOXONTARGET,
    FLOOR
};
class PositionNode
{
public:
    CPosition      m_position;
    PositionNode * m_next;
    PositionNode (CPosition & _pos,PositionNode * _next)
    {
        m_position = _pos;
        m_next     = _next;
    }
    PositionNode (CPosition & _pos)
    {
        m_position = _pos;
        m_next     = NULL;
    }
    PositionNode ()
    {
        m_position = CPosition(0,0);
        m_next     = NULL;
    }
};
class PositionNodeList
{
private:
    PositionNode ** m_nodes;
    long            m_n;
public:
    PositionNodeList(long _n)
    {
        m_nodes = new PositionNode*[_n];
        memset(m_nodes,0,sizeof(PositionNode*) * _n);
        m_n     = _n;
    }
    bool Resize(long _n)
    {
        if(m_nodes != 0)
        {
            delete []m_nodes;
        }
        m_nodes = new PositionNode*[_n];
        memset(m_nodes,0,sizeof(PositionNode*) * _n);
        m_n     = _n;
        return true;
    }
    ~PositionNodeList()
    {
        if(m_nodes != 0)
            delete []m_nodes;
    }
    typedef PositionNode * PNP;
    PNP operator[] (long _index)
    {
        if(_index < m_n)
        {
            return m_nodes[_index];
        }
        return 0;
    }
    bool AddNode(PositionNode & _node,long _hashvalue)
    {
        if(_hashvalue <0 || _hashvalue > m_n)
            return false;
        else
        {
            if(m_nodes[_hashvalue] == 0)
                m_nodes[_hashvalue] = new PositionNode(_node);
            insert(m_nodes[_hashvalue],_node);
            return true;
        }
    }
private:
    void insert(PNP _node,PositionNode & _newNode)
    {
        while(_node->m_next != 0)
        {
            _node = _node->m_next;
        }
        _node->m_next = new PositionNode(_newNode);
    }
};
template <typename Func>
void enumerated(int _row,int _line,Func _func)
{
    for(int row = 0;row < _row;row++)
    {
        for(int line =0;line<_line;line++)
        {
            _func(row,line);
        }
    }
}
struct SokobanData
{
    SokobanObject m_layout[16][16];
    CPosition     m_manPosition;
    SokobanData()
    {
        for(int row =0 ;row<16;row++)
        {
            for(int line = 0;line <16;line++)
            {
                m_layout[row][line] = FLOOR;
            }
        }
    }
};

EdgeInsets GetInsets(SokobanData _data);
#endif /* common_h */
