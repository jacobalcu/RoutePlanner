cmake_minimum_required(VERSION 3.10)
project(RoutePlanner VERSION 1.0)

# Use C++17 or C++20 for modern features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the headers
include_directories(include)

# Define the executable and its source files
add_executable(RoutePlanner 
    src/main.cpp 
    src/graph.cpp 
    src/router.cpp
)