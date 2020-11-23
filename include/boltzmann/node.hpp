#ifndef BOLTZMANN_NEURON_HPP
#define BOLTZMANN_NEURON_HPP

#include "boltzmann/boltzmann_config.hpp"

#include <array>
#include <vector>
#include <utility>
#include <algorithm>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef struct {
    int neighbor;
    float weight;
} neigh_t;

namespace boltzmann
{
    /// @brief The primary neuron class used for RBMs
    class Node
    {
    public:
        Node();
        Node(int nodeId);
        Node(int nodeId, std::string nodeName);
        ~Node();

        int id;
        std::string name;
        float bias;
        std::vector<neigh_t> neighbors;
    };
}

#endif // BOLTZMANN_NEURON_HPP