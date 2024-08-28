#ifndef CACHE_HIERARCHY_H
#define CACHE_HIERARCHY_H
#include "library_includes.h"
#include "cache_types.h"


class Three_Level_Cache_Hierarchy {
    public:
        std::shared_ptr<Set_Associative_Cache> L1;
        std::shared_ptr<Set_Associative_Cache> L2;
        std::shared_ptr<Set_Associative_Cache> L3;

        Three_Level_Cache_Hierarchy(uint64 l1_cache_size, uint64 l2_cache_size, uint64 l3_cache_size, uint32 block_size, REPLACEMENT replacement_policy, uint8 associativity) {
            std::shared_ptr<Statistics> stats(new Statistics());
            
            L3 = std::shared_ptr<Set_Associative_Cache>(new Set_Associative_Cache(LEVEL::L3, l3_cache_size, block_size, replacement_policy, associativity, stats, nullptr));
            L2 = std::shared_ptr<Set_Associative_Cache>(new Set_Associative_Cache(LEVEL::L2, l2_cache_size, block_size, replacement_policy, associativity, stats, std::dynamic_pointer_cast<Cache>(L3)));
            L1 = std::shared_ptr<Set_Associative_Cache>(new Set_Associative_Cache(LEVEL::L1, l1_cache_size, block_size, replacement_policy, associativity, stats, std::dynamic_pointer_cast<Cache>(L2)));

        }

        Cache_Block* access(uint64 address, uint8 access_type) {
            return L1->access(address, access_type);
        }
};
class Single_Level_Test_Hierarchy {
    public:
        std::shared_ptr<Set_Associative_Cache> L3;

        Single_Level_Test_Hierarchy(uint64 cache_size, uint32 block_size) {
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