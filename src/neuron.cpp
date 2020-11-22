#include "boltzmann/neuron.hpp"

#ifndef USE_BOOST_GRAPH
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
        return boost::container::vector<float>();
    }
}
#else
namespace boltzmann
{
    Neuron::Neuron()
    {

    }

    Neuron::~Neuron()
    {

    }
}
#endif