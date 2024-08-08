// #include "library_includes.h"
#include "cache_types.h"
#include "cache_hierarchy.h"

//Program to take in memory traces and simulate the cache hierarchy
int main() {
    std::unique_ptr<Test_Hierarchy> test(new Test_Hierarchy((uint64) 256, (uint32) 4));

    Cache_Block* block = test->access(0b11011000, 1);
    std::cout << block->tag << "\n" << block->index << "\n" << block->valid << "\n" << block->dirty << "\n" << static_cast<int>(block->lru_index) << "\n";
    

    return 0;
}