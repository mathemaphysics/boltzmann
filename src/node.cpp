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

    void addNeighbor(int _node)
    {
        
    }
    
    void addNeighbor(Node _node)
    {

    }

    void Node::update(float_t _temp)
    {
        // Node always has bias as base quantity
        float_t _input = bias;
        for (auto _tup : boost::combine(neighbors, weights))
        {
            shared_ptr<Node> _nodeptr;
            float_t _weight;
            boost::tie(_nodeptr, _weight) = _tup;
            if (_nodeptr->state > 0)
                _input += _weight;
        }

        // Take one Monte Carlo step (needs to be tuned still)
        float_t _prob = activation(_input, _temp);
        float_t _rand = (float_t)rand() / (float_t)RAND_MAX;
        if (_rand < _prob)
            state = 1;
        else
            state = 0;
    }

    float_t Node::activation(float_t _input, float_t _temp)
    {
        return 1.0 / (1.0 + exp((double)(_input / _temp)));
    }
}