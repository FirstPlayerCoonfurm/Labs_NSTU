#include "timer.h"

Timer::Timer() : start_(std::chrono::high_resolution_clock::now()) {}

void Timer::reset() {
    start_ = std::chrono::high_resolution_clock::now();
}

double Timer::elapsed() const {
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start_).count();
}
