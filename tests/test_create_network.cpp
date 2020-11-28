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
        if (&(net.layers[0][0]) == nullptr)
            return 3;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    
    return 0;
}