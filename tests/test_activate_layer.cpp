#include "boltzmann/network.hpp"

using namespace boltzmann;

int main(int argc, char **argv)
{
    try
    {
        Network net(3, {8, 8, 4});
        const int numSamples = 10000;

        // Temp output for the node evaluations
        std::vector<boltzFloat_t> nodeMeanStates(net.layers[2].size());
        std::vector<boltzFloat_t> layerMeanStates(net.layers[2].size());
        net.setLayerState(1, {1, 1, 1, 1, 1, 1, 1, 1});
        for (int n = 0; n < numSamples; n++)
        {
            net.updateLayerState(2); // Already has the temperature
            for (int i = 0; i < net.layers[2].size(); i++)
                layerMeanStates[i] += net.layers[2][i]->state;
            for (int i = 0; i < net.layers[2].size(); i++)
            {
                net.layers[2][i]->updateState(1.0); // Give temperature in the call
                nodeMeanStates[i] += net.layers[2][i]->state;
            }
        }
        for (int i = 0; i < net.layers[2].size(); i++)
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