#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <unordered_map>

namespace route_planner {
    // Rep directed connection from one node to another
    struct Edge {
        int targetNodeID;
        double distance;
    };

    // Rep a point on the map
    struct Node {
        int id;
        std::string name;
        double x, y; // Coords for A* heuristic
        std::vector<Edge> neighbors; // Adjacency list
    };

    class Graph {
    public:
        // Default constructor  
        Graph() = default;

        // Add Node to the map
        // 'const std::string& name' pass by reference to avoid copying, const to prevent modification
        void addNode(int id, const std::string& name, double x, double y);

        // Create connection between two nodes
        // Call twice for bidirectional road
        void addEdge(int u, int v, double distance);

        // Return pointer to node by ID, nullptr if not found
        const Node* getNode(int id) const;

        // Return entire map
        // const at end ensures method does not modify class members
        const std::unordered_map<int, Node>& getAllNodes() const;
    private:
        // Hash map provides O(1) lookup
        // Key: Node ID, Value: Node struct
        std::unordered_map<int, Node> nodes;
    };
};

#endif