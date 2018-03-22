//
//  CIteratorVeter.cpp
//  sokoban
//
//  Created by 张雨 on 2016/11/17.
//  Copyright © 2016年 张雨. All rights reserved.
//

#include "CIteratorVector.hpp"


CIteratorVector::CIteratorVector(vector<SokobanData> & _vec)
{
    *this = _vec;
    it    = this->begin();
}
CIteratorVector::CIteratorVector()
{

}
SokobanData & CIteratorVector::getCurState()const
{
    return * it;
}
void CIteratorVector::next()
{
    if(it < this->end() -1 )
    {
        it++;
    }
}
void CIteratorVector::last()
{
    if(it > this->begin())
    {
        it--;
    }
}
CIteratorVector & CIteratorVector::operator = (vector<SokobanData>  _vec)
{
    this->assign(_vec.begin(),_vec.end());
    it     = this->begin();
    return *this;
}
unsigned long CIteratorVector::index()
{
    return this->size()==0?0:it - this->begin() + 1;
}
void CIteratorVector::clear()
{
    vector<SokobanData>::clear();
    it = begin();
}
void CIteratorVector::push_back()
{

}
void CIteratorVector::pop_back()
{

}
