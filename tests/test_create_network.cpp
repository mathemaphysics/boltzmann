#include "boltzmann/network.hpp"

using namespace boltzmann;

int main(int argc, char **argv)
{
    try
    {
        Network net(3, {8, 8, 4});
        std::cout << net.toString() << std::endl;
        if (std::fabs(net.weights[0](0, 0)) > 1e-12)
            return 2;
        if (net.layers.size() != 3)
            return 3;
        if (net.weights.size() != 2)
            return 4;
        if (net.layers[0][0]->weights.size() != 8)
            return 5;
        if (net.layers[1][0]->weights.size() != 4)
            return 6;
        if (net.layers[2][0]->weights.size() != 0)
            return 7;
        if (net.weights[0].size1() != 8 && net.weights[0].size2() != 8)
            return 8;
        if (net.weights[1].size1() != 8 && net.weights[1].size2() != 4)
            return 9;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    
    return 0;
}