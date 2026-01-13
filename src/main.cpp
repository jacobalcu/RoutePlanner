#include <iostream>
#include "route_planner/graph.hpp"
#include "route_planner/map_loader.hpp"

// Not using namespace "RoutePlanner"
// Prefix with RoutePlanner:: to know where classes come from

int main() {
    RoutePlanner::Graph myMap;

    std::cout << "--- Route Planner Initializing ---" << std::endl;

    // Attempt to load nodes
    // if (RoutePlanner::MapLoader::loadNodes("data/nodes.csv", myMap)) {
    //     std::cout << "Nodes loaded successfully." << std::endl;
    // } else {
    //     std::cerr << "Failed to load nodes." << std::endl;
    //     return 1; // Exit with error
    // }
    if (!RoutePlanner::MapLoader::loadNodes("data/nodes.csv", myMap)) {
        if (!RoutePlanner::MapLoader::loadNodes("../data/nodes.csv", myMap)) {
            std::cerr << "Error: Could not find data/nodes.csv in current or parent directory." << std::endl;
            return 1;
        }
    }

    // Attempt to load edges
    if (RoutePlanner::MapLoader::loadEdges("data/edges.csv", myMap)) {
        std::cout << "Edges loaded successfully." << std::endl;
    } else {
        std::cerr << "Failed to load edges." << std::endl;
        return 1; // Exit with error
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

    return 0;
}