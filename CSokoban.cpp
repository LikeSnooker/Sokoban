//
//  CSokoban.cpp
//  sokoban
//
//  Created by 张雨 on 15/8/28.
//  Copyright (c) 2015年 张雨. All rights reserved.
//

#include "CSokoban.hpp"
#include "CHistory.hpp"
#include <sys/time.h>
unsigned char g_length =16;
static  Crossroads CRO_ALL = {true,true,true,true};
using __gnu_cxx::hash_map;
using __gnu_cxx::binary_function;
#define BE_WALL(pos)    m_wallState.existAt(pos)
#define BE_BOX(pos)     m_boxState.existAt(pos)
#define BE_TARGET(pos)  m_targetState.existAt(pos)
#define IN(pos)         (pos.m_row < 16 && pos.m_line <16)
#define CAN_GO(pos) (!m_wallState.existAt(pos) && !m_boxState.existAt(pos))
CSokoban::CSokoban()
{
}
CSokoban::CSokoban(const CSokoban &)
{

}
CSokoban * CSokoban::_instance = new CSokoban();
CSokoban * CSokoban::getInstance()
{
    return _instance;
}
template <typename pointerType>
inline void exchangePointer(pointerType * &pt1,pointerType * & pt2)
{
    pt1 = (pointerType*) ( (long)pt1 ^ (long)pt2 );
    pt2 = (pointerType*) ( (long)pt1 ^ (long)pt2 );
    pt1 = (pointerType*) ( (long)pt1 ^ (long)pt2 );
}
bool CSokoban::beBox(CPosition & _pos) const
{
    try {
        return m_boxState.existAt(_pos);
    } catch (OutsideException) {
        return false;
    }
    
}
bool CSokoban::beTarget(CPosition & _pos) const
{
    try {
        return m_targetState.existAt(_pos);
    } catch (OutsideException) {
        return false;
    }
    
}
bool CSokoban::beWall(CPosition &_pos) const
{
    try {
        return m_wallState.existAt(_pos);
    } catch (OutsideException) {
        return false;
    }
    
}

bool CSokoban::beBox   (unsigned char _row ,unsigned char _line) const
{
    try {
        return m_boxState.existAt(_row,_line);
    } catch (OutsideException) {
        return false;
    }
    
}
bool CSokoban::beTarget(unsigned char _row ,unsigned char _line) const
{
    try {
        return m_targetState.existAt(_row,_line);
    } catch (OutsideException) {
        return false;
    }
}
bool CSokoban::beWall       (unsigned char _row ,unsigned char _line) const
{
    try {
        return m_wallState.existAt(_row,_line);
    } catch (OutsideException) {
        return false;
    }
}

void CSokoban::setManPos    (const CPosition &_pos)
{
    if( !(_pos == m_boxState.m_manP) )
        [[NSNotificationCenter defaultCenter]postNotificationName:@"SOKOBAN_STATE_CHANGE" object:nil];
    m_boxState.m_manP = _pos;
}
void CSokoban::setManPos    (unsigned char _row,unsigned char _line)
{
    m_boxState.m_manP.m_row  = _row;
    m_boxState.m_manP.m_line = _line;
}
void CSokoban::setBoxOnPos(const CPosition &_pos)
{
    if(!m_boxState.existAt(_pos))
        [[NSNotificationCenter defaultCenter]postNotificationName:@"SOKOBAN_STATE_CHANGE" object:nil];
    m_boxState.setAt(_pos);
}
void CSokoban::unsetBoxOnPos(const CPosition &_pos)
{
    if(m_boxState.existAt(_pos))
        [[NSNotificationCenter defaultCenter]postNotificationName:@"SOKOBAN_STATE_CHANGE" object:nil];
    m_boxState.unsetAt(_pos);
}

void CSokoban::setWallOnPos  (const CPosition &_pos)
{
    if(!m_wallState.existAt(_pos))
        [[NSNotificationCenter defaultCenter]postNotificationName:@"SOKOBAN_STATE_CHANGE" object:nil];
    m_wallState.setAt(_pos);
}
void CSokoban::unsetWallOnPos(const CPosition &_pos)
{
    if(m_wallState.existAt(_pos))
        [[NSNotificationCenter defaultCenter]postNotificationName:@"SOKOBAN_STATE_CHANGE" object:nil];
    m_wallState.unsetAt(_pos);
}

void CSokoban::setTargetOnPos(const CPosition &_pos)
{
    if(!m_targetState.existAt(_pos))
        [[NSNotificationCenter defaultCenter]postNotificationName:@"SOKOBAN_STATE_CHANGE" object:nil];
    m_targetState.setAt(_pos);
}
void CSokoban::unsetTargetOnPos(const CPosition &_pos)
{
    if(m_targetState.existAt(_pos))
        [[NSNotificationCenter defaultCenter]postNotificationName:@"SOKOBAN_STATE_CHANGE" object:nil];
    m_targetState.unsetAt(_pos);
}
void CSokoban::setBoxOnPos     (unsigned char _row,unsigned char _line)
{
    setBoxOnPos(CPosition(_row,_line));
}
void CSokoban::unsetBoxOnPos   (unsigned char _row,unsigned char _line)
{
    unsetBoxOnPos( CPosition(_row,_line) );
}

void CSokoban::setWallOnPos    (unsigned char _row,unsigned char _line)
{
    setWallOnPos(CPosition(_row,_line));
}
void CSokoban::unsetWallOnPos  (unsigned char _row,unsigned char _line)
{
    unsetWallOnPos(CPosition(_row,_line));
}

void CSokoban::setTargetOnPos  (unsigned char _row,unsigned char _line)
{
    setTargetOnPos( CPosition(_row,_line) );
}
void CSokoban::unsetTargetOnPos(unsigned char _row,unsigned char _line)
{
    unsetTargetOnPos( CPosition(_row,_line) );
}
/////////////////////////
bool CSokoban::manNext(EDirection _direction)
{
    CPosition next  = m_boxState.m_manP.posByDirection(_direction);
    CPosition nextN = next.opposite(m_boxState.m_manP);
    if(!BE_WALL(next) && !BE_BOX(next))
    {
        m_boxState.m_manP = next;
        return true;
    }
    if(BE_BOX(next) && ! BE_WALL(nextN) && !BE_BOX(nextN))
    {
        m_boxState.m_manP = next;
        m_boxState.unsetAt(next);
        m_boxState.setAt  (nextN);
        return true;
    }
    return false;
}
const CPosition & CSokoban::getManPos()const
{
    return m_boxState.m_manP;
}
bool CSokoban::HavePath  (const CState & _state,CPosition &_pos1,CPosition & _pos2)const
{
    if(_pos1 == _pos2)
        return true;
    CState box_wall(_state);
    box_wall|=m_wallState;
    box_wall.fillFrom(_pos1,CRO_ALL);
    bool result = box_wall.existAt(_pos2);
    return result;
}
MAN_PATH CSokoban::GetPath   (CPosition _pos1,CPosition  _pos2)const
{
    CState state = m_boxState;
    return GetPath(_pos1, _pos2, state);
}
 MAN_PATH CSokoban::GetPath (CPosition _pos1 ,CPosition   _pos2,CState & _boxState)const
{
    MAN_PATH path;
    CPosition map[16][16];
    memset(map,0,sizeof(CPosition[16][16]));
    try {
        BFS(_pos1,_pos2,
            [&](CPosition & _prePos,CPosition & _pos)
            {
                map[_pos.m_row][_pos.m_line] = _prePos;
            },
            [&](CPosition &_pos)
            {
                return (!BE_WALL(_pos) && !_boxState.existAt(_pos));
                return false;
            });
    } catch (OutsideException) {
        return path;
    }
    
    if(map[_pos2.m_row][_pos2.m_line] == CPosition(0,0))
        return path;
    else
    {
        return Retrace(_pos1, _pos2,
                       [&](CPosition& _pos){
                           return map[_pos.m_row][_pos.m_line];
                       });
    }
}
MAN_PATH CSokoban::InnerPositions()const
{
    static vector<CPosition> result;
    result.clear();
    result.push_back(m_boxState.m_manP);
    try {
        BFS(m_boxState.m_manP,CPosition(20,20),
            [&](CPosition & _prePos,CPosition & _pos)
            {
                result.push_back(_pos);
            },
            [&](CPosition &_pos)
            {
                return (!BE_WALL(_pos) );
            });
    } catch (OutsideException) {
        return result;
    }
    return result;
}
MAN_PATH CSokoban::InnerPositions(CState & _boxState)const
{
    static vector<CPosition> result;
    result.clear();
    result.push_back(_boxState.m_manP);
    try {
        BFS(_boxState.m_manP,CPosition(20,20),
            [&](CPosition & _prePos,CPosition & _pos)
            {
                result.push_back(_pos);
            },
            [&](CPosition &_pos)
            {
                return (!BE_WALL(_pos) );
            });
    } catch (OutsideException) {
        return result;
    }
    return result;
}
bool CSokoban::PreCalculation()const
{
    if(BE_BOX(m_boxState.m_manP) || BE_WALL(m_boxState.m_manP))
        return false;
    unsigned boxCount    = 0;
    unsigned targetCount = m_targetState.existAt(m_boxState.m_manP)?1:0;

    try {
        BFS(m_boxState.m_manP,CPosition(20,20),
            [&](CPosition &_pos1,CPosition &_pos2){
                try {
                    BE_BOX(_pos2)?boxCount++:boxCount;
                    BE_TARGET(_pos2)?targetCount++:targetCount;
                } catch (OutsideException) {
                    throw OutsideException();
                }
            },
            [&](CPosition &_pos)
            {
                bool result = true;
                try {
                    result = (!BE_WALL(_pos));
                } catch (OutsideException) {
                    throw OutsideException();
                    return false;
                }
                return result;
            }
            );
    } catch (OutsideException) {
        return false;
    }
    return boxCount == targetCount;
}

template <typename Func1,typename Func2>
bool CSokoban::BFS(CPosition _originPosition,CPosition _destinationPosition,Func1 _processor,Func2 _filter)const
{
    static vector<CPosition> * waitExplorePositions = new vector<CPosition>;
    static vector<CPosition> * newExplorePositions  = new vector<CPosition>;
    static bool explored[16][16];
    if(_originPosition == _destinationPosition)
        return true;
    waitExplorePositions->clear();
    newExplorePositions ->clear();
    memset(explored, 0, sizeof(bool[16][16]));
    
    waitExplorePositions->push_back(_originPosition);
    explored[_originPosition.m_row][_originPosition.m_line] = true;
    
    while (waitExplorePositions->size()>0) {
        for(auto curPosition = waitExplorePositions->begin();curPosition!=waitExplorePositions->end();curPosition++)
        {
            for(int d =CPosition::UP; d < CPosition::MAX_D ; d++)
            {
                CPosition nextPos =  curPosition->posByDirection((EDirection)d);
                
                try {
                    if(!explored[nextPos.m_row][nextPos.m_line])
                    {
                        if(nextPos == _destinationPosition)
                        {
                            _processor(*curPosition,nextPos);
                            return true;
                        }
                        else if(_filter(nextPos))
                        {
                            explored[nextPos.m_row][nextPos.m_line] = true;
                            newExplorePositions->push_back (nextPos);
                            _processor(*curPosition,nextPos);
                        }
                    }
                }
                catch (OutsideException) {
                    throw OutsideException();
                    return false;
                }
            }
        }
        exchangePointer(waitExplorePositions, newExplorePositions);
        newExplorePositions->clear();
    }
    
    return false;
}



template <typename T, typename Filter,typename Propeller,typename Processor>
bool CSokoban::BFSEX(T _origin,T _destination,Propeller _propeller,Filter _filter, Processor _processor)const
{
    class C2D
    {
    public:
        C2D(size_t _size)
        {
            m_data = new bool[_size];
            m_size = _size;
            memset(m_data,0,_size * sizeof(bool));
        }
        ~C2D()
        {
            delete []m_data;
        }
        bool& operator[](size_t _index)
        {
            return m_data[_index];
        }
        void Init()
        {
            memset(m_data,0,m_size * sizeof(bool));
        }
    private:
        size_t m_size;
        bool * m_data;
    };
    static vector<T>  waitExplore;
    static vector<T>   newExplore;
    static const vector<T> *  cache;
    static C2D explored(_origin.HashTableSize());
    if(_origin == _destination)
    {
        return true;
    }
    
    waitExplore.clear();
    newExplore .clear();
    explored.Init();
    explored[_origin.HashValue()] = true;
    waitExplore.push_back(_origin);
    while (waitExplore.size()>0) {
        for(auto node = waitExplore.begin();node!=waitExplore.end();node++)
        {
            cache = _propeller(*node);
            for(auto cache_it = cache->begin(); cache_it != cache->end();cache_it++)
            {
                if( !explored[cache_it->HashValue()] )
                {
                    if(*cache_it == _destination)
                    {
                        _processor(*node,*cache_it);
                        return true;
                    }
                    else if(_filter(*cache_it))
                    {
                        explored[cache_it->HashValue()] = true;
                        newExplore.push_back(*cache_it);
                        _processor(*node,*cache_it);
                    }
                }
            }
        }
        waitExplore.swap(newExplore);
        newExplore.clear();
    }
    return false;
}

template <typename T,typename Func>
vector<T> CSokoban::Retrace(T _origin,T _destination,Func _func)const
{
    vector<T> path;
    T cur = _destination;
    while(! (cur == _origin) )
    {
        path.push_back(cur);
        cur = _func(cur);
    }
    path.push_back(_origin);
    vector<T> result;
    for(auto it = path.rbegin();it != path.rend();it++)
    {
        result.push_back(*it);
    }
    return result;
}
template <typename T, typename FilterFunction>
void CSokoban::Screen(vector<T>& _vector,vector<T>& _result, FilterFunction _filter)const
{
    _result.clear();
    for(auto node = _vector.begin();node != _vector.end();node++)
    {
        if(_filter(*node))
        {
            _result.push_back(*node);
        }
    }
}
void CSokoban::arrived(bool _matrix[16][16])const
{
  
    memset(_matrix,0,sizeof(bool[16][16]));
    _matrix[m_boxState.m_manP.m_row][m_boxState.m_manP.m_line] = true;
    try {
        BFS(m_boxState.m_manP,CPosition(20,20),
            [&](CPosition & _prePos, CPosition& _pos){
                _matrix[_pos.m_row][_pos.m_line] = true;
                return true;
            }
            ,[&](CPosition& _pos)
            {
                return ( !BE_WALL(_pos)&& !BE_BOX(_pos));
            });
    } catch (OutsideException) {
        return;
    }
}
void CSokoban::arrived(const CState & _boxState,bool _matrix[16][16])const
{
    memset(_matrix,0,sizeof(bool[16][16]));
    _matrix[m_boxState.m_manP.m_row][m_boxState.m_manP.m_line] = true;
    try {
        BFS(m_boxState.m_manP,CPosition(20,20),
            [&](CPosition & _prePos, CPosition& _pos){
                _matrix[_pos.m_row][_pos.m_line] = true;
                return true;
            }
            ,[&](CPosition& _pos)
            {
                return ( !BE_WALL(_pos)&& !_boxState[_pos.m_row][_pos.m_line]);
            });
    } catch (OutsideException) {
        return;
    }

}
vector<SokobanData> CSokoban::generalPath(const CState  _state)const
{
    vector<SokobanData> realResult;
    
    STATE_PATH result;
    STATE_PATH temp;
    temp.push_back(_state);
    CState curState = _state;
    vector<CChange> change_path;
    while (CHistory::getInstance()->findChange(curState) != CChange::EMPTY_CHANGE) {
        CChange change = CHistory::getInstance()->findChange(curState);
        change_path.push_back(change);
        curState.setAt(change.m_boxOldPosition);
        curState.unsetAt(change.m_boxNewPosition);
        curState.m_manP = change.m_manOldPosition;
        temp.push_back(curState);
    }
    while (temp.size()>0) {
        result.push_back(temp.back());
        temp.pop_back();
        if(temp.size()==0)
        {
            for(vector<CState>::iterator it = result.begin();it<result.end();it++)
            {
                SokobanData data = GetSokobanDataFromState(*it);
                realResult.push_back(data);
            }
            return realResult;
        }
        CState lastState  = result.back();
        CState curState   = temp.back();
        CChange change    = CHistory::getInstance()->findChange(curState);
        CPosition nextP   = change.m_boxOldPosition.opposite(change.m_boxNewPosition);
        MAN_PATH man_path = GetPath(lastState.m_manP, nextP,lastState);
        POS_IT it = man_path.begin();
        while (it != man_path.end()) {
            CState state =  result.back();
            state.m_manP =  *it;
            if( ! (result.back() == state) )
                result.push_back(state);
            it++;
        }
    }
    
    //转换成 sokobanData再返回
    for(vector<CState>::iterator it = result.begin();it<result.end();it++)
    {
        SokobanData data = GetSokobanDataFromState(*it);
        realResult.push_back(data);
    }
    return realResult;

}

vector<SokobanData> CSokoban::Calculation() //广度优先搜索
{
//    return Calculation2(m_boxState);
    static vector<const CState*>  * wait_explore     = new vector<const CState*>;
    static vector<const CState*>  *  new_explore     = new vector<const CState*>;
    vector<CPosition> innerPositions = InnerPositions();
    vector<CPosition> boxPositions;
    wait_explore ->reserve(2000);
    new_explore  ->reserve(2000);
    CState orginState= m_boxState;
    vector<SokobanData> path;
    //
    if(m_boxState.sameLayout(m_targetState))
    {
        return path;
    }
    CHistory    ::getInstance()->clear();
    initAllDetectors();

    if(!beAlive())
    {
        return path;
    }
    wait_explore->push_back (CHistory::getInstance()->addState(m_boxState, CChange::EMPTY_CHANGE));
    while (wait_explore -> size()>0) {
        cout << wait_explore->size()<<endl;
        for(auto it_cur_state = wait_explore->begin();it_cur_state != wait_explore->end();it_cur_state++){
            m_boxState = **it_cur_state;
            Screen(innerPositions, boxPositions,
                   [this](CPosition & _pos)
                   {
                       return m_boxState[_pos.m_row][_pos.m_line];
                   }
                   );
            bool canGo[16][16];
            arrived(canGo);
            for(auto it_cur_pos = boxPositions.begin();it_cur_pos != boxPositions.end();it_cur_pos++)
            {
                for(int d = CPosition::UP; d < CPosition::MAX_D;d++)
                {
                    CPosition box_go_pos      = it_cur_pos->posByDirection((EDirection)d);
                    CPosition man_go_pos      = it_cur_pos->opposite(box_go_pos);
                    CPosition man_old_pos     = m_boxState.m_manP;
                    if(canGo[man_go_pos.m_row][man_go_pos.m_line] && CAN_GO(box_go_pos))
                    {
                        m_boxState.m_manP = *it_cur_pos;
                        m_boxState.unsetAt(*it_cur_pos);
                        m_boxState.setAt(box_go_pos);
    
                        if(m_boxState.sameLayout(m_targetState))
                        {
                            CHistory::getInstance()->addState(m_boxState, CChange(man_old_pos,box_go_pos,*it_cur_pos));
                            wait_explore->clear();
                            new_explore ->clear();
                            path = generalPath(m_boxState);
                            m_boxState = orginState;
                            return path;
                        }
                        if(beAlive(*it_cur_pos,box_go_pos))
                        {
                            const CState * statePtr= CHistory::getInstance()->addState(m_boxState,CChange(man_old_pos,box_go_pos,*it_cur_pos));
                            if(statePtr != NULL)
                                new_explore->push_back(statePtr);
                        }
                        m_boxState = **it_cur_state;
                    }
                }

            };
        }
        exchangePointer(new_explore, wait_explore);
        new_explore->clear();
    }
    wait_explore->clear();
    new_explore ->clear();
    m_boxState = orginState;
    return path;
}
vector<SokobanData> CSokoban::Calculation2  (CState & _boxState) //广度优先搜索
{
    static vector<const CState*>  * wait_explore     = new vector<const CState*>;
    static vector<const CState*>  *  new_explore     = new vector<const CState*>;
    vector<CPosition> innerPositions = InnerPositions(); //
    vector<CPosition> boxPositions;
    wait_explore ->reserve(2000);
    new_explore  ->reserve(2000);
    vector<SokobanData> path;
    //
    if(_boxState.sameLayout(m_targetState))
    {
        return path;
    }
    CHistory    ::getInstance()->clear();
    initAllDetectors();  //
    
    if(!beAlive(_boxState)) //
    {
        return path;
    }
    wait_explore->push_back (CHistory::getInstance()->addState(_boxState, CChange::EMPTY_CHANGE));
    while (wait_explore -> size()>0) {
        for(const CState * it_cur_state : *wait_explore){
            CState curState = * it_cur_state;
            Screen(innerPositions, boxPositions, //
                   [&](CPosition & _pos)
                   {
                       return curState[_pos.m_row][_pos.m_line];
                   }
                   );
            bool canGo[16][16];
            
            arrived(curState,canGo); //
            for(auto it_cur_pos :boxPositions)
            {
                for(int d = CPosition::UP; d < CPosition::MAX_D;d++)
                {
                    curState = * it_cur_state;
                    CPosition box_go_pos      = it_cur_pos.posByDirection((EDirection)d);
                    CPosition man_go_pos      = it_cur_pos.opposite(box_go_pos);
                    CPosition man_old_pos     = _boxState.m_manP;
                    if(canGo[man_go_pos.m_row][man_go_pos.m_line] && !_boxState[box_go_pos.m_row][box_go_pos.m_line] && !m_wallState[box_go_pos.m_row][box_go_pos.m_line] )
                    {
                        curState.m_manP = it_cur_pos;
                        curState.unsetAt(it_cur_pos);  //
                        curState.setAt(box_go_pos);     //
                        
                        if(curState.sameLayout(m_targetState))
                        {
                            CHistory::getInstance()->addState(curState, CChange(man_old_pos,box_go_pos,it_cur_pos));  //
                            wait_explore->clear();
                            new_explore ->clear();
                            path = generalPath(curState); //
                            return path;
                        }
                        if(beAlive(it_cur_pos,box_go_pos))//
                        {
                            const CState * statePtr= CHistory::getInstance()->addState(curState,CChange(man_old_pos,box_go_pos,it_cur_pos));
                            if(statePtr != NULL)
                                new_explore->push_back(statePtr);
                        }
                    }
                }
                
            }
        }
        exchangePointer(new_explore, wait_explore);
        new_explore->clear();
    }
    wait_explore->clear();
    new_explore ->clear();
    return path;
}

void CSokoban::setStyle(unsigned char _row,unsigned char _line,unsigned char _style)
{
    if(_row < g_length && _line < g_length )
    {
        switch (_style) {
            case 0:      //MAN
                m_boxState.m_manP =    CPosition(_row,_line);
                break;
            case 1:      //BOX
                setBoxOnPos     (_row,_line);
                unsetWallOnPos  (_row,_line);
                unsetTargetOnPos(_row,_line);
                break;
            case 2:      //BOXONTARGET
                unsetWallOnPos  (_row,_line);
                setBoxOnPos     (_row,_line);
                setTargetOnPos  (_row,_line);
                break;
            case 3:      //TARGET
                unsetWallOnPos  (_row,_line);
                unsetBoxOnPos   (_row,_line);
                setTargetOnPos  (_row,_line);
                break;
            case 4:      //WALL
                setWallOnPos    (_row,_line);
                unsetBoxOnPos   (_row,_line);
                unsetTargetOnPos(_row,_line);
                break;
            case 5:      //EMPTY
                unsetWallOnPos  (_row,_line);
                unsetBoxOnPos   (_row,_line);
                unsetTargetOnPos(_row,_line);
                break;
            default:
                break;
        }
    }
}
bool CSokoban::sameAs(const CState & _state1 ,const CState & _state2)const
{
    if(_state1.sameLayout(_state2) )
    {
        CPosition p_dest = _state1.m_manP;
        CPosition p_star = _state2.m_manP;
        return HavePath(_state1,p_star,p_dest);
    }
    else
        return false;
}
void CSokoban::addDetector(CDetector * _detector)
{
    if(_detector == NULL)
        return;
    m_detectors.push_back(_detector);
}
void CSokoban::clear()
{
    m_boxState   .clear();
    m_wallState  .clear();
    m_targetState.clear();
}
//ISokobanDataSource Method
SokobanData CSokoban::GetSokobanData()
{
    SokobanData result;
    enumerated(16,16,[&](int row,int line){
        if(m_wallState.existAt(row, line) )
        {
            result.m_layout[row][line] = WALL;
        }
        if(m_boxState.existAt(row,line) && ! m_targetState.existAt(row,line))
        {
            result.m_layout[row][line] = BOX;
        }
        if(!m_boxState.existAt(row,line) && m_targetState.existAt(row,line))
        {
            result.m_layout[row][line] = TARGET;
        }
        if(m_boxState.existAt(row,line) && m_targetState.existAt(row,line))
        {
            result.m_layout[row][line] = BOXONTARGET;
        }

    });
    result.m_manPosition = m_boxState.m_manP;
    return result;
}
SokobanData CSokoban::GetSokobanDataFromState(CState & _state)const
{
    SokobanData result;
    enumerated(16,16,[&](int row,int line){
        if(m_wallState.existAt(row, line) )
        {
            result.m_layout[row][line] = WALL;
        }
        if(_state.existAt(row,line) && ! m_targetState.existAt(row,line))
        {
            result.m_layout[row][line] = BOX;
        }
        if(!_state.existAt(row,line) && m_targetState.existAt(row,line))
        {
            result.m_layout[row][line] = TARGET;
        }
        if(_state.existAt(row,line) && m_targetState.existAt(row,line))
        {
            result.m_layout[row][line] = BOXONTARGET;
        }
        
    });

    result.m_manPosition = _state.m_manP;
    return result;
}
void CSokoban::InitWithSokobanData(SokobanData &_sokobanData)
{
    clear();
    enumerated(16, 16, [&](int row,int line){
        switch (_sokobanData.m_layout[row][line]) {
            case WALL:
                m_wallState.setAt(row,line);
                break;
            case BOX:
                m_boxState.setAt(row, line);
                break;
            case TARGET:
                m_targetState.setAt(row, line);
                break;
            case BOXONTARGET:
                m_targetState.setAt(row, line);
                m_boxState.setAt(row, line);
                break;
            default:
                break;
        }
        
    });
    m_boxState.m_manP = _sokobanData.m_manPosition;
}
long Factorial(unsigned long _x) // _x * (_x -1) * (_x -2)  .... * 1
{
    long result = 1;
    while(_x > 1)
    {
        result *= _x;
        _x--;
    }
    return result;
}
long Factorial(unsigned long _n1,unsigned long _n2) // _n1 * (_n1 -1) * (_n1 -2) .... * _n2
{
    long result = 1;
    while(_n1  >= _n2)
    {
        result *= _n1;
        _n1--;
    }
    return result;
}
long A(unsigned long _n,unsigned long _m)// return A(_x,_y) 排列
{
    if(_n <= _m)
        return -1;
    return Factorial(_n,_n-_m);
}
long C(unsigned long _n,unsigned long _m)// return C(_n,_m) 组合
{
    if(_n <= _m)
        return -1;
    return _m == 0 ? 1: ( Factorial(_n,_n - _m+1) / (Factorial(_m)) );
}
long CSum(unsigned long _n1,unsigned long _n2,unsigned long _m)
{
    long result = 0;
    if(_n1 <= _n2)
        return 0;
    for(unsigned long i = _n1 ;i > _n2;i--)
    {
        result += C(i,_m);
    }
    return result;
}
long CSokoban::MaxHashValue()
{
    vector<CPosition> innerPositions = InnerPositions();
    vector<CPosition> boxPositions;
    Screen(innerPositions, boxPositions,
           [this](CPosition & _pos)
           {
               return m_boxState[_pos.m_row][_pos.m_line];
           }
           );
    return C( innerPositions.size(),boxPositions.size() );
}
long CSokoban::HashValue()
{
    long result = 0;
    vector<CPosition> innerPositions = InnerPositions();
    size_t innerFloorCount   = innerPositions.size();
    sort(innerPositions.begin(),innerPositions.end());
    vector<CPosition> boxPositions;
    Screen(innerPositions, boxPositions,
           [this](CPosition & _pos)
           {
               return m_boxState[_pos.m_row][_pos.m_line];
           }
           );
    size_t boxsCount = boxPositions.size();
    auto box   = boxPositions.begin();
    auto floor = innerPositions.begin();
    size_t lastFloorIndex = -1;
    size_t remainBoxCount = boxsCount -1;
    while(box != boxPositions.end() && floor != innerPositions.end())
    {
        if(*box == * floor)
        {
            size_t floorIndex     = floor - innerPositions.begin();
            
            result += CSum( innerFloorCount-(lastFloorIndex+1)-1,innerFloorCount- floorIndex-1,remainBoxCount);
            
            lastFloorIndex = floorIndex;
            
            box++;
            remainBoxCount--;
        }
        floor++;
    }
    return result;
}

