//
//  CDrawTool.cpp
//  sokoban
//
//  Created by 张雨 on 15/9/22
//  Copyright © 20015年 张雨. All rights reserved.
//

#include "CDrawTool.hpp"
#include "common.hpp"
extern int g_length;
float CDrawTool::_lineWidth = 1.5;
void CDrawTool::DrawEdge(CGContextRef _context,CGRect _rect)
{
    float width  = _rect.size.width;
    float height = _rect.size.height;
    float x      = _rect.origin.x;
    float y      = _rect.origin.y;
    CGContextMoveToPoint   (_context, x                     , y + _lineWidth/2.0);
    CGContextAddLineToPoint(_context, x+width               , y + _lineWidth/2.0);
    CGContextMoveToPoint   (_context, x+_lineWidth/2.0      , y);
    CGContextAddLineToPoint(_context, x+_lineWidth/2.0      , y+height);
    
    CGContextMoveToPoint   (_context, x+width - _lineWidth/2.0, y+height);
    CGContextAddLineToPoint(_context, x+width - _lineWidth/2.0, y);
    
    CGContextMoveToPoint   (_context, x+width               , y+height -_lineWidth/2.0);
    CGContextAddLineToPoint(_context, x                     , y+height-_lineWidth/2.0);
}
void CDrawTool::DrawSelectStyle(CGContextRef _context,CGRect _rect)
{
    CGRect newRect = CGRectMake(_rect.origin.x-2.0, _rect.origin.y-2.0, _rect.size.width+4.0, _rect.size.height+4.0);
    DrawEdge(_context, newRect);
}
void CDrawTool::DrawWall(CGContextRef _context ,CGRect _rect,bool _selectedStyle)
{
    CGContextSaveGState  (_context);
    if(_selectedStyle)
    {
        CDrawTool::DrawSelectStyle      (_context, _rect);
    }
    CGContextSetLineWidth(_context, _lineWidth);
    float width  = _rect.size.width;
    float height = _rect.size.height;
    float x      = _rect.origin.x;
    float y      = _rect.origin.y;
    
    CDrawTool::DrawEdge(_context,_rect);
    
    CGContextMoveToPoint   (_context, x + width/4, y);
    CGContextAddLineToPoint(_context, x + width/4, y+height);
    
    CGContextMoveToPoint   (_context, x + width/2.0, y);
    CGContextAddLineToPoint(_context, x + width/2.0, y+height);
    
    CGContextMoveToPoint   (_context, x + width*3/4, y);
    CGContextAddLineToPoint(_context, x + width*3/4, y+height);
    
    CGContextMoveToPoint   (_context, x,       y+height/4);
    CGContextAddLineToPoint(_context, x+width, y+height/4);
    
    CGContextMoveToPoint   (_context, x,       y+height/2.0);
    CGContextAddLineToPoint(_context, x+width, y+height/2.0);
    
    CGContextMoveToPoint   (_context, x,       y+height*3/4);
    CGContextAddLineToPoint(_context, x+width, y+height*3/4);

    CGContextSetStrokeColorWithColor(_context,WALL_COLOR);
    CGContextStrokePath(_context);
    
    CGContextRestoreGState(_context);
}
void CDrawTool::DrawBox(CGContextRef _context ,CGRect _rect,bool _selectedStyle)
{
    CGContextSaveGState(_context);
    if(_selectedStyle)
    {
        DrawSelectStyle      (_context, _rect);
    }
    CGContextSetLineWidth(_context, _lineWidth);
    
    int width  = _rect.size.width;
    int height = _rect.size.height;
    int x      = _rect.origin.x;
    int y      = _rect.origin.y;
    
    DrawEdge(_context,_rect);
    CGContextMoveToPoint   (_context, x + width/2.0 + _lineWidth/2.0 , y + _lineWidth/2.0);
    CGContextAddLineToPoint(_context, x + width/2.0 + _lineWidth/2.0 , y+height + _lineWidth/2.0);
    CGContextMoveToPoint   (_context, x             + _lineWidth/2.0 , y + height/2.0 + _lineWidth/2.0);
    CGContextAddLineToPoint(_context, x+width       + _lineWidth/2.0 , y + height/2.0 + _lineWidth/2.0);
    
    CGContextSetStrokeColorWithColor(_context,BOX_COLOR);
    CGContextStrokePath    (_context);
    
    CGContextRestoreGState (_context);
}
void CDrawTool::DrawMan(CGContextRef _context ,CGRect _rect,bool _selectedStyle)
{
    CGContextSaveGState    (_context);
    if(_selectedStyle)
    {
        DrawSelectStyle    (_context, _rect);
    }
    CGContextSetLineWidth  (_context, 1.0);
    CGContextSetStrokeColorWithColor(_context,MAN_COLOR );
    
    int width  = _rect.size.width;
    int height = _rect.size.height;
    int x      = _rect.origin.x + width/2.0;
    int y      = _rect.origin.y + height/2.0;
    CGContextMoveToPoint   (_context, x+width/2.0-2.0, y);
    CGContextAddArc        (_context, x, y, width/2.0 - 2.0, 0, 2.0 * MATH_PAI, 0);
    CGContextStrokePath    (_context);
    CGContextRestoreGState (_context);
}
void CDrawTool::DrawTarget(CGContextRef _context ,CGRect _rect,bool _selectedStyle)
{
    CGContextSaveGState    (_context);
    if(_selectedStyle)
    {
        DrawSelectStyle      (_context, _rect);
    }
    CGContextSetLineWidth  (_context, _lineWidth);
    CGContextSetStrokeColorWithColor(_context,TARGET_COLOR);
    int width  = _rect.size.width;
    int height = _rect.size.height;
    int x      = _rect.origin.x;
    int y      = _rect.origin.y;
    
    CGContextMoveToPoint   (_context, x + _lineWidth       , y + _lineWidth     );
    CGContextAddLineToPoint(_context, x+width  , y+height);
    
    CGContextMoveToPoint   (_context, x+width, y +_lineWidth      );
    CGContextAddLineToPoint(_context, x+_lineWidth        , y+height);
    
    CGContextStrokePath    (_context);
    
    CGContextRestoreGState (_context);
}
void CDrawTool::DrawBoxOnTarget(CGContextRef _context ,CGRect _rect,bool _selectedStyle)
{
    if(_selectedStyle)
    {
        DrawSelectStyle    (_context, _rect);
    }
    DrawTarget(_context, _rect);
    DrawBox   (_context, _rect);
}
void CDrawTool::DrawFloor(CGContextRef _context ,CGRect _rect,bool _selectedStyle)
{

    if(_selectedStyle)
    {
        DrawSelectStyle      (_context, _rect);
    }
    CGContextSaveGState      (_context);
    CGContextSetLineWidth    (_context, _lineWidth);
    CGContextSetStrokeColorWithColor(_context, WALL_COLOR);
    DrawEdge                 (_context, _rect);
    CGContextStrokePath      (_context);
    CGContextRestoreGState   (_context);
}
void CDrawTool::DrawCoordinate (CGContextRef _context ,CGRect _rect,int _row,int _line)
{
    CGContextSaveGState(_context);
    UIFont * font = [UIFont systemFontOfSize:8.0];
    [ [NSString stringWithFormat:@"%d",_row]  drawAtPoint:CGPointMake(_rect.origin.x -_lineWidth,_rect.origin.y-_lineWidth) withAttributes:@{NSFontAttributeName:font}];
    [ [NSString stringWithFormat:@"%d",_line] drawAtPoint:CGPointMake(_rect.origin.x+_rect.size.width/2.0-_lineWidth,_rect.origin.y+_rect.size.height/2.0-_lineWidth) withAttributes:@{NSFontAttributeName:font}];
    CGContextRestoreGState(_context);
}
void CDrawTool::DrawGuide(CGContextRef _context,CGRect _rect)
{
    float offset_x   = _rect.origin.x;
    float offset_y   = _rect.origin.y;
    float cell_width = _rect.size.width/16;
    ////////画虚线框
    CGContextSaveGState    (_context);
    CGContextSetStrokeColor(_context,CGColorGetComponents(GUIDE_COLOR));
    CGContextSetLineWidth  (_context, 0.5);
    CGFloat lenghts[] ={3,3};
    CGContextSetLineDash(_context, 0, lenghts, 2.0);
    
    for(int row =0;row < g_length+1;row++)
    {
        CGContextMoveToPoint   (_context,offset_x -1+ row * cell_width,offset_y -1+ 0);
        CGContextAddLineToPoint(_context,offset_x -1+ row * cell_width,offset_y -1+ cell_width * g_length);
        
        CGContextMoveToPoint   (_context,offset_x -1+ 0,offset_y-1+ row * cell_width);
        CGContextAddLineToPoint(_context,offset_x -1+ cell_width * g_length,offset_y-1+ row * cell_width);
    }
    CGContextStrokePath    (_context);
    CGContextRestoreGState (_context);
    
    //////
}

