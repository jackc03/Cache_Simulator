#ifndef CACHE_TYPES_H
#define CACHE_TYPES_H
#include "library_includes.h"


enum LEVEL {L1, L2, L3};

enum REPLACEMENT {LRU, LFU, N_MRU, RANDOM};


class Cache_Block {
    public:
        bool   valid;
        bool   dirty;

        //Index of how recently used a cache block is
        //1 is most recently used, num_ways is least recently used, and 0 is reserved for invalid blocks
        uint8  lru_index;
        uint32 index;
        uint32 data; //maybe unnecessary
        uint64 tag;

};

//TO-DO add all needed logic so stats is updated correctly, this is partially done in the access() function
class Statistics {
    public:

        int accesses;
        int hits;
        int missess;


        int l1_misses;
        int l1_hits;
        
        int l2_misses;
        int l2_hits;
        
        int l3_misses;
        int l3_hits;



        //Number of writes to main memory - does not include writebacks from one level to another, only l3->main memory
        int cache_full_writebacks;

        //Variables to track different types of misses
        //TO-DO implement a way to keep track of what blocks have been accessed before, most likely a vector
        int compulsory_misses;
        int conflict_misses;
};



class Cache {
    protected:
        //Enum holding which level of cache this object represents (L1, L2, L3)
        const LEVEL cache_level;

        //Size of cache in bytes
        const uint64 cache_size;

        //Size of block in bytes
        const uint32 block_size;
                
        //Number of offset bits
        uint32 num_offset_bits;

        //Number of index bits. 
        uint32 num_index_bits;

        //Max number of indexes. 
        uint32 num_indexes;

        //Reference to next level of cache so we can access it on a cache miss
        std::shared_ptr<Cache> next_level;

        //Object to hold all relevant statistics 
        std::shared_ptr<Statistics> stats;

    public:
        //Contructor for Cache, it should initialize every member variable except num_index_bits
        Cache(LEVEL cache_level, uint64 cache_size, uint32 block_size, std::shared_ptr<Statistics> stats, std::shared_ptr<Cache> next_level);
        virtual ~Cache() = default;

        /**
         * @brief Function to make a memory access on this level of memory
         * 
         * @param address: address to access
         * @param access_type: type of access, 1 for read and 2 for write
         * 
         * @return a copy of the cache block that has been accessed.
         * 
         */
        virtual Cache_Block* access(uint64 address, uint8 access_type)  = 0;

};

class Set_Associative_Cache : public Cache {

    protected:
        //Enum holding replacement policy type
        const REPLACEMENT replacement_policy;
        
        //Number of ways this cache has, valid values are [0,255]
        const uint8 num_ways;

        //Array holding all cache blocks and ways
        Cache_Block** blocks;

    public: 
        Set_Associative_Cache(LEVEL cache_level, uint64 cache_size, uint32 block_size, REPLACEMENT replacement_policy,
                                uint8 num_ways, std::shared_ptr<Statistics> stats, std::shared_ptr<Cache> next_level);

        ~Set_Associative_Cache();

        Cache_Block** get_backing_array() {
            return blocks;
        }
        

        Cache_Block* access(uint64 address, uint8 access_type) override;

};

class Direct_Map_Cache : public Cache {
    protected: 
        //Dynamically allocated array that holds tag and data info
        Cache_Block* blocks;
    public:
        Direct_Map_Cache(LEVEL cache_level, uint64 cache_size, uint32 block_size, std::shared_ptr<Statistics> stats, std::shared_ptr<Cache> next_level);

        Cache_Block* access(uint64 address, uint8 access_type) override;
};




#endif