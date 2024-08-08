#ifndef CACHE_HIERARCHY_H
#define CACHE_HIERARCHY_H
#include "library_includes.h"

class Test_Hierarchy {
    public:
        Set_Associative_Cache* L3;

        Test_Hierarchy(uint64 cache_size, uint32 block_size) {
            std::shared_ptr<Statistics> stats;
            L3 = new Set_Associative_Cache(LEVEL::L3, cache_size, block_size, REPLACEMENT::LRU, (uint8)4, stats);
        }
};


#endif