//
//  CFileAdapter.hpp
//  sokoban
//
//  Created by 张雨 on 15/10/8.
//  Copyright © 2015年 张雨. All rights reserved.
//

#ifndef CFileAdapter_hpp
#define CFileAdapter_hpp
#include "CSokoban.hpp"
class CFileAdapter
{
public:
    static CFileAdapter * getInstance();
private:
    static CFileAdapter* m_instance;
    CFileAdapter(const CFileAdapter & fileAdapter);
    CFileAdapter();
public:
    bool save(NSString * _fileName);
    bool read(NSString * _fileName);
};
#endif /* CFileAdapter_hpp */
