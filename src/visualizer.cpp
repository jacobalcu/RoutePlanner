#include "route_planner/graph.hpp"
#include "route_planner/visualizer.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
#include <optional>

namespace RoutePlanner {
    void displaySFML(const Graph& graph, const std::vector<int>& path) {
        sf::RenderWindow window(sf::VideoMode({800, 600}), "Route Planner Visualizer");

        sf::Font font;
        if (!font.openFromFile("assets/font.ttf")) {
            if (!font.openFromFile("../assets/font.ttf")) {
                std::cerr << "Error: Could not load font.ttf from assets folder" << std::endl;
            }
        }

        // Find bounds. Same logic as ASCII, but pixels now
        double minX = 1e9, maxX = -1e9, minY = 1e9, maxY = -1e9;
        for (const auto& [id, node] : graph.getAllNodes()) {
            minX = std::min(minX, node.x);
            maxX = std::max(maxX, node.x);
            minY = std::min(minY, node.y);
            maxY = std::max(maxY, node.y);
        }

        // Add padding so nodes not on very edge
        double padding = 50.0;
        auto toPixel = [&](double x, double y) {
            float px = padding + (x - minX) / (maxX - minX) * (800 - 2 * padding);
            float py = (600 - padding) - (y - minY) / (maxY - minY) * (600 - 2 * padding);
            return sf::Vector2f(px, py);
        };

        while (window.isOpen()) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) window.close();
            }

            window.clear(sf::Color(30,30,30)); // Dark grey

            // Draw ALL edges
            for (const auto& [id, node] : graph.getAllNodes()) {
                for (const auto& edge : node.neighbors) {
                    const Node* target = graph.getNode(edge.targetNodeID);
                    sf::Vertex line[] = {
                        {toPixel(node.x, node.y), sf::Color(100, 100, 100)},
                        {toPixel(target->x, target->y), sf::Color(100, 100, 100)}
                    };
                window.draw(line, 2, sf::PrimitiveType::Lines);
                }
            }

            // Draw the Path (highlighted)
            if (path.size() >= 2) {
                for (size_t i = 0; i < path.size() - 1; ++i) {
                    const Node* start = graph.getNode(path[i]);
                    const Node* end = graph.getNode(path[i + 1]);
                    sf::Vertex line[] = {
                        {toPixel(start->x, start->y), sf::Color::Cyan},
                        {toPixel(end->x, end->y), sf::Color::Cyan}
                    };
                    window.draw(line, 2, sf::PrimitiveType::Lines);
                }
            }

            // Draw Nodes
            for (const auto& [id, node] : graph.getAllNodes()) {
                sf::Vector2f pos = toPixel(node.x, node.y);

                // Draw node dot
                sf::CircleShape circle(5.f);
                circle.setOrigin({5.f, 5.f});
                circle.setPosition(toPixel(node.x, node.y));
                circle.setFillColor(sf::Color::White);
                window.draw(circle);

                // Draw label
                sf::Text label(font, node.name, 14); // font, string, size
                label.setFillColor(sf::Color::Yellow);

                // Offset text so no overlap
                label.setPosition({pos.x + 8.f, pos.y - 10.f});

                window.draw(label);
            }
            window.display();
        }

    }

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