//
//  CSokoban.h
//  sokoban
//
//  Created by 张雨 on 15/8/28.
//  Copyright (c) 2015年 张雨. All rights reserved.
//

#ifndef __sokoban__CSokoban__
#define __sokoban__CSokoban__
#include <stdio.h>
#include "CPosition.hpp"
#include "CState.hpp"
#include "CDrawTool.hpp"
#include "common.hpp"
#include "ISokobanDatasource.hpp"
#import  <UIKit/UIKit.h>
#include <vector>
#include <map>

#include <iostream>
using std::cout;
using std::endl;

using std::vector;
using std::map;
using std::pair;
using std::make_pair;

using EDirection = CPosition::EDirection;
class CDetector;
class CFileAdapter;
typedef vector<CPosition> MAN_PATH;
typedef vector<CPosition>::iterator POS_IT;
typedef vector<CState>  STATE_PATH;

class CSokoban :public ISokobanDataSource
{
    // singleton
public:
    static CSokoban * getInstance();
private:
    CSokoban();
    CSokoban(const CSokoban & );
    CSokoban & operator= (const CSokoban &);
    static CSokoban    * _instance;
    // singleton
private:
    CState             m_wallState;
    CState             m_targetState;
    CState             m_boxState;
    vector<CDetector*> m_detectors;
private:
    friend class CFileAdapter;
    friend class CDetector;
    friend class CReasoningDetector;
    void setBoxOnPos     (const CPosition &_pos);
    void unsetBoxOnPos   (const CPosition &_pos);
    
    void setWallOnPos    (const CPosition &_pos);
    void unsetWallOnPos  (const CPosition &_pos);
    
    void setTargetOnPos  (const CPosition &_pos);
    void unsetTargetOnPos(const CPosition &_pos);
    
    void setBoxOnPos     (unsigned char _row,unsigned char _line);
    void unsetBoxOnPos   (unsigned char _row,unsigned char _line);
    
    void setWallOnPos    (unsigned char _row,unsigned char _line);
    void unsetWallOnPos  (unsigned char _row,unsigned char _line);
    
    void setTargetOnPos  (unsigned char _row,unsigned char _line);
    void unsetTargetOnPos(unsigned char _row,unsigned char _line);
public:
    void setManPos       (const CPosition &_pos);
    bool manNext         (EDirection _direction);
    void setManPos       (unsigned char _row,unsigned char _line);
    void setStyle        (unsigned char _row,unsigned char _line,unsigned char _style);
    bool beBox        (CPosition & _pos) const;
    bool beTarget     (CPosition & _pos) const;
    bool beWall       (CPosition & _pos) const;
    
    bool beBox        (unsigned char _row ,unsigned char _line) const;
    bool beTarget     (unsigned char _row ,unsigned char _line) const;
    bool beWall       (unsigned char _row ,unsigned char _line) const;
    const CPosition & getManPos()const;
/////////////////////////////////////////////求解 相关函数
public:
    
    MAN_PATH GetPath          (CPosition _pos1 ,CPosition   _pos2)const;
    vector<SokobanData> Calculation  ();
    vector<SokobanData> Calculation2  (CState & _boxState);
    bool PreCalculation()const;     //搜索之前的预处理 判断是否可搜索
    bool sameAs      (const CState & _state1 ,const CState & _state2)const;//当前状态是否等同于指定状态，等同是指箱子布局相同，且人可以在不移动箱子的情况下移动到目标状态
    //判断是否是死局
private:
    template <typename Func1,typename Func2>
    bool BFS(CPosition _originPosition,CPosition _destinationPosition,Func1 _processor,Func2 _filter)const;
    
    template <typename T, typename Filter,typename Propeller,typename Processor>
    bool BFSEX(T _origin,T _destination,Propeller _propeller,Filter _filter, Processor _processor)const;
    
    template <typename T,typename Func>
    vector<T> Retrace(T _origin,T _destination,Func _func)const;
    
    template <typename T, typename FilterFunction>
    void Screen(vector<T>& _vector,vector<T>& _result,FilterFunction _filter)const;
    
    MAN_PATH GetPath   (CPosition _pos1 ,CPosition   _pos2,CState & _boxState)const;
    MAN_PATH InnerPositions()const;
    MAN_PATH InnerPositions(CState & _boxState)const;
    bool HavePath      (const CState & _state,CPosition &_pos1,CPosition & _pos2)const;
    bool beAlive()const;
    bool beAlive(CState &_state)const;
    bool beAlive(CPosition & _oldBoxPos,CPosition & _newBoxPos)const;
    bool beAlive(CState & _boxState,CPosition & _oldBoxPos,CPosition & _newBoxPos)const;
    void initAllDetectors();
    vector<SokobanData> generalPath(const CState  _state)const;
private:
    void arrived(bool _matrix[16][16])const;
    void arrived(const CState & _boxState,bool _matrix[16][16])const;
/////////////////////////////////////////////求解 相关函数
public:   //detect
    void addDetector(CDetector * _detector);
public:
    void clear();
    //ISokobanDataSource
    SokobanData GetSokobanData();
    SokobanData GetSokobanDataFromState(CState & _state)const;
    void InitWithSokobanData(SokobanData &_sokobanData);
    virtual long HashValue();
    long MaxHashValue();
};
#endif /* defined(__sokoban__CSokoban__) */
