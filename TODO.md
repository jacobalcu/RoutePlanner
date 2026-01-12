# Route Planner Project - Task List

## Phase 1: Foundations & Infrastructure

- [x] Set up directory structure (`include/`, `src/`, `tests/`)
- [x] Initialize Git repository and `.gitignore`
- [x] Create root `CMakeLists.txt` and verify build
- [ ] Define `Node` and `Edge` structures in `graph.hpp`
- [ ] Implement `Graph` class using an Adjacency List

## Phase 2: Data Handling & Parsing

- [ ] Create sample map data in `data/map.csv`
- [ ] Implement a `MapLoader` class/utility to parse files
- [ ] Add basic error handling for malformed input files

## Phase 3: Core Algorithm Implementation

- [ ] Implement Dijkstra’s Algorithm
- [ ] Use `std::priority_queue` for optimization
- [ ] Create a `Route` struct to store results (distance + path)
- [ ] (Optional/Intermediate) Implement A\* Search logic

## Phase 4: Quality Assurance & Engineering Best Practices

- [ ] Set up **Google Test** or **Catch2** integration
- [ ] Write unit tests for Graph edge cases (disconnected nodes, cycles)
- [ ] Write unit tests for Algorithm accuracy
- [ ] Refactor code for "Clean Code" principles (const-correctness, smart pointers)

## Phase 5: Final Interface & Polish

- [ ] Create a CLI (Command Line Interface) for user start/end points
- [ ] Add execution time logging (benchmarking)
- [ ] Final documentation in README.md
