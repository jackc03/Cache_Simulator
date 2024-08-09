// #include "library_includes.h"
#include "cache_types.h"
#include "cache_hierarchy.h"

//List of tests
void single_level_basic_cache_test();




//Program to take in memory traces and simulate the cache hierarchy
int main() {
    single_level_basic_cache_test();
    return 0;
}







void single_level_basic_cache_test() {
    std::unique_ptr<Single_Level_Test_Hierarchy> test(new Single_Level_Test_Hierarchy((uint64) 256, (uint32) 4));

    Cache_Block* block = test->access(0b11011000, 1);
    // std::cout << block->tag << "\n" << block->index << "\n" << block->valid << "\n" << block->dirty << "\n" << static_cast<int>(block->lru_index) << "\n";
    assert(block->tag == 3);
    assert(block->index == 6);
    assert(block->dirty == 0);
    assert(block->valid == 1);


}