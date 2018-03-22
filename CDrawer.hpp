//
//  CDrawer.hpp
//  sokoban
//
//  Created by 张雨 on 2016/12/5.
//  Copyright © 2016年 张雨. All rights reserved.
//

#ifndef CDrawer_hpp
#define CDrawer_hpp
#import <UIKit/UIKit.h>
#include <stdio.h>
#include "ISokobanDatasource.hpp"
#include "CDrawTool.hpp"
class CDrawer
{
public:
    static void DrawGame(SokobanData _sokobanData,CGContextRef _context,CGRect _rect,bool beLeaveANote);
};
#endif /* CDrawer_hpp */
