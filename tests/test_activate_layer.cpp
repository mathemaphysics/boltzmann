#include "boltzmann/network.hpp"
#include "gtest/gtest.h"

using namespace boltzmann;

/**
 * @brief Checks for consistency of activation (forward)
 * @test
 *  - Creates a 3-layer RBM with random weights
 *  - Sets layer 1's state to all "on"
 *  - Runs the network forward one layer down
 *  - Checks to see if the result for individual
 *    node functions and layer functions produce
 *    the same output; returns 0 if close enough,
 *    1 if not
 */
class NetworkTest: public ::testing::Test
{
protected:
    void SetUp() override
	{
        net = new Network(3, {8, 8, 4});
        net->setLayerState(1, {1, 1, 1, 1, 1, 1, 1, 1});
	}

    void TearDown() override
	{
        delete net;
	}

    const int numSamples = 10000;
    boltzmann::Network* net;
};

TEST_F(NetworkTest, LayerActivation)
{
    // Temp output for the node evaluations
    std::vector<boltzFloat_t> nodeMeanStates(net->layers[2].size(), 0.0);
    std::vector<boltzFloat_t> layerMeanStates(net->layers[2].size(), 0.0);
    for (int n = 0; n < numSamples; n++)
    {
        net->updateLayerState(2); // Already has the temperature
        for (int i = 0; i < net->layers[2].size(); i++)
            layerMeanStates[i] += net->layers[2][i]->state;
        for (int i = 0; i < net->layers[2].size(); i++)
        {
            EXPECT_NO_THROW(net->layers[2][i]->updateState(1.0)); // Give temperature in the call
            nodeMeanStates[i] += net->layers[2][i]->state;
        }
    }
    for (int i = 0; i < net->layers[2].size(); i++)
    {
        layerMeanStates[i] /= (boltzFloat_t)numSamples;
        nodeMeanStates[i] /= (boltzFloat_t)numSamples;
    }

    // Output the results in case anyone is watching
    cout << "Node results:  ";
    for (auto node : nodeMeanStates)
        cout << setw(7) << setprecision(3) << node;
    cout << endl;
    cout << "Layer results: ";
    for (auto node : layerMeanStates)
        cout << setw(7) << setprecision(3) << node;
    cout << endl;

    // Check that they're close enough (won't be exact)
    for (auto tup : boost::combine(nodeMeanStates, layerMeanStates))
    {
        boltzFloat_t a, b;
        boost::tie(a, b) = tup;

        EXPECT_LE(fabs(b - a), 0.04);
    }
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}