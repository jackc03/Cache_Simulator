#include "includes.h"
#ifndef CACHE_H
#define CACHE_H

enum LEVEL {L1, L2, L3};

enum REPLACEMENT {LRU, LFU, MRU, RANDOM};


class Cache_Block {
    bool   valid;
    bool   dirty;
    uint32 lru_index;
    uint32 index;
    uint32 tag;
    uint32 data; //maybe unnecessary
};



class Cache {
    protected:
        //Enum holding which level of cache this object represents (L1, L2, L3)
        const LEVEL cache_level;

        //Size of cache in bytes
        const uint64 size;

        //Size of block in bytes - May be unneccesary
        const uint8 block_size;



    public:
        virtual uint32 access(uint64 address) = 0;

};

class Set_Associative_Cache : Cache{

    protected:
        //Enum holding replacement policy type
        const REPLACEMENT replacement_policy;
        
        //Number of ways this cache has, valid values are [0,255]
        const uint8 ways;

        //Array holding all cache blocks and ways
        Cache_Block **blocks;

    public: 
        uint32 access(uint64 address) override;

};

class Direct_Map_Cache : Cache {
    protected: 
        //Dynamically allocated array that holds tag and data info
        Cache_Block* blocks;
    public:
        uint32 access(uint64 address) override;
};




#endif