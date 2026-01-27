[![C++ CI Build](https://github.com/jacobalcu/RoutePlanner/actions/workflows/ci.yaml/badge.svg)](https://github.com/jacobalcu/RoutePlanner/actions/workflows/ci.yaml)

# RoutePlanner

RoutePlanner Pro: A* Navigation Engine
A high-performance C++ navigation engine that uses the A Search Algorithm* to find the shortest path between nodes in a graph. Originally built as a command-line tool, it now features a fully interactive SFML 3.0 graphical interface.

🚀 Key Features
A\* Search Algorithm: Uses a Euclidean distance heuristic to optimize pathfinding over standard Dijkstra.

Interactive GUI: Built with SFML 3.0, featuring node hovering, mouse-based selection, and real-time path calculation.

Robust Core: Handles graph data via CSV loading with a custom-built adjacency list structure.

Automated Testing: Comprehensive unit tests using GoogleTest to ensure pathfinding accuracy.

CI/CD Pipeline: Integrated with GitHub Actions for cross-platform build validation (Windows/Linux).

🛠 Tech Stack
Language: C++17

Graphics: SFML 3.0

Build System: CMake

Testing: GoogleTest

Environment: MSYS2 / UCRT64

🏗 Project Architecture
The project is divided into modular components to ensure separation of concerns:

Graph Engine: Manages nodes and weighted edges.

Router: Contains the A\* implementation, decoupled from the UI.

Visualizer: Handles coordinate mapping (World space to Pixel space) and SFML rendering.

Map Loader: Parses CSV data into the Graph structure.

🏁 How to Run
Select Start: Hover over a white node and click. It will turn Green.

Select Destination: Click another node. It will turn Red.

View Route: The shortest path will be highlighted in Cyan.

Reset: Clicking a third time clears the previous path.

🛤 Future Roadmap
This project provides a solid foundation for several advanced features:

1. Advanced Interactivity
   Fuzzy Search: Re-integrate a search bar using Levenshtein distance to find locations by name if the user doesn't want to click.

Zoom & Pan: Implement an sf::View to allow exploration of much larger maps (e.g., an entire city).

2. Algorithmic Enhancements
   Dijkstra Comparison: Add a toggle to visualize the difference in nodes explored between Dijkstra and A\*.

Real-time Obstacles: Allow users to "block" nodes or edges and watch the algorithm recalculate the route dynamically.

3. Real-World Integration
   OSM Integration: A tool to convert OpenStreetMap .osm files into the project's CSV format.

Traffic Weighting: Adding a "congestion" factor to edges so the "shortest" path isn't always the "fastest."

👨‍💻 Lessons Learned
Cross-Platform CI: Navigating the version differences between SFML 3 (local) and SFML 2 (CI) using preprocessor macros.

Memory Management: Managing graph pointers and avoiding iterator invalidation in a real-time loop.

Coordinate Transformation: Mapping abstract map data to a fixed-pixel window while maintaining aspect ratios.
