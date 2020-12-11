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

    Node::Node(int _id, string _name)
    {
        id = _id;
        name = _name;
    }

    Node::~Node()
    {

    }

    void Node::addNeighbor(int _node)
    {
        
    }
    
    void Node::addNeighbor(Node _node)
    {

    }

    void Node::updateState(boltzFloat_t _temp)
    {
        // Node always has bias as base quantity
        boltzFloat_t _input = bias;
        for (auto _tup : boost::combine(bneighbors, bweights))
        {
            shared_ptr<Node> _nodeptr;
            boltzFloat_t _weight;
            boost::tie(_nodeptr, _weight) = _tup;
            if (_nodeptr->state > 0)
                _input += _weight;
        }

        // Take one Monte Carlo step (needs to be tuned still)
        boltzFloat_t _prob = activation(_input, _temp);
        boltzFloat_t _rand = (boltzFloat_t)rand() / (boltzFloat_t)RAND_MAX;
        if (_rand < _prob)
            state = 1;
        else
            state = 0;
    }

    string Node::toString()
    {
        ostringstream strs;

        strs << setw(12) << "NodeId: " << setw(7) << id << " ";
        strs << setw(12) << "Neigh: " << setw(7) << neighbors.size() << " ";
        strs << setw(12) << "BNeigh: " << setw(7) << bneighbors.size() << " ";
        strs << setw(12) << "Wts: " << setw(7) << weights.size() << " ";
        strs << setw(12) << "BWts: " << setw(7) << bweights.size();

        return strs.str();
    }

    boltzFloat_t Node::activation(boltzFloat_t _input, boltzFloat_t _temp)
    {
        return 1.0 / (1.0 + exp((double)(_input / _temp)));
    }
}