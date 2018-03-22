//
//  CHistory.cpp
//  sokoban
//
//  Created by 张雨 on 15/10/30.
//  Copyright © 2015年 张雨. All rights reserved.
//

#include "CHistory.hpp"
CHistory * CHistory::_instance = new CHistory();
CHistory * CHistory::getInstance()
{
    return _instance;
}
CHistory::CHistory()
{
    _history.resize(10000019);
}
CHistory::CHistory(const CHistory &)
{
    
}
const CState * CHistory::addState(const CState &_state,CChange _change)
{
    pair<hash_map<CState,CChange>::iterator,bool> it = _history.insert(CState_CChange_pair(_state,_change));
    return it.second?&it.first->first:NULL;
}
CChange CHistory::findChange(const CState & _state)
{
    hash_map<CState,CChange>::iterator it = _history.find(_state);
    bool _success = !(it == _history.end());
    return ( _success ? it->second : CChange::EMPTY_CHANGE );
}
void CHistory::clear()
{
    _history.clear();
}
long CHistory::getStateCount()
{
    return _history.size();
}
