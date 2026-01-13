#include <iostream>
#include "route_planner/graph.hpp"
#include "route_planner/map_loader.hpp"
#include "route_planner/router.hpp"

// Not using namespace "RoutePlanner"
// Prefix with RoutePlanner:: to know where classes come from

int main() {
    RoutePlanner::Graph myMap;

    std::cout << "--- Route Planner Initializing ---" << std::endl;

    // Attempt to load nodes
    if (!RoutePlanner::MapLoader::loadNodes("data/nodes.csv", myMap)) {
        if (!RoutePlanner::MapLoader::loadNodes("../data/nodes.csv", myMap)) {
            std::cerr << "Error: Could not find data/nodes.csv in current or parent directory." << std::endl;
            return 1;
        }
    }

    // Attempt to load edges
    // if (RoutePlanner::MapLoader::loadEdges("data/edges.csv", myMap)) {
    //     std::cout << "Edges loaded successfully." << std::endl;
    // } else {
    //     std::cerr << "Failed to load edges." << std::endl;
    //     return 1; // Exit with error
    // }
    if (!RoutePlanner::MapLoader::loadEdges("data/edges.csv", myMap)) {
        if (!RoutePlanner::MapLoader::loadEdges("../data/edges.csv", myMap)) {
            std::cerr << "Error: Could not find data/edges.csv in current or parent directory." << std::endl;
            return 1;
        }
    }

    // Verify data
    const auto& allNodes = myMap.getAllNodes();
    std::cout << "Total nodes in graph: " << allNodes.size() << std::endl;

    // Print neighbors of Node 1 to see if edges linked correctly
    const auto* node1 = myMap.getNode(1);
    if (node1) {
        std::cout << "Neighbors of " << node1->name << ":" << std::endl;
        for (const auto& edge : node1->neighbors) {
            std::cout << " -> Connects to Node ID: " << edge.targetNodeID
                        << " (Distance: " << edge.distance << ")" << std::endl;
        }
    }

    // Test Dijkstra's Algorithm
    RoutePlanner::RouteResult result = RoutePlanner::Router::computePath(myMap, 1, 5);
    if (result.success) {
        std::cout << "Path found from Node 1 to Node 5:" << std::endl;
        for (int nodeId : result.path) {
            std::cout << " -> Node ID: " << nodeId << std::endl;
        }
        std::cout << "Total Distance: " << result.totalDist << std::endl;
    } else {
        std::cout << "No path found from Node 1 to Node 5." << std::endl;
    }

    return 0;
}