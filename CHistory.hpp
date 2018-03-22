//
//  CHistory.hpp
//  sokoban
//
//  Created by 张雨 on 15/10/30.
//  Copyright © 2015年 张雨. All rights reserved.
//

#ifndef CHistory_hpp
#define CHistory_hpp

#include <stdio.h>
#include "CSokoban.hpp"
#include <map>
#include <vector>
#include <ext/hash_map>
#include "CChange.hpp"
using std::map;
using std::pair;
using std::make_pair;
using std::vector;
using __gnu_cxx::hash_map;
using __gnu_cxx::binary_function;
typedef pair<CState,bool>    my_hash_pair;
typedef pair<CState,CChange> CState_CChange_pair;
class CHistory
{
public:
    static CHistory * getInstance();
private:
    CHistory();
    CHistory(const CHistory & );
    CHistory & operator= (const CHistory &);
    static CHistory * _instance;
private:
    struct compare_state
    {
        bool operator()(const CState& _state1 ,const CState & _state2) const
        {
            return CSokoban::getInstance()->sameAs(_state1,_state2);
        }
    };
    struct hash_state{
        size_t operator()(const CState & _state) const
        {
            return _state.hash_value();
        }
    };
private:
    hash_map<CState,CChange,hash_state,compare_state> _history;
public:
    const CState * addState(const CState &_state,CChange _change);
    CChange findChange(const CState & _state);
    void clear();
public:
    long getStateCount();
};
#endif /* CHistory_hpp */
