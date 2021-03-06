#include "boltzmann/network.hpp"

using namespace boltzmann;
/**
 * @brief 
 * @test
 *  - Creates a 2-layer network
 *  - Sets the only node-node weight to 2.0
 *  - Sets the state of the top layer node to "on"
 *  - Computes the average activation of the layer 2 node
 *  - Checks that it is within proper range and returns
 *    0 if okay or 1 if not
 */
int main(int argc, char **argv)
{
    const int numSamples = 10000;
    Network net(2, {1, 1});
    net.setNodeWeight(0, 0, 0, 2.0);

    net.layers[0][0]->state = 1;
    net.layers[1][0]->state = 0;
    boltzFloat_t meanActivation = 0.0;
    for (int n = 0; n < numSamples; n++)
    {
        net.layers[1][0]->updateState(1.0);
        meanActivation += (boltzFloat_t)net.layers[1][0]->state;
    }
    meanActivation /= (boltzFloat_t) numSamples;
    cout << "Mean Activation: " << setw(10) << setprecision(7) << meanActivation << endl;

    if (meanActivation > 0.20 || meanActivation < 0.05)
        return 1;

    return 0;
}