#ifndef BOLTZMANN_NETWORK_HPP
#define BOLTZMANN_NETWORK_HPP

#include "boltzmann/boltzmann_config.hpp"

#include "boltzmann/node.hpp"
#include <cmath>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <memory>
#include <boost/range/combine.hpp>
#include <boost/foreach.hpp>
#include <boost/multi_array.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

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
         * @brief Updates all node states in the layer
         * @param _layer The index of the layer to update
         */
        void updateLayer(int _layer);

        /**
         * @brief Set a specific weight in a layer of a network
         * @param _layer The index of the layer in the network
         * @param _node The index of the node in the layer
         * @param _neighbor The index of the node in the next layer
         * @param _weight The value to set the weight to
         */
        void setWeight(int _layer, int _node, int _neighbor, float_t _weight);

        /**
         * @brief Convert object to a string description
         * @return Converted string
         */
        string toString();

        /**
         * @brief The layers and their nodes
         */
        int size;
        float_t temperature;
#ifdef USE_BOOST_MULTIARRAY
        boost::multi_array<float_t, 3> weights;
        boost::multi_array<Node, 2> layers;
#else
        vector<matrix> weights;
        vector<vector<shared_ptr<Node>>> layers;
#endif
    };
}
#endif // BOLTZMANN_NETWORK_HPP