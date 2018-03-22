//
//  CDrawer.hpp
//  sokoban
//
//  Created by 张雨 on 15/9/22.
//  Copyright © 2015年 张雨. All rights reserved.
//

#ifndef CDrawTool_hpp
#define CDrawTool_hpp
#import <UIKit/UIKit.h>
#include <stdio.h>
#include "CSokoban.hpp"
#include "ISokobanDatasource.hpp"
#define MATH_PAI 3.1415926
//石板灰
#define WALL_COLOR   [[UIColor colorWithRed:112/255.0 green:118/255.0  blue:144/255.0  alpha:1.0] CGColor]

#define BOX_COLOR    [[UIColor colorWithRed:255/255.0 green:235/255.0  blue:205/255.0  alpha:1.0] CGColor]

#define TARGET_COLOR [[UIColor colorWithRed:2220/255.0 green:20/255.0  blue:60/255.0  alpha:1.0] CGColor]

#define FILL_COLOR   [[UIColor colorWithRed:255/255.0 green:255/255.0  blue:255/255.0  alpha:1.0] CGColor]
#define MAN_COLOR    [[UIColor colorWithRed:218/255.0 green:165/255.0  blue:105/255.0  alpha:1.0] CGColor]

#define GUIDE_COLOR  [[UIColor colorWithRed:220/255.0 green:220/255.0  blue:220/255.0  alpha:1.0] CGColor]

class CDrawTool
{
public:
    static void DrawWall       (CGContextRef _context ,CGRect _rect,bool _selectedStyle = false);
    static void DrawBox        (CGContextRef _context ,CGRect _rect,bool _selectedStyle = false);
    static void DrawMan        (CGContextRef _context ,CGRect _rect,bool _selectedStyle = false);
    static void DrawTarget     (CGContextRef _context ,CGRect _rect,bool _selectedStyle = false);
    static void DrawBoxOnTarget(CGContextRef _context ,CGRect _rect,bool _selectedStyle = false);
    static void DrawFloor      (CGContextRef _context ,CGRect _rect,bool _selectedStyle = false);
    static void DrawCoordinate (CGContextRef _context ,CGRect _rect,int _row,int _line);
    static void DrawGuide(CGContextRef _context,CGRect _rect);
private:
    static float _lineWidth;
    static void DrawEdge       (CGContextRef _context ,CGRect _rect);
    static void DrawSelectStyle(CGContextRef _context ,CGRect _rect);
};


#endif /* CDrawer_hpp */
