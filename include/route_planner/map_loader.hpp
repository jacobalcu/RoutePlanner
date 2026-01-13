#ifndef MAP_LOADER_HPP
#define MAP_LOADER_HPP

#include "route_planner/graph.hpp"
#include <string>

namespace RoutePlanner {
    class MapLoader {
        public:
            // static: method belongs to class, not instance
            // Return true if successful, false otherwise
            // pass 'Graph& graph' by ref to modify original object
            static bool loadNodes(const std::string& filepath, Graph& graph);
            static bool loadEdges(const std::string& filepath, Graph& graph);
    };
}

#endif