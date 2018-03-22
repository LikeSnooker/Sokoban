//
//  algorithm.cpp
//  sokoban
//
//  Created by 张雨 on 2016/11/28.
//  Copyright © 2016年 张雨. All rights reserved.
//

#include <stdio.h>
#include "CPosition.hpp"
//求解相关的算法
#include <vector>
#include <queue>
#include <ext/hash_map>
using __gnu_cxx::hash_map;
using __gnu_cxx::binary_function;
using namespace std;
#define abs(x) ( (x) < 0 ? (-x) : (x) )


struct Node
{
    CPosition m_positions[16];
    int count;
    int h;
    int g;
    int f;
};
const int dirs[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};
struct Layout
{
    bool     matrix[16][16];//二维数组的方式保存
};

bool HavePath(Layout _wallLayout,Layout _boxLayout,Layout _targetLayout,CPosition _manOrigin,CPosition _manDestination)
{
    return true;
}
bool BeImpasse(Layout _wallLayout,Layout _boxLayout,Layout _targetLayout,CPosition _manPosition)
{
    return false;
}
Node GetBoxPositions(Layout _boxLayout)
{
    Node result;
    int boxCount =0;
    for(int row =0;row<16;row++)
    {
        for(int line =0;line < 16;line++)
        {
            if(_boxLayout.matrix[row][line])
            {
                result.m_positions[boxCount].m_row = row;
                result.m_positions[boxCount].m_line= line;
                boxCount++;
            }
        }
    }
    result.count = boxCount;
    return result;
}
void MoveManByDirection(Layout _wallLayout,Layout& _boxLayout,Layout _targetLayout,CPosition & _manPosition,int _direction)
{
    CPosition manGo;
    manGo.m_row  = _manPosition.m_row  += dirs[_direction][0];
    manGo.m_line = _manPosition.m_line += dirs[_direction][1];
    if(!(_wallLayout.matrix[manGo.m_row][manGo.m_line] || _boxLayout.matrix[manGo.m_row][manGo.m_line]))
    {
        _manPosition = manGo;
        return;
    }
    if(_boxLayout.matrix[manGo.m_row][manGo.m_line])
    {
        CPosition boxGo;
        boxGo.m_row  = manGo.m_row += dirs[_direction][0];
        boxGo.m_line = manGo.m_line+= dirs[_direction][1];
        if(!(_wallLayout.matrix[boxGo.m_row][boxGo.m_line] || _boxLayout.matrix[boxGo.m_row][boxGo.m_line]))
        {
            _manPosition = manGo;
            _boxLayout.matrix[manGo.m_row][manGo.m_line] = false;
            _boxLayout.matrix[boxGo.m_row][boxGo.m_line] = true;
        }
    }
}
bool operator < (const Node _node1,const Node _node2)
{
    return _node1.f > _node2.f;
}
int Heuristic(CPosition _boxs[16],CPosition _targets[16],int count)
{
    int sum = 0;
    for(int m =0 ;m < count ;m++)
    {
        sum += abs(_boxs[m].m_row  - _boxs[m].m_row);
        sum += abs(_boxs[m].m_line - _boxs[m].m_line);
    }
    return sum;
}
long RSHash(const Node & _node)
{
    int b     = 378551;
    int a     = 63689;
    long hash = 0;
    for(int i = 0; i < _node.count; i++)
    {
        hash = hash * a + _node.m_positions[i].m_row;
        a    = a * b;
        //
        hash = hash * a + _node.m_positions[i].m_line;
        a    = a * b;
        
    }
    return hash;
}
struct compare_state
{
    bool operator()(const Node& _node1 ,const Node & _node2) const
    {
        return _node1.m_positions == _node2.m_positions;
    }
};
struct hash_state{
    size_t operator()(const Node & _node) const
    {
        return RSHash(_node);
    }
};


hash_map<Node,bool,hash_state,compare_state> visited;
priority_queue<Node> open_list;

void AStar()
{
    Layout boxLayout,wallLayout,targetLayout;
    CPosition manPosition;
    Node t,s;
    while(!open_list.empty())
    {
        t = open_list.top();
        open_list.pop();
        visited[t] = true;
        Node temp = GetBoxPositions(boxLayout);
        for(int boxID = 0 ;boxID < t.count;boxID++)
        {
            for(int direction = 0 ;direction < 4;direction++)
            {
                int op_direction = 3 - direction;//
                CPosition manGo;
                manGo.m_row  = temp.m_positions[boxID].m_row + dirs[op_direction][0];
                manGo.m_line = temp.m_positions[boxID].m_line+ dirs[op_direction][1];
                
                if(! ( boxLayout.matrix[manGo.m_row][manGo.m_line] || wallLayout.matrix[manGo.m_row][manGo.m_line]))
                {
                    manPosition = manGo;
                    MoveManByDirection(wallLayout, boxLayout, targetLayout, manPosition, direction);
                }
            }
        }
    }
}

