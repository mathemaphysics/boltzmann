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
        for (int _l = 0; _l < _nlayers - 1; _l++)
        {
            for (int _np = 0; _np < _lsizes[_l]; _np++)
            {
                for (int _nq = 0; _nq < _lsizes[_l+1]; _nq++)
                {
                    layers[_l][_np]->neighbors.push_back(layers[_l][_nq]);
                }
            }
        }
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