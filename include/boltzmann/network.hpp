#ifndef BOLTZMANN_NETWORK_HPP
#define BOLTZMANN_NETWORK_HPP

#include "boltzmann/boltzmann_config.hpp"

#include "boltzmann/node.hpp"
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
         * @brief Convert object to a string description
         * @return Converted string
         */
        std::string toString();

        /**
         * @brief The layers and their nodes
         */
        int size;
#ifdef USE_BOOST_MULTIARRAY
        boost::multi_array<float_t, 3> weights;
        boost::multi_array<Node, 2> layers;
#else
        vector<matrix> weights;
        vector<vector<shared_ptr<Node>>> layers;
#endif
    };
}
#endif