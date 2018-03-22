//
//  CWeltDetector.h
//  sokoban
//
//  Created by 张雨 on 15/9/8.
//  Copyright (c) 2015年 张雨. All rights reserved.
//

#ifndef __sokoban__CWeltDetector__
#define __sokoban__CWeltDetector__

#include <stdio.h>
#include <vector>
using std::vector;
#include "CDetector.hpp"
#include "CPosition.hpp"
class CWeltDetector: public CDetector // 靠边检测器
{
private:
    struct Edge
    {
        vector<CPosition> m_positions;
        int          m_targetCount;
        Edge(vector<CPosition> & _positions ,int _targetCount)
        {
            m_positions   = _positions;
            m_targetCount = _targetCount;
        }
    };
public:
    CWeltDetector();
    bool detect         ();
    bool detect         (CState &_state);
    bool detect         (CPosition & _oldBoxPos,CPosition & _newBoxPos);
    bool detect         (CState & _boxState,CPosition &_oldBoxPos,CPosition & _newBoxPos);
    void init           ();
    void clearDectector ();
private:
    Edge * m_mapingTable[16][16];
    vector<Edge>  m_edges;
};
#endif /* defined(__sokoban__CWeltDetector__) */
