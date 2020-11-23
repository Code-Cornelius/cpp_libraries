#include "tacc_rdtscp.h"
#include "timer.h"


int main(){
    Timer timer;

    for (size_t i{0}; i < int(1E10); ++i) {
        i++;
    }
    timer.stop();
    timer.print();
    return 0;
}
