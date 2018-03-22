//
//  ISokobanDatasource.cpp
//  sokoban
//
//  Created by 张雨 on 2016/12/1.
//  Copyright © 2016年 张雨. All rights reserved.
//
#ifndef ISokobanDatasource_hpp
#define ISokobanDatasource_hpp
#include <stdio.h>
#include "CPosition.hpp"
#include "common.hpp"
class ISokobanDataSource
{
public:
    virtual  SokobanData GetSokobanData()=0;
    virtual void InitWithSokobanData(SokobanData & _sokobanData)=0;
    virtual long HashValue()=0;
};
#endif
