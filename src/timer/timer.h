#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>


class Timer {
public:
    Timer();

    void start();

    void stop();

    double duration() const;

    void print() const;

private:
    using time_point_t = std::chrono::high_resolution_clock::time_point;
    time_point_t t_start_;
    time_point_t t_end_;
    bool timer_stopped_ = false;
};

#endif // !defined TIMER_HPP
