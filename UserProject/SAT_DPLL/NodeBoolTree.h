#ifndef NODEBOOLTREE_H
#define NODEBOOLTREE_H

#include "BBV.h"
#include "boolinterval.h"
#include "boolequation.h"
#include "Allocator.h"   // <-- добавляем: подключаем аллокатор

class NodeBoolTree
{
#ifdef USE_ALLOCATOR
    DECLARE_ALLOCATOR   // <-- добавляем: аллокатор для класса NodeBoolTree (только если включён)
#endif
public:
    NodeBoolTree(BoolEquation *equation){this->eq = equation;}
    NodeBoolTree(const NodeBoolTree &node){
        this->eq = node.eq;
        this->lt = node.lt;
        this->rt = node.rt;}
    
	NodeBoolTree *lt = nullptr, *rt = nullptr;

	BoolEquation *eq;
};

#endif // NODEBOOLTREE_H
