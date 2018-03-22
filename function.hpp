//
//  function.hpp
//  sokoban
//
//  Created by 张雨 on 15/11/27.
//  Copyright © 2015年 张雨. All rights reserved.
//

#ifndef function_hpp
#define function_hpp

#include <stdio.h>
#include "common.hpp"
bool checkBit(int _xx,int _line);
bool checkBit(int _matrix[20],int _row,int _line);
void setBit  (int _matrix[20],int _row,int _line);
SokobanData ChangeToSokobanData(int _boxs[20],int _targets[20],int _walls[20],CPosition _manP);
#endif /* function_hpp */
