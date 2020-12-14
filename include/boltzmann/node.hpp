#ifndef BOLTZMANN_NODE_HPP
#define BOLTZMANN_NODE_HPP

#include "boltzmann/boltzmann_config.hpp"

#include <cmath>
#include <array>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>

#include <boost/range/combine.hpp>
#include <boost/foreach.hpp>

//#include <boost/graph/graph_traits.hpp>
//#include <boost/graph/adjacency_list.hpp>
//#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;

namespace boltzmann
{
    /// @brief The primary neuron class used for RBMs
    class Node
    {
    public:
        Node();
        Node(int _node, int layer = -1);
        Node(int _node, string _name, int _layer = -1);
        ~Node();

        /**
         * @brief Update the value of the node based on forward states
         * @param _temp The (pseudo) temperature of the network to use
         */
        void updateState(boltzFloat_t _temp = 1.0);

        /**
         * @brief Update the value of the node state base on back states
         * @param _temp The (pseudo) temperature of the network to use
         */
        void updateStateBack(boltzFloat_t _temp = 1.0);

        /**
         * @brief Add an existing node with given ID
         * @param _node Index of the node to add as neighbor
         */
        void addNeighbor(int _node);
        void addNeighbor(Node _node);

        string toString();

        int id;
        int state;
        int layer;
        boltzFloat_t bias;
        string name;
        vector<shared_ptr<Node>> neighbors;
        vector<boltzFloat_t> weights;
        vector<shared_ptr<Node>> bneighbors;
        vector<boltzFloat_t> bweights;
        boltzFloat_t activation(boltzFloat_t _input, boltzFloat_t _temp);
    };
}

#endif // BOLTZMANN_NODE_HPP