#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdint.h>
#include <array>
#include <string.h>
#include <string>
#include <memory>
#include <cstdint>
#include <cassert>

//variable that defines whether or not to print debug statements
#define DEBUG 1

//the following may become circular includes if I missunderstand header guards, if there are issues with includes look here first
// #include "cache_types.h"
// #include "cache_hierarchy.h"

typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;


#endif