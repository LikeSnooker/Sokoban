//
//  CPileDetector.cpp
//  sokoban
//
//  Created by 张雨 on 15/9/9.
//  Copyright (c) 2015年 张雨. All rights reserved.
//

#include "CPileDetector.hpp"
extern int g_length;
bool CPileDetector::detect(CPosition & _oldBoxPos,CPosition &_newBoxPos)
{
    bool U_N_P  = false;
    bool D_N_P  = false;
    bool L_N_P  = false;
    bool R_N_P  = false;
    bool LU_N_P = false;
    bool LD_N_P = false;
    bool RU_N_P = false;
    bool RD_N_P = false;
    bool Z_N_P  = false;
    Z_N_P       = !CSokoban::getInstance()->beTarget(_newBoxPos);
    
    bool U  = false;
    bool L  = false;
    bool D  = false;
    bool R  = false;
    bool LU = false;
    bool LD = false;
    bool RU = false;
    bool RD = false;
    
    
    CPosition U_P  = CPosition(_newBoxPos.m_row-1,_newBoxPos.m_line);
    CPosition D_P  = CPosition(_newBoxPos.m_row+1,_newBoxPos.m_line);
    CPosition L_P  = CPosition(_newBoxPos.m_row  ,_newBoxPos.m_line-1);
    CPosition R_P  = CPosition(_newBoxPos.m_row  ,_newBoxPos.m_line+1);
    CPosition LU_P = CPosition(_newBoxPos.m_row-1,_newBoxPos.m_line-1);
    CPosition LD_P = CPosition(_newBoxPos.m_row+1,_newBoxPos.m_line-1);
    CPosition RU_P = CPosition(_newBoxPos.m_row-1,_newBoxPos.m_line+1);
    CPosition RD_P = CPosition(_newBoxPos.m_row+1,_newBoxPos.m_line+1);
    /////////////////////// 左上角
    if(CSokoban::getInstance()->beBox(U_P))
    {
        U = true;
        U_N_P = !CSokoban::getInstance()->beTarget(U_P);
    }
    if(CSokoban::getInstance()->beWall(U_P))
    {
        U = true;
    }
    
    if(CSokoban::getInstance()->beBox(L_P))
    {
        L = true;
        L_N_P = !CSokoban::getInstance()->beTarget(L_P);
    }
    if(CSokoban::getInstance()->beWall(L_P))
    {
        L = true;
    }
    
    if(CSokoban::getInstance()->beBox(LU_P))
    {
        LU = true;
        LU_N_P = !CSokoban::getInstance()->beTarget(LU_P);
    }
    if(CSokoban::getInstance()->beWall(LU_P))
    {
        LU = true;
    }
    if(L && U && LU && (U_N_P || L_N_P || LU_N_P || Z_N_P))
        return false;
    //////////////////////// 左下角
    if(CSokoban::getInstance()->beBox(D_P))
    {
        D = true;
        D_N_P = !CSokoban::getInstance()->beTarget(D_P);
    }
    if(CSokoban::getInstance()->beWall(D_P))
    {
        D = true;
    }
    
    if(CSokoban::getInstance()->beBox(LD_P))
    {
        LD = true;
        LD_N_P = !CSokoban::getInstance()->beTarget(LD_P);
    }
    if(CSokoban::getInstance()->beWall(LD_P))
    {
        LD = true;
    }
    if(L && D && LD && (L_N_P || D_N_P || LD_N_P || Z_N_P))
        return false;
    //////////////////////// 右上角
    
    if(CSokoban::getInstance()->beBox(R_P))
    {
        R = true;
        R_N_P = !CSokoban::getInstance()->beTarget(R_P);
    }
    if(CSokoban::getInstance()->beWall(R_P))
    {
        R = true;
    }
    
    if(CSokoban::getInstance()->beBox(RU_P))
    {
        RU = true;
        RU_N_P = !CSokoban::getInstance()->beTarget(RU_P);
    }
    if(CSokoban::getInstance()->beWall(RU_P))
    {
        RU = true;
    }
    if(R && U && RU && (R_N_P || U_N_P || RU_N_P || Z_N_P))
        return false;
    //////////////////////// 右下角
    if(CSokoban::getInstance()->beBox(RD_P))
    {
        RD = true;
        RD_N_P = !CSokoban::getInstance()->beTarget(RD_P);
    }
    if(CSokoban::getInstance()->beWall(RD_P))
    {
        RD = true;
    }
    if(R && D && RD && (R_N_P || D_N_P || RD_N_P || Z_N_P))
        return false;
    return true;
}
bool CPileDetector::detect(CState & _boxState,CPosition &_oldBoxPos,CPosition & _newBoxPos)
{
    bool U_N_P  = false;
    bool D_N_P  = false;
    bool L_N_P  = false;
    bool R_N_P  = false;
    bool LU_N_P = false;
    bool LD_N_P = false;
    bool RU_N_P = false;
    bool RD_N_P = false;
    bool Z_N_P  = false;
    Z_N_P       = !CSokoban::getInstance()->beTarget(_newBoxPos);
    
    bool U  = false;
    bool L  = false;
    bool D  = false;
    bool R  = false;
    bool LU = false;
    bool LD = false;
    bool RU = false;
    bool RD = false;
    
    
    CPosition U_P  = CPosition(_newBoxPos.m_row-1,_newBoxPos.m_line);
    CPosition D_P  = CPosition(_newBoxPos.m_row+1,_newBoxPos.m_line);
    CPosition L_P  = CPosition(_newBoxPos.m_row  ,_newBoxPos.m_line-1);
    CPosition R_P  = CPosition(_newBoxPos.m_row  ,_newBoxPos.m_line+1);
    CPosition LU_P = CPosition(_newBoxPos.m_row-1,_newBoxPos.m_line-1);
    CPosition LD_P = CPosition(_newBoxPos.m_row+1,_newBoxPos.m_line-1);
    CPosition RU_P = CPosition(_newBoxPos.m_row-1,_newBoxPos.m_line+1);
    CPosition RD_P = CPosition(_newBoxPos.m_row+1,_newBoxPos.m_line+1);
    /////////////////////// 左上角
    if(_boxState[U_P.m_row][U_P.m_line])
    {
        U = true;
        U_N_P = !CSokoban::getInstance()->beTarget(U_P);
    }
    if(CSokoban::getInstance()->beWall(U_P))
    {
        U = true;
    }
    
    if(_boxState[L_P.m_row][L_P.m_line])
    {
        L = true;
        L_N_P = !CSokoban::getInstance()->beTarget(L_P);
    }
    if(CSokoban::getInstance()->beWall(L_P))
    {
        L = true;
    }
    
    if(_boxState[LU_P.m_row][LU_P.m_line])
    {
        LU = true;
        LU_N_P = !CSokoban::getInstance()->beTarget(LU_P);
    }
    if(CSokoban::getInstance()->beWall(LU_P))
    {
        LU = true;
    }
    if(L && U && LU && (U_N_P || L_N_P || LU_N_P || Z_N_P))
        return false;
    //////////////////////// 左下角
    if(_boxState[D_P.m_row][D_P.m_line])
    {
        D = true;
        D_N_P = !CSokoban::getInstance()->beTarget(D_P);
    }
    if(CSokoban::getInstance()->beWall(D_P))
    {
        D = true;
    }
    
    if(_boxState[LD_P.m_row][LD_P.m_line])
    {
        LD = true;
        LD_N_P = !CSokoban::getInstance()->beTarget(LD_P);
    }
    if(CSokoban::getInstance()->beWall(LD_P))
    {
        LD = true;
    }
    if(L && D && LD && (L_N_P || D_N_P || LD_N_P || Z_N_P))
        return false;
    //////////////////////// 右上角
    
    if(_boxState[R_P.m_row][R_P.m_line])
    {
        R = true;
        R_N_P = !CSokoban::getInstance()->beTarget(R_P);
    }
    if(CSokoban::getInstance()->beWall(R_P))
    {
        R = true;
    }
    
    if(_boxState[RU_P.m_row][RU_P.m_line])
    {
        RU = true;
        RU_N_P = !CSokoban::getInstance()->beTarget(RU_P);
    }
    if(CSokoban::getInstance()->beWall(RU_P))
    {
        RU = true;
    }
    if(R && U && RU && (R_N_P || U_N_P || RU_N_P || Z_N_P))
        return false;
    //////////////////////// 右下角
    if(_boxState[RD_P.m_row][RD_P.m_line])
    {
        RD = true;
        RD_N_P = !CSokoban::getInstance()->beTarget(RD_P);
    }
    if(CSokoban::getInstance()->beWall(RD_P))
    {
        RD = true;
    }
    if(R && D && RD && (R_N_P || D_N_P || RD_N_P || Z_N_P))
        return false;
    return true;
}
bool CPileDetector::detect()
{
    int boxMatrix[16];
    memset(boxMatrix, 0, sizeof(int[16]));
    
    for(int row =m_up ;row < m_down ; row++)
    {
        for(int line = m_left;line < m_right ;line++)
        {
            if(CSokoban::getInstance()->beBox(row,line))
            {
                boxMatrix[row]  |= (32768>>line);
            }
        }
    }
    int boxs_1;
    int boxs_2;
    int wall_1;
    int wall_2;
    int target_1;
    int target_2 ;
    int b_w_1  ;
    int b_w_2 ;
    int ss ;
    for(int row =0;row<16;row++)
    {
        if(boxMatrix[row] == 0)
            continue;
        boxs_1   = boxMatrix   [row];
        boxs_2   = boxMatrix   [row+1];
        wall_1   = m_wallMatrix[row];
        wall_2   = m_wallMatrix[row+1];
        target_1 = m_targetMatrix[row];
        target_2 = m_targetMatrix[row+1];
        
        b_w_1   = boxs_1  | wall_1;
        b_w_2   = boxs_2  | wall_2;
        ss      = b_w_1   & b_w_2 ;
        while (ss > 3) {
            while( !(ss & 1) )
            {
                ss       = ss       >>1;
                boxs_1   = boxs_1   >>1;
                boxs_2   = boxs_2   >>1;
                wall_1   = wall_1   >>1;
                wall_2   = wall_2   >>1;
                target_1 = target_1 >>1;
                target_2 = target_2 >>1;
            }
            if( (ss & 3) == 3 )
            {
                if( !( (target_1 & 3) == (boxs_1 & 3)  &&  (target_2 & 3) == (boxs_2 & 3) ) )
                    return false;
                ss       = ss       >>1;
                boxs_1   = boxs_1   >>1;
                boxs_2   = boxs_2   >>1;
                wall_1   = wall_1   >>1;
                wall_2   = wall_2   >>1;
                target_1 = target_1 >>1;
                target_2 = target_2 >>1;
            }
            else
            {
                ss       = ss       >>2;
                boxs_1   = boxs_1   >>2;
                boxs_2   = boxs_2   >>2;
                wall_1   = wall_1   >>2;
                wall_2   = wall_2   >>2;
                target_1 = target_1 >>2;
                target_2 = target_2 >>2;

            }
        }
    }
    return true;
}
bool CPileDetector::detect(CState &_state)
{
    int boxMatrix[16];
    memset(boxMatrix, 0, sizeof(int[16]));
    
    for(int row =m_up ;row < m_down ; row++)
    {
        for(int line = m_left;line < m_right ;line++)
        {
            if(_state[row][line])
            {
                boxMatrix[row]  |= (32768>>line);
            }
        }
    }
    int boxs_1;
    int boxs_2;
    int wall_1;
    int wall_2;
    int target_1;
    int target_2 ;
    int b_w_1  ;
    int b_w_2 ;
    int ss ;
    for(int row =0;row<16;row++)
    {
        if(boxMatrix[row] == 0)
            continue;
        boxs_1   = boxMatrix   [row];
        boxs_2   = boxMatrix   [row+1];
        wall_1   = m_wallMatrix[row];
        wall_2   = m_wallMatrix[row+1];
        target_1 = m_targetMatrix[row];
        target_2 = m_targetMatrix[row+1];
        
        b_w_1   = boxs_1  | wall_1;
        b_w_2   = boxs_2  | wall_2;
        ss      = b_w_1   & b_w_2 ;
        while (ss > 3) {
            while( !(ss & 1) )
            {
                ss       = ss       >>1;
                boxs_1   = boxs_1   >>1;
                boxs_2   = boxs_2   >>1;
                wall_1   = wall_1   >>1;
                wall_2   = wall_2   >>1;
                target_1 = target_1 >>1;
                target_2 = target_2 >>1;
            }
            if( (ss & 3) == 3 )
            {
                if( !( (target_1 & 3) == (boxs_1 & 3)  &&  (target_2 & 3) == (boxs_2 & 3) ) )
                    return false;
                ss       = ss       >>1;
                boxs_1   = boxs_1   >>1;
                boxs_2   = boxs_2   >>1;
                wall_1   = wall_1   >>1;
                wall_2   = wall_2   >>1;
                target_1 = target_1 >>1;
                target_2 = target_2 >>1;
            }
            else
            {
                ss       = ss       >>2;
                boxs_1   = boxs_1   >>2;
                boxs_2   = boxs_2   >>2;
                wall_1   = wall_1   >>2;
                wall_2   = wall_2   >>2;
                target_1 = target_1 >>2;
                target_2 = target_2 >>2;
                
            }
        }
    }
    return true;
}
void CPileDetector::init()
{
    m_up   = 100;
    m_down = 0 ;
    m_left = 100;
    m_right= 0;
    memset(m_targetMatrix, 0, sizeof(int[16]));
    memset(m_wallMatrix,   0, sizeof(int[16]));
    for(int row =0;row < 16 ; row++)
    {
        for(int line =0;line < 16 ;line++)
        {
            if(CSokoban::getInstance()->beWall(row,line))
            {
                if(row > m_down)
                    m_down = row;
                if(row < m_up)
                    m_up   = row;
                if(line > m_right)
                    m_right = line;
                if(line < m_left)
                    m_left = line;
                m_wallMatrix[row]   |= (32768>>line);
            }
            if(CSokoban::getInstance()->beTarget(row,line))
            {
                m_targetMatrix[row] |=(32768>>line);
            }
        }
    }
}
void CPileDetector::clearDectector()
{
    
}
