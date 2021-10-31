#include "boltzmann/node.hpp"
#include "gtest/gtest.h"

using namespace boltzmann;

class NetworkTest: public ::testing::Test
{
protected:
    void SetUp() override
    {
        node = new Node(0, "test");
        node->addNeighbor(1);
    }

    void TearDown() override
    {
        delete node;
    }

    Node* node;
};

TEST_F(NetworkTest, CreateNodeTest)
{
    EXPECT_EQ(node->id, 0);
    EXPECT_EQ(node->name, "test");
    EXPECT_GT(node->neighbors.size(), 0);
}