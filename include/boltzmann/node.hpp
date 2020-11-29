#ifndef BOLTZMANN_NEURON_HPP
#define BOLTZMANN_NEURON_HPP

#include "boltzmann/boltzmann_config.hpp"

#include <array>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>

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
        Node(int nodeId);
        Node(int nodeId, string nodeName);
        ~Node();

        int id;
        int state;
        float_t bias;
        string name;
        vector<shared_ptr<Node>> neighbors;
        vector<float_t> weights;
    };
}

#endif // BOLTZMANN_NEURON_HPP