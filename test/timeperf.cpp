//
//  timeperf.cpp
//  timeperf
//
//  Created by larryhou on 2023/4/21.
//

#include "timeperf.hpp"

#define NANOSECONDS_PER_SECOND 1000000000

namespace timeperf {
perf perf::shared;

node::node(int32_t id, int64_t time): id(id), time(time) { }

std::ostream& node::dump(std::ostream &out, int level)  {
    indent(out, level) << "[" << id << "] " << elapse << '\n';
    for (auto i = 0; i < nodes.size(); i++) { nodes[i]->dump(out, level + 1); }
    return out;
}

inline std::ostream& node::indent(std::ostream &out, int level) {
    for (auto i = 0; i < level; i++) { out << "    "; }
    return out;
}

node::~node() {
//    printf("~node %d\n", id);
}

perf::perf() {
#ifdef __APPLE__
    mach_timebase_info(&info);
#endif
}

inline int64_t perf::gettime() {
#ifdef __APPLE__
    return mach_absolute_time();
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * NANOSECONDS_PER_SECOND + ts.tv_nsec;
#endif
}

void perf::enter(int32_t id) {
    auto node = std::make_shared<struct node>(id, gettime());
    if (stack.size()) { stack.top()->nodes.push_back(node); }
    stack.push(node);
}

nodeptr perf::exit() {
    auto top = stack.top();
    top->elapse = gettime() - top->time;
#ifdef __APPLE__
    top->elapse = top->elapse * info.numer / info.denom;
#endif
    stack.pop();
    return top;
}

point::point(int32_t id) { perf::shared.enter(id); }
point::~point() { perf::shared.exit(); }

}



