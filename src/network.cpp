#include "boltzmann/network.hpp"

namespace boltzmann
{
    Network::Network()
    {
        
    }

    Network::Network(int _nlayers, vector<int> _lsizes)
    {
#ifdef USE_BOOST_MULTIARRAY
        /* Initialize multiarrays */
        
#else
        /* Initialize matrix and weights */
        int _index = 0;
        for (int _l = 0; _l < _nlayers - 1; _l++)
        {
            // Create the matrix for the weight from _l to _l + 1
            weights.push_back(matrix(_lsizes[_l], _lsizes[_l + 1], (float_t) 0.0));

            // Create the nodes for layer _l
            vector<shared_ptr<Node>> temp(_lsizes[_l]);
            for (int _n = 0; _n < _lsizes[_l]; _n++)
                temp[_n] = shared_ptr<Node>(new Node(_index++));
            
            // Add it to the list of layers
            layers.push_back(temp);
        }

        // Create the final layer of nodes; not included above
        vector<shared_ptr<Node>> temp(_lsizes[_nlayers-1]);
        for (int _n = 0; _n < _lsizes[_nlayers-1]; _n++)
            temp[_n] = shared_ptr<Node>(new Node(_index++));

        // Set the final size of the system; number of nodes
        size = _index;

        /* Now point weights to individual nodes */
        for (auto _l = layers.begin(); _l < layers.end() - 1; _l++)
            for (auto _np = _l->begin(); _np < _l->end(); _np++)
                for (auto _nq = (_l + 1)->begin(); _nq < (_l + 1)->end(); _nq++)
                    (*_np)->neighbors.push_back(*_nq);
#endif
    }

    Network::~Network()
    {
        
    }

    std::string Network::toString()
    {
        std::ostringstream strs;
        strs << "Layers: " << std::setw(10) << layers.size() << std::endl;
        strs << "Nodes:  " << std::setw(10) << size;
        return strs.str();
    }
}