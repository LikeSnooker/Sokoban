//
//  CFileAdapter.cpp
//  sokoban
//
//  Created by 张雨 on 15/10/8.
//  Copyright © 2015年 张雨. All rights reserved.
//

#include "CFileAdapter.hpp"

#include "function.hpp"
extern int g_length;
CFileAdapter *CFileAdapter::m_instance = new CFileAdapter();
CFileAdapter::CFileAdapter(const CFileAdapter & fileAdapter)
{

}
CFileAdapter::CFileAdapter()
{

}
CFileAdapter * CFileAdapter::getInstance()
{
    return m_instance;
}
bool CFileAdapter::save(NSString * _fileName)
{
    if( [[NSUserDefaults standardUserDefaults]objectForKey:_fileName] !=nil)
        return false;
    int box_matrix   [20];
    memset(box_matrix, 0, sizeof(int[20]));
    int wall_matrix  [20];
    memset(wall_matrix, 0, sizeof(int[20]));
    int target_matrix[20];
    memset(target_matrix, 0, sizeof(int[20]));
    unsigned char length = g_length;
    for(int row =0;row<length;row++)
    {
        for(int line =0;line<length;line++)
        {
            if(CSokoban::getInstance()->beBox(row,line))
            {
                setBit(box_matrix, row, line);
            }
            if(CSokoban::getInstance()->beWall(row,line))
            {
                setBit(wall_matrix, row, line);
            }
            if(CSokoban::getInstance()->beTarget(row,line))
            {
                setBit(target_matrix, row, line);
            }

        }
    }
    NSMutableDictionary * map       = [[NSMutableDictionary alloc]init];
    NSMutableArray      * boxArr    = [[NSMutableArray alloc]init];
    NSMutableArray      * wallArr   = [[NSMutableArray alloc]init];
    NSMutableArray      * targetArr = [[NSMutableArray alloc]init];
    for(int row =0;row<20;row++)
    {
        NSNumber * box_row_num       = [NSNumber numberWithInteger:box_matrix[row]];
        [boxArr addObject:box_row_num];
        
        NSNumber * wall_row_num      = [NSNumber numberWithInteger:wall_matrix[row]];
        [wallArr addObject:wall_row_num];
        
        NSNumber * target_row_num    = [NSNumber numberWithInteger:target_matrix[row]];
        [targetArr addObject:target_row_num];
    }
    [map setObject:boxArr    forKey:@"box_map"];
    [map setObject:wallArr   forKey:@"wall_map"];
    [map setObject:targetArr forKey:@"target_map"];
    
    NSNumber * man_row  = [NSNumber numberWithInt:CSokoban::getInstance()->getManPos().m_row];
    NSNumber * man_line = [NSNumber numberWithInt:CSokoban::getInstance()->getManPos().m_line];
    [map setObject:man_row  forKey:@"man_row"];
    [map setObject:man_line forKey:@"man_line"];
    
    [[NSUserDefaults standardUserDefaults]setObject:[NSDictionary dictionaryWithDictionary:map] forKey:_fileName];

    NSArray * map_names =[[NSUserDefaults standardUserDefaults]objectForKey:@"map_names"];
    NSMutableArray * mut_map_names =[NSMutableArray arrayWithArray:map_names];
    [mut_map_names addObject:_fileName];
    
    [[NSUserDefaults standardUserDefaults]setObject:[NSArray arrayWithArray:mut_map_names] forKey:@"map_names"];
    return [[NSUserDefaults standardUserDefaults]synchronize];
}
bool CFileAdapter::read(NSString * _fileName)
{
    if([[NSUserDefaults standardUserDefaults]objectForKey:_fileName]==nil)
        return false;
    unsigned char length   =  g_length;
    NSDictionary * map     =  [[NSUserDefaults standardUserDefaults]objectForKey:_fileName];
    NSArray *     boxArr   =  [map objectForKey:@"box_map"];
    NSArray *     wallArr  =  [map objectForKey:@"wall_map"];
    NSArray *     targetArr=  [map objectForKey:@"target_map"];
    for(int row =0;row<length;row++)
    {
        for(int line =0;line<length;line++)
        {
            if(checkBit([boxArr[row]intValue], line))
            {
                CSokoban::getInstance()->setBoxOnPos(row, line);
            }
            
            if(checkBit([wallArr[row]intValue], line))
            {
                CSokoban::getInstance()->setWallOnPos(row, line);
            }
            
            if(checkBit([targetArr[row]intValue], line))
            {
                CSokoban::getInstance()->setTargetOnPos(row, line);
            }
        
        }
    }
    NSNumber * man_row   = [map objectForKey:@"man_row"];
    NSNumber * man_line  = [map objectForKey:@"man_line"];
    
    CPosition manP = CPosition(man_row==nil?0:[man_row intValue],man_line ==nil?0 :[man_line intValue] );
    CSokoban::getInstance()->setManPos(manP);
    return true;
}