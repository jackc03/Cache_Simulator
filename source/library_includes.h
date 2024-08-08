#ifndef INCLUDES
#define INCLUDES

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdint.h>
#include <array>
#include <string.h>
#include <string>
#include <memory>

//variable that defines whether or not to print debug statements
#define DEBUG 1

//the following may become circular includes if I missunderstand header guards, if there are issues with includes look here first
#include "cache_types.h"
#include "cache_hierarchy.h"

typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

uint32 simple_log_2(int x) {
    int log = 0;
    while (x > 1) {
        x /= 2;
        log++;
    }
    return log; 
}

void debug_print(std::string s) {
    if (DEBUG)
    std::cout << s << std::endl;
}


#endif