#include "cache_types.h"

uint32 simple_log_2(int x) {
    int log = 0;
    while (x > 1) {
        x /= 2;
        log++;
    }
    return log; 
}


Cache::Cache(LEVEL cache_level, uint64 cache_size, uint32 block_size, std::shared_ptr<Statistics> stats, std::shared_ptr<Cache> next_level) : cache_level(cache_level), cache_size(cache_size), block_size(block_size), next_level(next_level) {
    //Find number of offset bits for later
    num_offset_bits = simple_log_2(block_size);
    this->stats = stats;
}




Set_Associative_Cache::Set_Associative_Cache(LEVEL cache_level, uint64 cache_size, uint32 block_size, REPLACEMENT replacement_policy, uint8 num_ways, std::shared_ptr<Statistics> stats, std::shared_ptr<Cache> next_level) : Cache(cache_level, cache_size, block_size, stats, next_level), replacement_policy(replacement_policy), num_ways(num_ways) {    
    //Finish finding number of index bits
    num_indexes = cache_size/(block_size * num_ways);
    num_index_bits = simple_log_2(num_indexes);

    
    //Allocate memory for array of cache blocks
    blocks = new Cache_Block*[num_indexes];
    for (int i = 0; (uint32) i < num_indexes; ++i) {
        blocks[i] = new Cache_Block[num_ways]();
    }
}

Set_Associative_Cache::~Set_Associative_Cache() {
    for (int i = 0; (uint32) i < num_indexes; ++i) {
        delete blocks[i];
    }
    delete blocks;
}


Cache_Block* Set_Associative_Cache::access(uint64 address, uint8 access_type) {
    //Make bit masks to extract index and tag
    uint64 index_mask = ((1 << num_index_bits) - 1) << num_offset_bits;
    uint64 tag_mask   = ((1 << (64 - (num_index_bits + num_offset_bits))) - 1) << (num_index_bits + num_offset_bits);

    
    //Use bitmasks to extract index and tag
    uint64 index = index_mask & address;
    uint64 tag   = tag_mask   & address;
    index = index >> num_offset_bits;
    tag   = tag   >> (num_index_bits + num_offset_bits);

    //index of which way at specified index is empty, if no indexes are empty then cache will follow specified replacement policy
    int invalid_way = -1;
    for (int i = 0; i < num_ways; ++i) {
        if(blocks[index][i].valid == 0) {
            invalid_way = i;
            blocks[index][i].lru_index = 0;
        }

        if (blocks[index][i].tag == tag) {
            int prev_index = blocks[index][i].lru_index;
            for (int j = 0; j < num_ways; ++j) {
                if (blocks[index][j].lru_index > prev_index) {
                    blocks[index][j].lru_index--;
                }
            }
            blocks[index][i].lru_index = 1;

            return &blocks[index][i];
        }
    }
    stats->l3_misses++;
    stats->full_cache_misses++;
    //if 
    if (cache_level == L3 && next_level == 0) {
        //This is a full cache miss, meaning the block was not found in L1, L2, or L3. 
        //Increment statistics, pull a new cache block, and follow replacement policy

        //TO-DO add logic to determine the type of cache miss and increment the appropriate statistic

        //implement logic for different access types, read/write/instruction_fetch

        int i = 0;
        if (invalid_way == -1) {
            //follow replacement policy
            if (replacement_policy == LRU || 1) {
                for (i = 0; i < num_ways; ++i) {
                    if (blocks[index][i].lru_index == num_ways) {
                        break;
                    }
                }

                int prev_index = blocks[index][i].lru_index;
                blocks[index][i].lru_index = 1;
                for (int j = 0; j < num_ways; ++j) {
                    if (blocks[index][j].lru_index > prev_index) {
                        blocks[index][j].lru_index--;
                    }
                }
            }
        } else {
            i = invalid_way;
        }


        Cache_Block* target = new Cache_Block();
        target->index = index;
        target->tag   = tag;
        target->valid = 1;
        target->lru_index = (uint8)1;
        target->dirty = access_type == 2 ? 1 : 0;

        memcpy(&blocks[index][i], target, sizeof(Cache_Block));
        delete target;
        return &blocks[index][i];

    } else if (next_level == 0) {
        printf("Current cache level %d does not have a valid reference to next level and is not the highest level of cache", cache_level);
        exit(1);
    } else {
        int i = 0;
        

        if (invalid_way == -1) {
            //follow replacement policy
            if (replacement_policy == LRU || 1) {
                for (i = 0; i < num_ways; ++i) {
                    if (blocks[index][i].lru_index == num_ways) {
                        break;
                    }
                }

                int prev_index = blocks[index][i].lru_index;
                blocks[index][i].lru_index = 1;
                for (int j = 0; j < num_ways; ++j) {
                    if (blocks[index][j].lru_index > prev_index) {
                        blocks[index][j].lru_index--;
                    }
                }
            }
        } else {
            i = invalid_way;
        }

        //TO-DO finish access part for L1 and L2
        if (blocks[index][i].valid && blocks[index][i].dirty) {
            //TO-DO recreate address from tag and index and write block back to next level of memory

        }

        Cache_Block* retrieved = next_level->access(address, access_type);
        memcpy(&blocks[index][i], retrieved, sizeof(Cache_Block));
        blocks[index][i].lru_index = 1;
        blocks[index][i].dirty = access_type == 2? 1 : 0;
        if (!blocks[index][i].valid) {
            printf("block came back as not valid, gdb from this point.\n");
            exit(1);
        }
        
        return &blocks[index][i];

    }


}

