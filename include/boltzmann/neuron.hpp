#ifndef BOLTZMANN_NEURON_HPP
#define BOLTZMANN_NEURON_HPP

#include "boltzmann/boltzmann_config.hpp"

#ifndef USE_BOOST_GRAPH
#   include "node.hpp"
#else
#   include <boost/graph/undirected_graph.hpp>
#   include <boost/graph/directed_graph.hpp>
#endif

#ifndef USE_BOOST_GRAPH
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
#else
namespace boltzmann
{
    class Neuron
    {
    public:
        Neuron();
        ~Neuron();
    };
}
#endif

#endif // BOLTZMANN_NEURON_HPP