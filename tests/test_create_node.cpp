#include "boltzmann/node.hpp"

using namespace boltzmann;

int main(int argc, char **argv)
{
    Node<double, 2> node(0, "test");

    if (node.getName() != std::string("test"))
        return 1;
    if (node.getId() != 0)
        return 2;

    return 0;
}