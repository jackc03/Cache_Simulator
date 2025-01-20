#ifndef CACHE_HIERARCHY_H
#define CACHE_HIERARCHY_H
#include "library_includes.h"
#include "cache_types.h"


class Three_Level_Cache_Hierarchy {
    public:
        // Access times used to calculate AMAT in ns
        // Default values are 2, 10, 20, 100 respectively
        const double L1_access_time, L2_access_time, L3_access_time, DRAM_access_time;
        std::shared_ptr<Set_Associative_Cache> L1;
        std::shared_ptr<Set_Associative_Cache> L2;
        std::shared_ptr<Set_Associative_Cache> L3;

        Three_Level_Cache_Hierarchy(uint64 l1_cache_size, uint64 l2_cache_size, uint64 l3_cache_size, uint32 block_size, REPLACEMENT replacement_policy, uint8 associativity) 
                                    : L1_access_time(L1_access_time), L2_access_time(L2_access_time), L3_access_time(L3_access_time), DRAM_access_time(DRAM_access_time) {
            // std::shared_ptr<Statistics> stats(new Statistics(), double L1_access_time = 2.0, double L2_access_time = 10.0, double L3_access_time = 20, double DRAM_access_time = 100.0);
            
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