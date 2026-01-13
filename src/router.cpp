#include "route_planner/router.hpp"
#include <queue>
#include <limits>
#include <algorithm>
#include <cmath>

namespace RoutePlanner {

    // helper struct for priority queue
    struct NodeDistance {
        int id;
        double fScore; // gScore + heuristic

        // Overload 'greater than' op
        // std::priority_queue uses max-heap by default
        // We want min-heap behavior
        bool operator>(const NodeDistance& other) const {
            return fScore > other.fScore;
        }
    };

    // Helper function to calculate straight-line (Euclidean distance)
    double calculateHeuristic(const Node* a, const Node* b) {
        if (!a || !b) return 0.0;
        return std::sqrt(std::pow(a->x - b->x, 2) + std::pow(a->y - b->y, 2));
    }

    RouteResult Router::computePath(const Graph& graph, int startId, int endId) {
        // Setup Data Structures
        // Stores shortest known distance to each node
        // Key: Node ID, Value: Distance from start
        std::unordered_map<int, double> gScores;

        // Stores "parent" of each node for path reconstruction
        // Key: Node ID, Value: Parent Node ID
        std::unordered_map<int, int> parents;

        // Min-heap priority queue to select next node with smallest distance
        // Priority Queue: <Type, Container, Comparator>
        std::priority_queue<NodeDistance, std::vector<NodeDistance>, std::greater<NodeDistance>> pq;

        // Keep for A* heuristic
        const Node* endNode = graph.getNode(endId);
        if (!endNode) return { {}, 0.0, false };

        // Init all distances to infinity
        for (const auto& pair : graph.getAllNodes()) {
            gScores[pair.first] = std::numeric_limits<double>::infinity();
        }

        // Start algo
        gScores[startId] = 0.0;

        // Init fScore is gScore(0) + heuristic to end
        double initialH = calculateHeuristic(graph.getNode(startId), endNode);
        pq.push({startId, initialH});

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
            // if (current.dist > distances[current.id]) continue;

            const Node* node = graph.getNode(current.id);
            if (!node) continue; // Safety check

            // Check all neighbors
            for (const auto& edge : node->neighbors) {
                double tentativeGScore = gScores[current.id] + edge.distance;

                // If found shorter path to neighbor
                if (tentativeGScore < gScores[edge.targetNodeID]) {
                    gScores[edge.targetNodeID] = tentativeGScore;
                    parents[edge.targetNodeID] = current.id;

                    // A* advantage
                    // Priority = Distance Traveled + Estimated to Goal
                    double h = calculateHeuristic(graph.getNode(edge.targetNodeID), endNode);
                    pq.push({edge.targetNodeID, tentativeGScore + h});
                }
            }
        }

        // Reconstruct path if found
        RouteResult result;
        if (found) {
            result.success = true;
            result.totalDist = gScores[endId];

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
        }

        return result;
    }
}