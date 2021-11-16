#include "boltzmann/network.hpp"
#include "gtest/gtest.h"

using namespace boltzmann;

/**
 * @brief Checks for consistency of activation (back)
 * @test
 *  - Creates a 3-layer RBM with random weights
 *  - Sets layer 2's state to all "on"
 *  - Runs the network backward one layer up
 *  - Checks to see if the result for individual
 *    node functions and layer functions produce
 *    the same output; returns 0 if close enough,
 *    1 if not
 */
int main(int argc, char **argv)
{
    try
    {
        Network net(3, {8, 8, 4});
        const int numSamples = 10000; // Get expectation values using numSamples samples

        vector<boltzFloat_t> nodeMeanStates(net.layers[1].size());
        vector<boltzFloat_t> layerMeanStates(net.layers[1].size());
        net.setLayerState(2, {1, 1, 1, 1});
        for (int n = 0; n < numSamples; n++)
        {
            net.updateLayerStateBack(1); // Already has the temperature
            for (int i = 0; i < net.layers[1].size(); i++)
                layerMeanStates[i] += net.layers[1][i]->state;
            for (int i = 0; i < net.layers[1].size(); i++)
            {
                net.layers[1][i]->updateStateBack(1.0); // Give temperature in the call
                nodeMeanStates[i] += net.layers[1][i]->state;
            }
        }
        for (int i = 0; i < net.layers[1].size(); i++)
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

            if (fabs(b - a) > 0.04)
                return 1;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 2;
    }
    
    return 0;
}
