//
//  CDetector.cpp
//  sokoban
//
//  Created by 张雨 on 15/9/8.
//  Copyright (c) 2015年 张雨. All rights reserved.
//

#include "CDetector.hpp"
bool CSokoban::beAlive() const
{
    for(auto it = m_detectors.begin();it!=m_detectors.end();it++)
    {
        if(! (*it)->detect() )
        {
            return false;
        }
    }
    return true;
}
bool CSokoban::beAlive(CState &_state)const
{
    for(auto it = m_detectors.begin();it!=m_detectors.end();it++)
    {
        if(! (*it)->detect(_state) )
        {
            return false;
        }
    }
    return true;
}
bool CSokoban::beAlive(CPosition & _oldBoxPos,CPosition &_newBoxPos)const
{
    for(auto it = m_detectors.begin();it!=m_detectors.end();it++)
    {
        if(! (*it)->detect(_oldBoxPos,_newBoxPos) )
        {
            return false;
        }
    }
    return true;
}
bool CSokoban::beAlive(CState & _boxState,CPosition & _oldBoxPos,CPosition & _newBoxPos)const
{
    for(auto it = m_detectors.begin();it!=m_detectors.end();it++)
    {
        if(! (*it)->detect(_boxState,_oldBoxPos,_newBoxPos) )
        {
            return false;
        }
    }
    return true;
}
void CSokoban::initAllDetectors()
{
    for(auto it = m_detectors.begin();it!=m_detectors.end();it++)
    {
        (*it)->init();
    }
}
