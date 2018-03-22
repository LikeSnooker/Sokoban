//
//  CSurroundDetector.hpp
//  sokoban
//
//  Created by 张雨 on 15/10/20.
//  Copyright © 2015年 张雨. All rights reserved.
//

#ifndef CSurroundDetector_hpp
#define CSurroundDetector_hpp

#include <stdio.h>
#include <vector>
#include "CPosition.hpp"
#include "CDetector.hpp"
using namespace std;
class CSurroundDetector :public CDetector
{
private:
    struct DoublePos
    {
        CPosition m_pos1;
        CPosition m_pos2;
        DoublePos(CPosition _pos1,CPosition _pos2)
        {
            m_pos1 = _pos1;
            m_pos2 = _pos2;
        }
    };
public:
    CSurroundDetector();
private:
    vector<vector<DoublePos>> m_edges;
    vector<DoublePos> * m_mapingTable[16][16];
public:
    bool detect        ();
    bool detect(CState &_state);
    bool detect        (CPosition & _oldBoxPos,CPosition & _newBoxPos);
    bool detect(CState & _boxState,CPosition &_oldBoxPos,CPosition & _newBoxPos);
    void init          ();
    void clearDectector();
};
#endif /* CSurroundDetector_hpp */
