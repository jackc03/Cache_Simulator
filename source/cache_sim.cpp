// #include "library_includes.h"
#include "cache_types.h"
#include "cache_hierarchy.h"

//List of tests
void single_level_basic_cache_test(std::shared_ptr<Single_Level_Test_Hierarchy> test);


int next_access(std::shared_ptr<Three_Level_Cache_Hierarchy> cache_hierarchy,FILE* trace_file) {
    if (feof(trace_file) || ferror(trace_file)) return 0;
    else {
        int t;
        unsigned long long address, instr;
        fscanf(trace_file, "%d %llx %llx\n", &t, &address, &instr);
        cache_hierarchy->access(address, t);
    }
    return 1;
}



//Program to take in memory traces and simulate the cache hierarchy
int main() {
    //TO-DO implement parameters and default arguements from commandline

    //declare some important variables that will need to be set
    FILE* input_file;
    uint64 l1_cache_size, l2_cache_size, l3_cache_size;
    l1_cache_size = l2_cache_size = l3_cache_size = 4096;
    uint64 block_size = 32;
    REPLACEMENT replacement_policy = LRU;
    uint8 associativity = 8;

    //Make actual hierarchy
    std::shared_ptr<Three_Level_Cache_Hierarchy> cache_hierarchy(new Three_Level_Cache_Hierarchy(l1_cache_size, l2_cache_size, l3_cache_size, block_size, replacement_policy, associativity));

    //iterate through and do each access
    while (next_access(cache_hierarchy, input_file));



    return 0;
}







void single_level_basic_cache_test(std::shared_ptr<Single_Level_Test_Hierarchy> test) {

    Cache_Block* block = test->access(0b11011000, 0);
    // std::cout << block->tag << "\n" << block->index << "\n" << block->valid << "\n" << block->dirty << "\n" << static_cast<int>(block->lru_index) << "\n";
    assert(block->tag == 3);
    assert(block->index == 6);
    assert(block->dirty == 0);
    assert(block->valid == 1);

    block = test->access(0b11011000, 1);
    assert(block->tag == 3);
    assert(block->index == 6);
    assert(block->dirty == 1);
    assert(block->valid == 1);

    block = test->access(0b11011000, 0);
    assert(block->tag == 3);
    assert(block->index == 6);
    assert(block->dirty == 1);
    assert(block->valid == 1);


}