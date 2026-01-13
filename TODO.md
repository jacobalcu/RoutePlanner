# Route Planner Project - Task List

## Phase 1: Foundations & Infrastructure

- [x] Set up directory structure (`include/`, `src/`, `tests/`)
- [x] Initialize Git repository and `.gitignore`
- [x] Create root `CMakeLists.txt` and verify build
- [x] Define `Node` and `Edge` structures in `graph.hpp`
- [x] Implement `Graph` class using an Adjacency List

## Phase 2: Data Handling & Parsing

- [x] Create sample data in `data/nodes.csv` and `data/edges.csv`
- [x] Implement a `MapLoader` class/utility to parse files
- [x] Add basic error handling for malformed input files

## Phase 3: Core Algorithm Implementation

- [x] Implement Dijkstra’s Algorithm
- [x] Use `std::priority_queue` for optimization
- [x] Create a `Route` struct to store results (distance + path)
- [x] (Optional/Intermediate) Implement A\* Search logic

## Phase 4: Quality Assurance & Engineering Best Practices

- [x] Set up **Google Test** or **Catch2** integration
- [x] Write unit tests for Graph edge cases (disconnected nodes, cycles)
- [x] Write unit tests for Algorithm accuracy
- [ ] Refactor code for "Clean Code" principles (const-correctness, smart pointers)

## Phase 5: Final Interface & Polish

- [ ] Create a CLI (Command Line Interface) for user start/end points
- [ ] Add execution time logging (benchmarking)
- [ ] Final documentation in README.md
