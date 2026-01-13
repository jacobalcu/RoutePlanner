#include "route_planner/graph.hpp"
#include "route_planner/visualizer.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

namespace RoutePlanner {
    void drawAsciiMap(const Graph& graph, const std::vector<int>& path) {
        const int WIDTH = 50;
        const int HEIGHT = 20;

        // Find bounds of map
        double minX = 1e9, maxX = -1e9, minY = 1e9, maxY = -1e9;
        for (const auto& [id, node] : graph.getAllNodes()) {
            minX = std::min(minX, node.x);
            maxX = std::max(maxX, node.x);
            minY = std::min(minY, node.y);
            maxY = std::max(maxY, node.y);
        }

        // Create empty grid
        std::vector<std::string> grid(HEIGHT, std::string(WIDTH, ' '));

        // Helper to convert Graph coords to Grid coords
        auto toGrid = [&](double x, double y) {
            int gridX = static_cast<int>((x - minX) / (maxX - minX) * (WIDTH - 1));
            // Subtract from (HEIGHT - 1) because terminal Y increases downward
            int gridY = (HEIGHT - 1) - static_cast<int>((y - minY) / (maxY - minY) * (HEIGHT - 1));
            return std::make_pair(gridX, gridY);
        };

        // Place all nodes as '.'
        for (const auto& [id, node] : graph.getAllNodes()) {
            auto [gx, gy] = toGrid(node.x, node.y);
            grid[gy][gx] = 'X';
        }

        // Place path nodes as 'O'
        // int num = 1;
        for (int nodeId : path) {
            const auto* node = graph.getNode(nodeId);
            auto [gx, gy] = toGrid(node->x, node->y);
            // grid[gy][gx] = std::to_string(num);
            grid[gy][gx] = 'O';
            // num++;
            // grid[gy][gx] = node->name[0];
        }

        // Print grid with border
        std::cout << "+" << std::string(WIDTH, '-') << "+" << std::endl;
        for (const auto& row : grid) {
            std::cout << "|" << row << "|" << std::endl;
        }
        std::cout << "+" << std::string(WIDTH, '-') << "+" << std::endl;
        std::cout << "( . = Location, O = Your Route )" << std::endl;
    }
}