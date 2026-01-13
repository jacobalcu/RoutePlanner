#include "route_planner/map_loader.hpp"
#include <fstream> // File stream
#include <sstream> // String stream
#include <iostream> // For debugging

namespace RoutePlanner {
    bool MapLoader::loadNodes(const std::string& filepath, Graph& graph) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open nodes file: " << filepath << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            // Skip comments or empty lines
            if (line.empty() || line[0] == '#') continue;

            // std::stringstream acts like a buffer
            // Feed line into it, then extrat data piece by piece
            std::stringstream ss(line);
            std::string item;

            int id;
            std::string name;
            double x, y;

            // Parsing: ID, Name, X, Y
            // std::getline(ss, item, ',') reads until next comma
            try {
                std::getline(ss, item, ','); id = std::stoi(item);
                std::getline(ss, name, ','); 
                std::getline(ss, item, ','); x = std::stod(item);
                std::getline(ss, item, ','); y = std::stod(item);

                graph.addNode(id, name, x, y);
            } catch(...) {
                // '...' catches all exceptions
                continue;
            }
        }
        return true;
    }

    bool MapLoader::loadEdges(const std::string& filepath, Graph& graph) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open edges file: " << filepath << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            // Skip comments or empty lines
            if (line.empty() || line[0] == '#') continue;

            // std::stringstream acts like a buffer
            // Feed line into it, then extrat data piece by piece
            std::stringstream ss(line);
            std::string item;

            int u, v;
            double distance;

            // Parsing: U, V, Distance
            // std::getline(ss, item, ',') reads until next comma
            try {
                std::getline(ss, item, ','); u = std::stoi(item);
                std::getline(ss, item, ','); v = std::stoi(item);
                std::getline(ss, item, ','); distance = std::stod(item);

                graph.addEdge(u, v, distance);
                graph.addEdge(v, u, distance); // Bidirectional road;
            } catch(...) {
                // '...' catches all exceptions
                continue;
            }
        }
        return true;
    }
}