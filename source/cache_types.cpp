#include "cache_types.h"


Cache::Cache(LEVEL cache_level, uint64 cache_size, uint32 block_size)  : cache_level(cache_level), cache_size(cache_size), block_size(block_size) {
    //Find number of offset bits for later
    num_offset_bits = simple_log_2(block_size);
}




Set_Associative_Cache::Set_Associative_Cache(LEVEL cache_level, uint64 cache_size, uint32 block_size, REPLACEMENT replacement_policy, uint8 num_ways) : Cache(cache_level, cache_size, block_size), replacement_policy(replacement_policy), num_ways(num_ways) {    
    //Finish finding number of index bits
    num_indexes = cache_size/(block_size * num_ways);
    num_index_bits = simple_log_2(num_indexes);

    
    //Allocate memory for array of cache blocks
    blocks = new Cache_Block*[num_indexes];
    for (int i = 0; i < num_indexes; ++i) {
        blocks[i] = new Cache_Block[num_ways]();
    }

    
    // blocks = (Cache_Block**) calloc(num_indexes, sizeof(Cache_Block*));
    // for (int i = 0; i < num_indexes; ++i) {
    //     blocks[i] = (Cache_Block*) calloc(num_ways, sizeof(Cache_Block));
    //     for(int j = 0; j < num_ways; ++i) {
    //         blocks[i][j] = (Cache_Block) calloc(1, sizeof(Cache_Block));
    //     }
    // }
}


Cache* Set_Associative_Cache::access(uint64 address, uint8 access_type) {
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
        }
        if (blocks[index][i].tag == tag) {
            return (Cache*) &blocks[index][i];
        }
    }

    //if 
    if (cache_level == L3 && next_level == 0) {
        //This is a full cache miss, meaning the block was not found in L1, L2, or L3. 
        //Increment statistics 
    } else if (next_level == 0) {
        printf("Current cache level %d does not have a valid reference to next level and is not the highest level of cache", cache_level);
        exit(1);
    } else {

    }


    

    
}

