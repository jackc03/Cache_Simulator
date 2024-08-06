#ifndef INCLUDES
#define INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <array>

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


#endif