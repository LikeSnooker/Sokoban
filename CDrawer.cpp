//
//  CDrawer.cpp
//  sokoban
//
//  Created by 张雨 on 2016/12/5.
//  Copyright © 2016年 张雨. All rights reserved.
//

#include "CDrawer.hpp"

void CDrawer::DrawGame(SokobanData _sokobanData,CGContextRef _context,CGRect _rect,bool beLeaveANote)
{
    float offset_x = _rect.origin.x;
    float offset_y = _rect.origin.y;
    float edge     = _rect.size.width;
    EdgeInsets insets = GetInsets(_sokobanData);
    enumerated(16, 16, [&](int row,int line){
        CGRect rect = CGRectMake( (beLeaveANote?line:line-insets.left) * edge + offset_x , (beLeaveANote?row:row-insets.up) * edge +offset_y,edge-2,edge-2);
        switch (_sokobanData.m_layout[row][line]) {
            case WALL:
                CDrawTool::DrawWall       (_context, rect);
                break;
            case BOX:
                CDrawTool::DrawBox        (_context, rect);
                break;
            case TARGET:
                CDrawTool::DrawTarget     (_context, rect);
                break;
            case BOXONTARGET:
                CDrawTool::DrawBoxOnTarget(_context, rect);
                break;
            default:
                break;
        }
    });
    CPosition manP = _sokobanData.m_manPosition;
    CDrawTool::DrawMan(_context,CGRectMake(manP.m_line * edge +offset_x,manP.m_row* edge + offset_y,edge-2,edge-2));
}
