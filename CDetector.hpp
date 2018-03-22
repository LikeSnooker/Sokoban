//
//  CDetector.h
//  sokoban
//
//  Created by 张雨 on 15/9/8.
//  Copyright (c) 2015年 张雨. All rights reserved.
//

#ifndef __sokoban__CDetector__
#define __sokoban__CDetector__

#include <stdio.h>
#include "CSokoban.hpp"
class CDetector
{
public:
    virtual bool detect()=0;
    virtual bool detect(CState &_state)=0;
    virtual bool detect(CPosition &_oldBoxPos,CPosition & _newBoxPos)=0;
    virtual bool detect(CState & _boxState,CPosition &_oldBoxPos,CPosition & _newBoxPos)=0;
    virtual void init()=0;
    virtual void clearDectector()=0;
};
#endif /* defined(__sokoban__CDetector__) */
