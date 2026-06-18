#include "NodeBoolTree.h"

#ifdef USE_ALLOCATOR
// <-- добавляем: реализация аллокатора для класса NodeBoolTree (только если включён)
// 0 = неограниченное количество блоков из кучи (режим HEAP_BLOCKS)
IMPLEMENT_ALLOCATOR(NodeBoolTree, 0, nullptr)
#endif