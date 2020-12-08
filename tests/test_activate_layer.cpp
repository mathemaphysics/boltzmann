#include "boltzmann/network.hpp"

using namespace boltzmann;

int main(int argc, char **argv)
{
    try
    {
        Network net(3, {8, 8, 4});
        std::cout << net.toString() << std::endl;

        net.updateLayerState(2);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    
    return 0;
}