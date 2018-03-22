//
//  function.cpp
//  sokoban
//
//  Created by 张雨 on 15/11/27.
//  Copyright © 2015年 张雨. All rights reserved.
//

#include "function.hpp"

bool checkBit(int _xx,int _line)
{
    return _xx  & (1<< ( 19 - _line));
}
bool checkBit(int _matrix[20],int _row,int _line)
{
    return _matrix[_row] & (1<< (19-_line));
}
void setBit  (int _matrix[20],int _row,int _line)
{
    _matrix[_row] |= (1<<(19-_line));
}
SokobanData ChangeToSokobanData(int _boxs[20],int _targets[20],int _walls[20],CPosition m_manP)
{
    SokobanData result;
    for(int row =0;row<16;row++)
    {
        for(int line =0;line<16;line++)
        {
            if(checkBit(_walls[row],line))
            {
                result.m_layout[row][line] = WALL;
            }
            if( checkBit(_boxs[row],line) && !checkBit(_targets[row],line) )
            {
                result.m_layout[row][line] = BOX;
            }
            if( !checkBit(_boxs[row],line) && checkBit(_targets[row],line) )
            {
                result.m_layout[row][line] = TARGET;
            }
            if( checkBit(_boxs[row],line) && checkBit(_targets[row],line) )
            {
                result.m_layout[row][line] = BOXONTARGET;
            }
        }
    }
    result.m_manPosition = m_manP;
    return result;
}
