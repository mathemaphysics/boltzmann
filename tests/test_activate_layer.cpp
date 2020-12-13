#include "boltzmann/network.hpp"

using namespace boltzmann;

int main(int argc, char **argv)
{
    try
    {
        Network net(3, {8, 8, 4});
        std::cout << net.toString() << std::endl;
        const int numSamples = 1000;

        boltzFloat_t nodeMeanState = 0;
        boltzFloat_t layerMeanState = 0;
        net.setLayerState(1, {1, 1, 1, 1, 1, 1, 1, 1});
        for (int n = 0; n < numSamples; n++)
        {
            net.updateLayerState(2); // Already has the temperature
            layerMeanState += net.layers[2][0]->state;
            net.layers[2][0]->updateState(1.0); // Give temperature in the call
            nodeMeanState += net.layers[2][0]->state;
        }
        layerMeanState /= (boltzFloat_t) numSamples;
        nodeMeanState /= (boltzFloat_t) numSamples;

        cout << "Node result:  " << nodeMeanState << endl;
        cout << "Layer result: " << layerMeanState << endl;

        if (fabs(layerMeanState - nodeMeanState) > 0.04)
            return 1;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 2;
    }
    
    return 0;
}