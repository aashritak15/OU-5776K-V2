#pragma once

#include <stdint.h>
#include <cstddef>

extern "C" {

typedef struct __attribute__((__packed__)) _asset {
        uint8_t* buf;
        size_t size;
} asset;
}

#define ASSET(x)                                                                                                       
    extern "C" {                                                                                                       
    extern uint8_t _binary_static_x_start[], _binary_static_x_size[];                                          
    static asset x = {_binary_static_x_start, (size_t)_binary_static_x_size};                                  
    }