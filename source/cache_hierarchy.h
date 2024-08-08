#ifndef CACHE_HIERARCHY_H
#define CACHE_HIERARCHY_H
#include "library_includes.h"
#include "cache_types.h"

class Test_Hierarchy {
    public:
        std::shared_ptr<Set_Associative_Cache> L3;

        Test_Hierarchy(uint64 cache_size, uint32 block_size) {
            std::shared_ptr<Statistics> stats(new Statistics());
            // L3.reset(new Set_Associative_Cache(LEVEL::L3, cache_size, block_size, REPLACEMENT::LRU, (uint8)4, stats, nullptr));
            L3 = std::shared_ptr<Set_Associative_Cache>(new Set_Associative_Cache(LEVEL::L3, cache_size, block_size, REPLACEMENT::LRU, (uint8)4, stats, nullptr));
        }

        Cache_Block* access (uint64 address, uint8 access_type) {
            return L3->access(address, access_type);
        }
        std::shared_ptr<Set_Associative_Cache> get_cache() {
            return L3;
        }
};


#endif