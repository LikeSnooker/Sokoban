//
//  CHashMaker.hpp
//  sokoban
//
//  Created by 张雨 on 15/10/19.
//  Copyright © 2015年 张雨. All rights reserved.
//

#ifndef CHashMaker_hpp
#define CHashMaker_hpp

#include <stdio.h>
class CHashMaker
{
public:
    CHashMaker();
public:
    void init();
    long makeHash();
private:
    unsigned char m_mapping[20][20];
};
#endif /* CHashMaker_hpp */
