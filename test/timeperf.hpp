//
//  timeperf.hpp
//  timeperf
//
//  Created by larryhou on 2023/4/21.
//

#ifndef timeperf_hpp
#define timeperf_hpp

#include <iostream>
#include <vector>
#include <stack>

#ifdef __APPLE__
#include <mach/mach_time.h>
#endif

namespace timeperf {
struct node;
using nodeptr = std::shared_ptr<node>;

struct node {
    int32_t id;
    int64_t time;
    int64_t elapse;
    std::vector<nodeptr> nodes;
    
public:
    node(int32_t id, int64_t time);
    ~node();
    
    std::ostream& dump(std::ostream &out, int level = 0);
    
private:
    std::ostream& indent(std::ostream &out, int level);
};

class perf {
#ifdef __APPLE__
    mach_timebase_info_data_t info;
#endif
    std::stack<nodeptr> stack;
    
private:
    int64_t gettime();
    
public:
    perf();
    static perf shared;
    void enter(int32_t id);
    nodeptr exit();
};

struct point {
    point(int32_t id);
    ~point();
};

inline void enter(int32_t id) { perf::shared.enter(id); }
inline nodeptr exit() { return perf::shared.exit(); }

}

#endif /* timeperf_hpp */
