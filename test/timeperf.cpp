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

time time::operator -(const time &v) const {
    time r{sec-v.sec, nanosec-v.nanosec};
    if (r.nanosec < 0) {
        r.nanosec += NANOSECONDS_PER_SECOND;
        r.sec--;
    }
    return r;
}

time time::operator +(const time &v) const {
    time r{sec+v.sec, nanosec+v.nanosec};
    if (r.nanosec >= NANOSECONDS_PER_SECOND) {
        r.nanosec -= NANOSECONDS_PER_SECOND;
        r.sec++;
    }
    return r;
}

node::node(int32_t id, struct time time): id(id), time(time) { }

std::ostream& node::dump(std::ostream &out, int level)  {
    indent(out, level) << "[" << id << "] " << elapse / 1000 << '\n';
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

inline time perf::gettime() {
    struct timeval tv;
    gettimeofday(&tv, 0);
    return {static_cast<int64_t>(tv.tv_sec), static_cast<int64_t>(tv.tv_usec * 1000)};
}

void perf::enter(int32_t id) {
    auto node = std::make_shared<struct node>(id, gettime());
    if (stack.size()) { stack.top()->nodes.push_back(node); }
    stack.push(node);
}

nodeptr perf::exit() {
    auto top = stack.top();
    auto dur = gettime() - top->time;
    top->elapse = dur.sec * NANOSECONDS_PER_SECOND + dur.nanosec;
    stack.pop();
    return top;
}

point::point(int32_t id) { perf::shared.enter(id); }
point::~point() { perf::shared.exit(); }

}



