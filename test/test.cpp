//
//  test.cpp
//  timeperf
//
//  Created by larryhou on 2023/4/20.
//

#include "test.hpp"
#include "timeperf.hpp"

#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <chrono>

#ifdef __APPLE__
#include <mach/mach_time.h>
#endif

void measure(std::function<void()> method) {
    int64_t total = 0;
    static const int REPEAT_COUNT = 10;
    static const int SAMPLE_COUNT = 1000000;
    
    for (auto i = 0; i < REPEAT_COUNT; i++) {
        auto beg = std::chrono::high_resolution_clock::now();
        for (auto i = 0; i < SAMPLE_COUNT; i++) {method();}
        auto end = std::chrono::high_resolution_clock::now();
        auto elapse = std::chrono::duration_cast<std::chrono::nanoseconds>(end - beg).count();
        std::cout << '#' << i << ' ' << elapse << std::endl;
        total += elapse;
    }
    std::cout << '#' << 'M' << ' ' << total / REPEAT_COUNT << ' ' << total / REPEAT_COUNT / SAMPLE_COUNT << std::endl;
    
}

extern "C" void runtest() {
    timeperf::point _(1);
    
    timeperf::enter(2);
    struct timeval tv;
    std::cout << "gettimeofday" << std::endl;
    timeperf::enter(3);
    measure([&](){ gettimeofday(&tv, 0); });
    timeperf::exit();
    timeperf::exit();
    
    timeperf::enter(4);
    std::cout << "clock" << std::endl;
    measure([&](){ clock(); });
    timeperf::exit();
    
    timeperf::enter(5);
    std::cout << "std::chrono::high_resolution_clock::now" << std::endl;
    measure([&](){ std::chrono::high_resolution_clock::now(); });
    timeperf::exit();
    
    timeperf::enter(6);
    std::cout << "std::chrono::system_clock::now" << std::endl;
    measure([&](){ std::chrono::system_clock::now(); });
    timeperf::exit();
    
    timeperf::enter(7);
    std::cout << "std::chrono::steady_clock::now" << std::endl;
    measure([&](){ std::chrono::steady_clock::now(); });
    timeperf::exit();
    
    timeperf::enter(8);
    std::cout << "std::chrono::steady_clock::now" << std::endl;
    measure([&](){ std::chrono::steady_clock::now(); });
    timeperf::exit();
    
    timeperf::enter(9);
    struct timespec tp;
    std::cout << "clock_gettime(CLOCK_MONOTONIC)" << std::endl;
    measure([&](){ clock_gettime(CLOCK_MONOTONIC, &tp); });
    timeperf::exit();
    
    timeperf::enter(10);
    std::cout << "clock_gettime(CLOCK_PROCESS_CPUTIME_ID)" << std::endl;
    measure([&](){ clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp); });
    timeperf::exit();
    
#ifdef __APPLE__
    timeperf::enter(11);
    std::cout << "mach_absolute_time:" << std::endl;
    measure([&](){ mach_absolute_time(); });
    timeperf::exit();
#endif
}
