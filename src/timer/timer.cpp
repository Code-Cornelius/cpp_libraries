#include "timer.h"

#include <stdexcept>
#include <iostream>

using namespace std;
using namespace chrono;
Timer::Timer() {
  t_start_ = high_resolution_clock::now();
}


void Timer::stop() {
  t_end_ = high_resolution_clock::now();
#ifndef NDEBUG
    if (!timer_stopped_) {
        timer_stopped_ = true;
    } else { throw logic_error("The Timer has already been stopped."); }
#endif
}

double Timer::duration() const {
  return std::chrono::duration< double >(t_end_ - t_start_).count();
}

void Timer::print() const{
    std::cout << "Computed call in " << duration() << " seconds." << std::endl;

}