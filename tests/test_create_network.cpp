#include "boltzmann/network.hpp"
#include "gtest/gtest.h"

using namespace boltzmann;

class NetworkTest: public ::testing::Test
{
protected:
    void SetUp() override
    {
        net = new Network(3, {8, 8, 4}, 5.0);
    }

    void TearDown() override
    {
        delete net;
    }

    boltzmann::Network* net;
};

TEST_F(NetworkTest, CreateNetworkTest)
{
    try
    {
        Network net(3, {8, 8, 4}, 5.0);
        std::cout << net.toString() << std::endl;
        EXPECT_EQ(net.layers.size(), 3);
        EXPECT_EQ(net.weights.size(), 2);
        EXPECT_EQ(net.layers[0][0]->weights.size(), 8);
        EXPECT_EQ(net.layers[1][0]->weights.size(), 4);
        EXPECT_EQ(net.layers[2][0]->weights.size(), 0);
#ifdef USE_BOOST_UBLAS
        EXPECT_EQ(net.weights[0].size1(), 8);
        EXPECT_EQ(net.weights[0].size2(), 8);
        EXPECT_EQ(net.weights[1].size1(), 8);
        EXPECT_EQ(net.weights[1].size2(), 4);
#endif
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}