//
//  CReasoningDetector.hpp
//  sokoban
//
//  Created by 张雨 on 2017/1/11.
//  Copyright © 2017年 张雨. All rights reserved.
//

#ifndef CReasoningDetector_hpp
#define CReasoningDetector_hpp

#include <stdio.h>
#include "CDetector.hpp"
class CReasoningDetector : public CDetector //推理式检测，当前布局 在不考虑其他箱子存在的情况下，这个箱子是否是活的
{
public:
    bool detect();
    bool detect(CState &_state);
    bool detect(CPosition & _oldBoxPos,CPosition & _newBoxPos);
    bool detect(CState & _boxState,CPosition &_oldBoxPos,CPosition & _newBoxPos);
    void init();
    void clearDectector ();
};
#endif /* CReasoningDetector_hpp */
