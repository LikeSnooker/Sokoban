//
//  CLongBool.hpp
//  sokoban
//
//  Created by 张雨 on 15/10/19.
//  Copyright © 2015年 张雨. All rights reserved.
//

#ifndef CLongBool_hpp
#define CLongBool_hpp

#include <stdio.h>
#include <cstring>
class CLongBool
{
private:
    CLongBool();
public:
    CLongBool(long _maxValue);
    ~CLongBool();
private:
    int * m_data;
    long  m_maxValue;
public:
    void setBoolOnSet(long _set);
    bool beBoolOnSet (long _set);
};
#endif /* CLongBool_hpp */
