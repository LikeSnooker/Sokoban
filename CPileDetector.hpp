//
//  CPileDetector.h
//  sokoban
//
//  Created by 张雨 on 15/9/9.
//  Copyright (c) 2015年 张雨. All rights reserved.
//

#ifndef __sokoban__CPileDetector__
#define __sokoban__CPileDetector__

#include <stdio.h>
#include "CDetector.hpp"
class CPileDetector:public CDetector
{
public:
    bool detect();
    bool detect(CState &_state);
    bool detect(CPosition & _oldBoxPos,CPosition & _newBoxPos);
    bool detect(CState & _boxState,CPosition &_oldBoxPos,CPosition & _newBoxPos);
    void init  ();
    void clearDectector ();
private:
    int m_wallMatrix[16];
    int m_targetMatrix[16];
    int m_up;
    int m_left;
    int m_down;
    int m_right;
};
#endif /* defined(__sokoban__CPileDetector__) */
