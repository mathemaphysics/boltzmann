#include "boltzmann/node.hpp"

namespace boltzmann
{
    Node::Node()
    {
        
    }

    Node::Node(int _id)
    {
        id = _id;
        neighbors = vector<shared_ptr<Node>>();
        weights = vector<float_t>();
    }

    Node::Node(int _id, std::string _name)
    {
        id = _id;
        name = _name;
        neighbors = vector<shared_ptr<Node>>();
        weights = vector<float_t>();
    }

    Node::~Node()
    {

    }
}