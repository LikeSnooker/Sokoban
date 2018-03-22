//
//  IDataAdpter.hpp
//  sokoban
//
//  Created by 张雨 on 2016/12/5.
//  Copyright © 2016年 张雨. All rights reserved.
//

#ifndef IDataAdpter_hpp
#define IDataAdpter_hpp

#include <stdio.h>
class IDataAdpter
{
public:
    char * save();
    void read(char *_bytes,int _length);
};
#endif /* IDataAdpter_hpp */
