//
// Created by jack on 1/1/19.
//

#include <cstdint>
#include <cstdio>


void dumpData(uint8_t* in, int len) {
    for ( int i = 0; i < len; i++ ) {
        if ( i % 16 == 0 ) { printf("\n"); }
        printf("%02x ", in[i]);
    }
    printf("\n");
}