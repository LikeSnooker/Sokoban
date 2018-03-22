//
//  common.cpp
//  sokoban
//
//  Created by 张雨 on 16/7/21.
//  Copyright © 2016年 张雨. All rights reserved.
//

#include "common.hpp"
#define MIN(x,y) (x)<(y)?(x):(y)
#define MAX(x,y) (x)>(y)?(x):(y)
EdgeInsets GetInsets(SokobanData _data)
{
    EdgeInsets edge_insets;
    edge_insets.left  = 15;
    edge_insets.right = 0;
    edge_insets.up    = 15;
    edge_insets.down  = 0;
    enumerated(16,16,[&](int _row,int _line){
        if(! (_data.m_layout[_row][_line]==FLOOR))
        {
            edge_insets.left  = MIN(edge_insets.left,_line);
            edge_insets.right = MAX(edge_insets.right,_line);
            edge_insets.up    = MIN(edge_insets.up, _row);
            edge_insets.down  = MAX(edge_insets.down,_row);
        }
        
    } );
    return edge_insets;

}
int EdgeInsets::width()
{
    int result = right - left+1;
    return result > 0 ?result:0;
}
int EdgeInsets::height()
{
    int result = down - up+1;
    return result > 0 ?result:0;
}
