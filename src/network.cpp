#include "boltzmann/network.hpp"

namespace boltzmann
{
    Network::Network()
    {
        
    }

    Network::Network(std::vector<Node>&& _nodes, std::vector<std::pair<int, int>>&& _edges)
        : nodes(_nodes), edges(_edges)
    {
        
    }

    Network::~Network()
    {

    }
}