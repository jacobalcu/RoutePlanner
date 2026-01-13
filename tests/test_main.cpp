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