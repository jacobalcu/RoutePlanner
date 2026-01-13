#ifndef ROUTER_HPP
#define ROUTER_HPP

#include "graph.hpp"
#include <vector>
#include <unordered_map>

namespace RoutePlanner {

    // Stor result of pathfinding op in struct
    struct RouteResult {
        std::vector<int> path; // Seq of Node IDs
        double totalDist; // Sum of edge weights
        bool success; // True if path found
    };

    class Router {
        public:
            // pass 'const Graph&' bc router should read map, not modify it
            static RouteResult computePath(const Graph& graph, int startId, int endId);
    };
}

#endif