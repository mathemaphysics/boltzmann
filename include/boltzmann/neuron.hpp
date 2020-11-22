#ifndef BOLTZMANN_NEURON_HPP
#define BOLTZMANN_NEURON_HPP

#include "node.hpp"

namespace boltzmann
{
    /// @brief The primary neuron class used for RBMs
    class Neuron : public Node<float, 1>
    {
    public:
        Neuron();
        ~Neuron();

        float getBias();
        float getWeight(int);
        boost::container::vector<float> getWeights();

    private:
        boost::container::vector<float> weights;
        boost::container::vector<int> indexes;
    };
}

#endif
