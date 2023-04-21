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

#include <sys/time.h>

namespace timeperf {
struct time {
    int64_t sec;
    int64_t nanosec;
    
    time operator -(const time &v) const;
    time operator +(const time &v) const;
};

struct node;
using nodeptr = std::shared_ptr<node>;

struct node {
    int32_t id;
    time time;
    uint64_t elapse;
    std::vector<nodeptr> nodes;
    
public:
    node(int32_t id, struct time time);
    ~node();
    
    std::ostream& dump(std::ostream &out, int level = 0);
    
private:
    std::ostream& indent(std::ostream &out, int level);
};

class perf {
    std::stack<nodeptr> stack;
    
private:
    time gettime();
    
public:
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
