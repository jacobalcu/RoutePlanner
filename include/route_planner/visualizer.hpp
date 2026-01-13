#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include "route_planner/graph.hpp"
#include <vector>

namespace RoutePlanner {
    // The "Promise" to the compiler
    void drawAsciiMap(const Graph& graph, const std::vector<int>& path);
}

#endif