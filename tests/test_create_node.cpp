#include "boltzmann/node.hpp"

using namespace boltzmann;

int main(int argc, char **argv)
{
    Node node(0, "test");

    if (node.id != 0)
        return 1;
    if (node.name != "test")
        return 2;
    if (node.neighbors.size() > 0)
        return 3;

    return 0;
}