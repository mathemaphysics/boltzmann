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
        ~Network();

        std::vector<Node> nodes;
        std::vector<std::pair<int, int>> edges;
    };
}
#endif