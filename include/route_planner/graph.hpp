#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <unordered_map>

namespace route_planner {
    struct Edge {
        int targetNodeID;
        double distance;
    };

    struct Node {
        int id;
        std::string name;
        double x, y; // Coords for A* heuristic
        std::vector<Edge> neighbors;
    };

    class Graph {
    public:
        void addNode(int id, const std::string& name, double x, double y);
        void addEdge(int u, int v, double distance);

        const Node* getNode(int id) const;
        const std::unordered_map<int, Node>& getAllNodes() const;
    private:
        std::unordered_map<int, Node> nodes;
    };
};

#endif