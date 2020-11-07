//current threads's node/core
// determine CPU and NUMA node on which the calling thread is running

#include "tacc_rdtscp.h"


unsigned long tacc_rdtscp(int *chip, int *core) {
    unsigned long a, d, c;
    __asm__ volatile("rdtscp" : "=a" (a), "=d" (d), "=c" (c));
    *chip = (c & 0xFFF000) >> 12;
    *core = c & 0xFFF;
    return (unsigned long) a | (unsigned long) d << 32;;
}