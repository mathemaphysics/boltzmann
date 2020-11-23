#ifndef BOLTZMANN_LAYER_HPP
#define BOLTZMANN_LAYER_HPP

#include "boltzmann/node.hpp"

namespace boltzmann
{
    class Layer
    {
    public:
        Layer();
        Layer(int _lsize);
        ~Layer();

        int getSize();

    private:
        int size;
        std::vector<Node> nodes;
    };
}

#endif
