#include "boltzmann/node.hpp"

namespace boltzmann
{
    Node::Node()
    {
        
    }

    Node::Node(int _id)
    {
        id = _id;
    }

    Node::Node(int _id, std::string _name)
    {
        id = _id;
        name = _name;
    }

    Node::~Node()
    {

    }
}