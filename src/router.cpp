#include "route_planner/router.hpp"
#include <queue>
#include <limits>
#include <algorithm>

namespace RoutePlanner {

    // helper struct for priority queue
    struct NodeDistance {
        int id;
        double dist;

        // Overload 'greater than' op
        // std::priority_queue uses max-heap by default
        // We want min-heap behavior
        bool operator>(const NodeDistance& other) const {
            return dist > other.dist;
        }
    };

    RouteResult Router::computePath(const Graph& graph, int startId, int endId) {
        // Setup Data Structures
        // Stores shortest known distance to each node
        // Key: Node ID, Value: Distance from start
        std::unordered_map<int, double> distances;

        // Stores "parent" of each node for path reconstruction
        // Key: Node ID, Value: Parent Node ID
        std::unordered_map<int, int> parents;

        // Min-heap priority queue to select next node with smallest distance
        // Priority Queue: <Type, Container, Comparator>
        std::priority_queue<NodeDistance, std::vector<NodeDistance>, std::greater<NodeDistance>> pq;

        // Init all distances to infinity
        for (const auto& pair : graph.getAllNodes()) {
            distances[pair.first] = std::numeric_limits<double>::infinity();
        }

        // Start algo
        distances[startId] = 0.0;
        pq.push({startId, 0.0});

        bool found = false;

        while(!pq.empty()) {
            // Get node with smallest distance in pq
            NodeDistance current = pq.top();
            pq.pop();

            // If we reached destination, stop
            if (current.id == endId) {
                found = true;
                break;
            }

            // If found better path before, skip
            if (current.dist > distances[current.id]) continue;

            const Node* node = graph.getNode(current.id);
            if (!node) continue; // Safety check

            // Check all neighbors
            for (const auto& edge : node->neighbors) {
                double newDist = distances[current.id] + edge.distance;

                // If found shorter path to neighbor
                if (newDist < distances[edge.targetNodeID]) {
                    distances[edge.targetNodeID] = newDist;
                    parents[edge.targetNodeID] = current.id;
                    pq.push({edge.targetNodeID, newDist});
                }
            }
        }

        // Reconstruct path if found
        RouteResult result;
        if (found) {
            result.success = true;
            result.totalDist = distances[endId];

            // Backtrack from endId to startId
            int curr = endId;
            while (curr != startId) {
                result.path.push_back(curr);
                curr = parents[curr];
            }
            result.path.push_back(startId);

            // Path is backwards, reverse it
            std::reverse(result.path.begin(), result.path.end());
        } else {
            result.success = false;
            result.totalDist = 0.0;
        }

        return result;
    }
}