//
//  CZigzagDetector.hpp
//  sokoban
//
//  Created by 张雨 on 15/12/23.
//  Copyright © 2015年 张雨. All rights reserved.
//

#ifndef CZigzagDetector_hpp
#define CZigzagDetector_hpp
#include "CDetector.hpp"
#include <stdio.h>
//判断 #*
//     *#
class CZigzagDetector :public CDetector
{
private:
    struct pos_pair
    {
        CPosition m_first;
        CPosition m_second;
        pos_pair(CPosition _pos1,CPosition _pos2)
        {
            m_first  = _pos1;
            m_second = _pos2;
        }
    };
    vector<pos_pair> pos_pairs;
public:
    bool detect();
    bool detect(CState &_state);
    bool detect(CPosition & _oldBoxPos,CPosition & _newBoxPos);
    bool detect(CState & _boxState,CPosition &_oldBoxPos,CPosition & _newBoxPos);
    void init();
    void clearDectector ();
};
#endif /* CZigzagDetector_hpp */
