#include <gtest/gtest.h>
#include "route_planner/graph.hpp"
#include "route_planner/router.hpp"

using namespace RoutePlanner;

// Test case for a basic path
TEST(RouterTest, SameStartAndEnd) {
    Graph g;
    g.addNode(1, "A", 0, 0);
    g.addNode(2, "B", 1, 1);
    g.addEdge(1, 2, 5.0);

    auto result = Router::computePath(g, 1, 1);

    EXPECT_TRUE(result.success);
    EXPECT_EQ(result.totalDist, 0.0);
    EXPECT_EQ(result.path.size(), 1);
}

// Test case for disconnected graph
TEST(RouterTest, NoPathFound) {
    Graph g;
    g.addNode(1, "A", 0, 0);
    g.addNode(2, "B", 1, 1);
    // Note: No edge added

    auto result = Router::computePath(g, 1, 2);

    EXPECT_FALSE(result.success);
}

// Test case for best path
TEST(RouterTest, BestPath) {
    Graph g;
    g.addNode(1, "A", 0, 0);
    g.addNode(2, "B", 1, 0);
    g.addNode(3, "C", 2, 0);
    g.addNode(4, "D", 0, 5);
    g.addNode(5, "E", 5, 9);
    g.addNode(6, "F", 10, 20);
    g.addEdge(1, 2, 1.0);
    g.addEdge(2, 3, 1.0);
    g.addEdge(1, 4, 10.0);
    g.addEdge(4, 5, 10.0);
    g.addEdge(5, 6, 10.0);
    g.addEdge(6, 3, 10.0);

    auto result = Router::computePath(g, 1, 3);

    EXPECT_TRUE(result.success);
    EXPECT_EQ(result.totalDist, 2.0);
    EXPECT_EQ(result.path.size(), 3);
}

// Test case for negative coords
TEST(RouterTest, NegativeCoordinates) {
    Graph g;
    g.addNode(1, "A", 0, 0);
    g.addNode(2, "B", -1, 0);
    g.addEdge(1, 2, 1.0);

    auto result = Router::computePath(g, 1, 2);

    EXPECT_TRUE(result.success);
    EXPECT_EQ(result.totalDist, 1.0);
    EXPECT_EQ(result.path.size(), 2);
}

// Test case for an invalid id
TEST(RouterTest, InvalidID) {
    Graph g;
    g.addNode(1, "A", 0, 0);
    g.addNode(2, "B", 1, 1);
    g.addEdge(1, 2, 5.0);

    auto result = Router::computePath(g, 1, 3);

    EXPECT_FALSE(result.success);
}

// Pick more steps over fewer but heavier edges
TEST(RouterTest, MoreStepsOptimalPath) {
    Graph g;
    g.addNode(1, "Start", 0, 0);
    g.addNode(2, "Middle", 0, 0);
    g.addNode(3, "End", 0, 0);

    // Path A: Direct 1 -> 3 but weight is 10
    g.addEdge(1, 3, 10.0);
    // Path B: Indirect 1 -> 2 -> 3 but total weight is 2+2=4
    g.addEdge(1, 2, 2.0);
    g.addEdge(2, 3, 2.0);

    auto result = Router::computePath(g, 1, 3);

    EXPECT_TRUE(result.success);
    EXPECT_DOUBLE_EQ(result.totalDist, 4.0);
    ASSERT_EQ(result.path.size(), 3);
    EXPECT_EQ(result.path[1], 2); // Middle node should be ID 2
}

// Test Graph Class: Adjacency list integrity
TEST(GraphTest, AddNodeAndEdge) {
    Graph g;
    g.addNode(1, "Test", 1.0, 2.0);
    g.addEdge(1, 1, 0.5); // Self-loop edge

    const Node* n = g.getNode(1);
    ASSERT_NE(n, nullptr); // Ensure pointer isn't null
    EXPECT_EQ(n->name, "Test");
    EXPECT_EQ(n->neighbors.size(), 1);
}