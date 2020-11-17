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

    private:
        boost::container::vector<float> weights;
        boost::array<float, 1> bias;
    };
}

#endif
