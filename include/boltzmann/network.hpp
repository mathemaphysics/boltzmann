#ifndef BOLTZMANN_NETWORK_HPP
#define BOLTZMANN_NETWORK_HPP

#include "boltzmann/boltzmann_config.hpp"

#include "boltzmann/node.hpp"
#include <boost/numeric/ublas/matrix.hpp>

using matrix = boost::numeric::ublas::matrix<float>;
using namespace std;

namespace boltzmann
{
    class Network
    {
    public:
        /**
         * @brief The default constructor for Networks
         */
        Network();

        /**
         * @brief Construct a new Network with given layers and sizes
         * @param _nlayers The number of layers to create
         * @param _lsizes The number of nodes in each layer
         */
        Network(int _nlayers, int *_lsizes);

        /**
         * @brief Construct a new Network with given layers and sizes
         * @param _nlayers The number of layers to create
         * @param _lsizes The number of nodes in each layer
         */
        Network(int _nlayers, vector<int> _lsizes);

        /**
         * @brief Clean things up; this may need work
         */
        ~Network();

        /**
         * @brief The layers and their nodes
         */
        std::vector<vector<Node>> layers;
        std::vector<matrix> weights;
    };
}
#endif