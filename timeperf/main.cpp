//
//  main.cpp
//  timeperf
//
//  Created by larryhou on 2023/4/20.
//

#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <chrono>

#ifdef __APPLE__
#include <mach/mach_time.h>
#endif

void measure(std::function<void()> method) {
    for (auto i = 0; i < 3; i++) {
        auto beg = std::chrono::system_clock::now();
        for (auto i = 0; i < 1000000; i++) {method();}
        auto end = std::chrono::system_clock::now();
        auto elapse = std::chrono::duration_cast<std::chrono::nanoseconds>(end - beg).count();
        std::cout << i << ": " << elapse << std::endl;
    }
}

int main(int argc, const char * argv[]) {
    struct timeval tv;
    std::cout << "gettimeofday:" << std::endl;
    measure([&](){ gettimeofday(&tv, 0); });
    
    std::cout << "clock:" << std::endl;
    measure([&](){ clock(); });
    
    std::cout << "system_clock:" << std::endl;
    measure([&](){ std::chrono::system_clock::now(); });
    
    std::cout << "steady_clock:" << std::endl;
    measure([&](){ std::chrono::steady_clock::now(); });
    
    std::cout << "steady_clock:" << std::endl;
    measure([&](){ std::chrono::steady_clock::now(); });
    
    struct timespec tp;
    std::cout << "clock_gettime(CLOCK_MONOTONIC):" << std::endl;
    measure([&](){ clock_gettime(CLOCK_MONOTONIC, &tp); });
    
    std::cout << "clock_gettime(CLOCK_PROCESS_CPUTIME_ID):" << std::endl;
    measure([&](){ clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &tp); });
    
#ifdef __APPLE__
    std::cout << "mach_absolute_time:" << std::endl;
    measure([&](){ mach_absolute_time(); });
#endif
    return 0;
}
