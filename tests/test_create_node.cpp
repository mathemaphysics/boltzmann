#include "boltzmann/node.hpp"

#include <cmath>

using namespace boltzmann;

int main(int argc, char **argv)
{
    Node<double, 2> node(0, "test");

    if (node.getName() != std::string("test"))
        return 1;
    if (node.getId() != 0)
        return 2;
    if (node.getLayerId() != -1)
        return 3;
    
    boost::array<double, 2> nodeState = node.getNodeState();
    if (std::fabs(nodeState[0]) > (double)1e-8
     || std::fabs(nodeState[1]) > (double) 1e-8)
        return 4; 

    return 0;
}