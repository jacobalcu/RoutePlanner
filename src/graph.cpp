#include "route_planner/graph.hpp"
#include <stdexcept>

namespace route_planner {
    void Graph::addNode(int id, const std::string& name, double x, double y) {
        // Use ID as key to insert new Node
        // If ID already exists, this will overwrite it
        nodes[id] = Node{id, name, x, y, {}};
    }

    void Graph::addEdge(int u, int v, double weight) {
        // Find node 'u' in map
        // .find() safer than []
        // [] will create a new entry if key not found
        auto it = nodes.find(u);

        // Loop over all nodes
        if (it != nodes.end()) {
            // it->second refers to Node object assoc with ID
            it->second.neighbors.push_back(Edge{v, weight});
        } else {
            // throw exception to be caught elsewhere
            throw std::runtime_error("Source node " + std::to_string(u) + " not found.");
        }
    }

    const Node* Graph::getNode(int id) const {
        auto it = nodes.find(id);
        if (it != nodes.end()) {
            // Return address of Node in map
            return &(it->second);
        }
        return nullptr; // Not found
    }

    const std::unordered_map<int, Node>& Graph::getAllNodes() const {
        return nodes;
    }
}