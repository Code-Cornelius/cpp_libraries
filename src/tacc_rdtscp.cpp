//
// Created by nie_k on 24/10/2020.
//

#include "tacc_rdtscp.h"


unsigned long tacc_rdtscp(int *chip, int *core) {
    unsigned long a, d, c;
    __asm__ volatile("rdtscp" : "=a" (a), "=d" (d), "=c" (c));
    *chip = (c & 0xFFF000) >> 12;
    *core = c & 0xFFF;
    return (unsigned long) a | (unsigned long) d << 32;;
}