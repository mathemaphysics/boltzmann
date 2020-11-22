#include "boltzmann/neuron.hpp"

namespace boltzmann
{
    Neuron::Neuron()
    {
        
    }

    Neuron::~Neuron()
    {

    }

    float Neuron::getBias()
    {
        return getNodeState()[0];
    }

    float Neuron::getWeight(int nodeId)
    {
        return weights[nodeId];
    }

    boost::container::vector<float> Neuron::getWeights()
    {

    }
}

