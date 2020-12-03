#include "boltzmann/network.hpp"

namespace boltzmann
{
    Network::Network()
    {
        srand((unsigned)time(0));
    }

    /**
     * @brief Initialize a Network with \c _nlayers layers
     * Network objects store weights redundantly in both the
     * \c Node::neighbors \c vector and also in a \c matrix
     * in order to make it easier to compute with
     * 
     * @param _nlayers The number of layers to create
     * @param _lsizes The sizes of each layer
     */
    Network::Network(int _nlayers, vector<int> _lsizes)
    {
        // This is a Metropolis-Hastings algorithm so seed well
        srand((unsigned)time(0));
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
        layers.push_back(temp);

        // Set the final size of the system; number of nodes
        size = _index;

        /* Now point weights to individual nodes */
        vector<vector<shared_ptr<Node>>>::iterator __l;
        vector<matrix>::iterator __w;
        vector<shared_ptr<Node>>::iterator __np, __nq;
        for (__l = layers.begin(), __w = weights.begin(); __l < layers.end() - 1 && __w < weights.end(); __l++, __w++)
        {
            for (__np = __l->begin(); __np < __l->end(); __np++)
            {
                for (__nq = (__l + 1)->begin(); __nq < (__l + 1)->end(); __nq++)
                {
                    (*__np)->neighbors.push_back(*__nq);
                    (*__np)->weights.push_back(
                        (*__w)(__np - __l->begin(), __nq - (__l+1)->begin())
                    );
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