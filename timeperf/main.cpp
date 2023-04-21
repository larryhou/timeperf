//
//  main.cpp
//  timeperf
//
//  Created by larryhou on 2023/4/20.
//

#include "test.hpp"
#include "timeperf.hpp"

#include <sstream>

int main(int argc, const char * argv[]) {
    timeperf::enter(0);
    runtest();
    timeperf::exit()->dump(std::cout) << std::endl;
    return 0;
}
