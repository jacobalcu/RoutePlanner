#include "route_planner/graph.hpp"
#include "route_planner/visualizer.hpp"
#include "route_planner/router.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Cursor.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <optional>

namespace RoutePlanner {
    void displaySFML(const Graph& graph) {
        // Add antialiasing to make it smoother
        sf::ContextSettings settings;
        settings.antiAliasingLevel = 8; // higher = smoother

        sf::RenderWindow window(sf::VideoMode({800, 600}), "Route Planner", sf::State::Windowed, settings);

        sf::Font font;
        if (!font.openFromFile("assets/font.ttf")) {
            if (!font.openFromFile("../assets/font.ttf")) {
                std::cerr << "Error: Could not load font.ttf from assets folder" << std::endl;
            }
        }

        // Selection state
        int startNodeId = -1;
        int endNodeId = -1;
        int hoveredNodeId = -1;
        std::vector<int> currentPath;

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
                if (event->is<sf::Event::KeyPressed>()) {
                    if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
                        window.close();
                    }
                }

                // Handle Mouse Clicks
                if (event->is<sf::Event::MouseButtonPressed>()) {
                    // Get mouse position
                    auto mousePos = sf::Mouse::getPosition(window);
                    
                    sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

                    // Find which node was clicked
                    for (const auto& [id, node] : graph.getAllNodes()) {
                        sf::Vector2f nodePos = toPixel(node.x, node.y);
                        float dist = std::sqrt(std::pow(worldPos.x - nodePos.x, 2) + std::pow(worldPos.y - nodePos.y, 2));

                        if (dist < 10.0f) { // 10 pixel hit box
                            if (startNodeId == -1 || (startNodeId != -1 && endNodeId != -1)) {
                                startNodeId = id;
                                endNodeId = -1;
                                currentPath.clear();
                            } else {
                                endNodeId = id;
                                // Calc route immediately
                                auto result = Router::computePath(graph, startNodeId, endNodeId);
                                if (result.success) {
                                    currentPath = result.path;
                            }
                            break;
                        }
                    }
                }
            }

            // Handle Hover Logic (Every Frame)
            auto mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
            
            hoveredNodeId = -1; // Reset each frame
            for (const auto& [id, node] : graph.getAllNodes()) {
                sf::Vector2f nodePos = toPixel(node.x, node.y);
                float dist = std::sqrt(std::pow(worldPos.x - nodePos.x, 2) + std::pow(worldPos.y - nodePos.y, 2));

                if (dist < 12.0f) { // Slightly larger hitbox for hovering
                    hoveredNodeId = id;
                    break; 
                }
            }
            if (hoveredNodeId != -1) {
                const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand).value();
                window.setMouseCursor(cursor);
            } else {
                const auto cursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow).value();
                window.setMouseCursor(cursor);
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
            if (!currentPath.empty()) {
                for (size_t i = 0; i < currentPath.size() - 1; ++i) {
                    const Node* start = graph.getNode(currentPath[i]);
                    const Node* end = graph.getNode(currentPath[i + 1]);
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
                sf::CircleShape circle(7.f);
                circle.setOrigin({7.f, 7.f});
                circle.setPosition(toPixel(node.x, node.y));

                circle.setFillColor(sf::Color::White);
                // Start node is green, end is red, others white
                if(!currentPath.empty()) {
                    if(id== currentPath.front()) circle.setFillColor(sf::Color::Green);
                    else if(id== currentPath.back()) circle.setFillColor(sf::Color::Red);
                }

                // Add outline to hovered node
                if (id == hoveredNodeId) {
                    circle.setOutlineThickness(2.f);
                    circle.setOutlineColor(sf::Color::Cyan);
                }
                
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