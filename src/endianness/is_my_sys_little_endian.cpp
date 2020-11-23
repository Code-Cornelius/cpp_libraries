#include "is_my_sys_little_endian.h"

bool is_my_sys_little_endian() {

    int one = 1; // 32-bit integer
    char *p = reinterpret_cast<char *>(&one);
    bool little = p[0]; //check the first byte
    if (little) {
        return true;
    } else {
        return false;
    }
}
