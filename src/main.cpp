#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include "route_planner/utility.hpp"
#include "route_planner/graph.hpp"
#include "route_planner/map_loader.hpp"
#include "route_planner/router.hpp"
#include "route_planner/visualizer.hpp"

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
    if (!RoutePlanner::MapLoader::loadEdges("data/edges.csv", myMap)) {
        if (!RoutePlanner::MapLoader::loadEdges("../data/edges.csv", myMap)) {
            std::cerr << "Error: Could not find data/edges.csv in current or parent directory." << std::endl;
            return 1;
        }
    }

    std::cout << "========================================" << std::endl;
    std::cout << "   WELCOME TO THE CPP ROUTE PLANNER     " << std::endl;
    std::cout << "========================================" << std::endl;

    std::cout << "Available Locations:" << std::endl;
    for (const auto& [id, node] : myMap.getAllNodes()) {
        std::cout << " - " << node.name << std::endl;
    }

    while(true) {
        std::string startName, endName;

        std::cout << "\nEnter starting location (or 'exit' to quit): ";
        std::getline(std::cin, startName);
        if (startName == "exit") break;

        std::cout << "Enter destination: ";
        std::getline(std::cin, endName);

        int startId = myMap.findIdByName(RoutePlanner::toLower(startName));
        int endId = myMap.findIdByName(RoutePlanner::toLower(endName));

        std::cout << "Start: " << startName << std::endl;
        std::cout << "End: " << endName << std::endl;

        if (startId == -1 || endId == -1) {
            std::cout << "Error: One or both locations not found on the map" << std::endl;
            continue;
        }

        // Benchmark and calculate path
        auto startT = std::chrono::high_resolution_clock::now();
        auto result = RoutePlanner::Router::computePath(myMap, startId, endId);
        auto endT = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endT - startT);

        if (result.success) {
            std::cout << "\n--- Route Found in " << duration.count() << "us ---" << std::endl;
            std::cout << "Total Distance: " << result.totalDist << " units" << std::endl;
            std::cout << "Path: ";
            for (size_t i = 0; i < result.path.size(); ++i) {
                // Get the node name from the ID for a better UX
                std::cout << myMap.getNode(result.path[i])->name 
                          << (i == result.path.size() - 1 ? "" : " -> ");
            }
            std::cout << "\n----------------------------------------" << std::endl;

            // Visualize route in ASCII
            std::cout << "\nMap Visualization:\n" << std::endl;
            RoutePlanner::drawAsciiMap(myMap, result.path);
        } else {
            std::cout << ">> No path exists between these points." << std::endl;
        }
    }

    std::cout << "Exiting Route Planner. Goodbye!" << std::endl;
    return 0;
}