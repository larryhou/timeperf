//
//  main.cpp
//  timeperf
//
//  Created by larryhou on 2023/4/20.
//

#include "test.hpp"

#ifndef TARGET_OS_IPHONE
int main(int argc, const char * argv[]) {
    runtest();
    return 0;
}
#endif
