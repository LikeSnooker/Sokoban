//
//  DeadangleDetector.h
//  sokoban
//
//  Created by 张雨 on 15/9/11.
//  Copyright (c) 2015年 张雨. All rights reserved.
//

#ifndef __sokoban__DeadangleDetector__
#define __sokoban__DeadangleDetector__

#include <stdio.h>
#include <vector>
#include "CDetector.hpp"
#include "CPosition.hpp"
using namespace std;
class CDeadangleDetector:public CDetector
{
public:
    bool detect        ();
    bool detect(CState &_state);
    bool detect        (CPosition & _oldBoxPos,CPosition & _newBoxPos);
    bool detect(CState & _boxState,CPosition &_oldBoxPos,CPosition & _newBoxPos);
    void init          ();
    void clearDectector();
private:
    vector<CPosition> m_deadAngles;
    bool m_dead[16][16];
};
#endif /* defined(__sokoban__DeadangleDetector__) */
