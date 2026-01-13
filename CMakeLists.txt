cmake_minimum_required(VERSION 3.14)
project(RoutePlanner VERSION 1.0)

# Use C++17 or C++20 for modern features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch Google Test from GitHub
include(FetchContent)
FetchContent_Declare(
 googletest
 URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

# For Windows/MSYS2 compat
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Project Library
add_library(RoutePlannerLib
    src/graph.cpp
    src/map_loader.cpp
    src/router.cpp
)
target_include_directories(RoutePlannerLib PUBLIC include)

# Main Executable
add_executable(RoutePlanner src/main.cpp)
target_link_libraries(RoutePlanner RoutePlannerLib)

# The test executable
enable_testing()
add_executable(RoutePlannerTests tests/test_main.cpp)
target_link_libraries(RoutePlannerTests RoutePlannerLib gtest_main)

# Tests show up in VS Code's Test explorer
include(GoogleTest)
gtest_discover_tests(RoutePlannerTests)

# Include the headers
# include_directories(include)

# Define the executable and its source files
# add_executable(RoutePlanner 
#     src/main.cpp 
#     src/graph.cpp 
#     src/map_loader.cpp
#     src/router.cpp
# )