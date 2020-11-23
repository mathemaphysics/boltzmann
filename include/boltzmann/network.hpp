#ifndef BOLTZMANN_NETWORK_HPP
#define BOLTZMANN_NETWORK_HPP

#include "boltzmann/boltzmann_config.hpp"

#include "boltzmann/node.hpp"

namespace boltzmann
{
    class Network
    {
    public:
        Network();
        /**
         * @brief Construct a new Network with given layers and sizes
         * @param _nlayers The number of layers to create
         * @param _lsizes The number of nodes in each layer
         */
        Network(int _nlayers, std::vector<int> _lsizes);
        Network(std::vector<Node>&&, std::vector<std::pair<int, int>>&&);
        ~Network();

        std::vector<std::vector<Node>> layers;
        std::vector<Node> nodes;
        std::vector<std::pair<int, int>> edges;
    };
}
#endif