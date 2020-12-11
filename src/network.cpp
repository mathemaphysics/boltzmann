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
            weights.push_back(matrix(_lsizes[_l], _lsizes[_l + 1], (boltzFloat_t) 0.0));

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
        vector<vector<shared_ptr<Node>>>::iterator __lf;
        vector<vector<shared_ptr<Node>>>::reverse_iterator __lr;
        vector<matrix>::iterator __wf;
        vector<matrix>::reverse_iterator __wr;
        vector<shared_ptr<Node>>::iterator __np, __nq;
        for (__lf = layers.begin(), __wf = weights.begin(); __lf < layers.end() - 1 && __wf < weights.end(); __lf++, __wf++)
        {
            for (__np = __lf->begin(); __np < __lf->end(); __np++)
            {
                for (__nq = (__lf + 1)->begin(); __nq < (__lf + 1)->end(); __nq++)
                {
                    (*__np)->neighbors.push_back(*__nq);
                    (*__np)->weights.push_back(
                        (*__wf)(__np - __lf->begin(), __nq - (__lf+1)->begin())
                    );
                }
            }
        }
        for (__lr = layers.rbegin(), __wr = weights.rbegin(); __lr < layers.rend() - 1 && __wr < weights.rend(); __lr++, __wr++)
        {
            for (__np = __lr->begin(); __np < __lr->end(); __np++)
            {
                for (__nq = (__lr + 1)->begin(); __nq < (__lr + 1)->end(); __nq++)
                {
                    (*__np)->bneighbors.push_back(*__nq);
                    (*__np)->bweights.push_back(
                        (*__wr)(__nq - (__lr+1)->begin(), __np - __lr->begin())
                    );
                }
            }
        }
#endif
    }

    Network::~Network()
    {
        
    }

    void Network::initLayerState(int _layer)
    {
        
    }

    void Network::setLayerState(int _layer)
    {

    }

    void Network::updateLayerState(int _layer)
    {
        int numNodes = layers[_layer].size();
        matrix activations(numNodes, 1, 0.0);
        cout << activations << endl;
        cout << weights[_layer-1] << endl;
        auto result = boost::numeric::ublas::prod(weights[_layer-1], activations);
        cout << result << endl;
        for (int row = 0; row < numNodes; row++)
        {

        }
    }

    // Set the weight symmetrically; assumes that you're giving the layer in
    // which the source node lives first
    void Network::setWeight(int _layer, int _node, int _neighbor, boltzFloat_t _weight)
    {
        weights[_layer](_node, _neighbor) = _weight;
        layers[_layer][_node]->weights[_neighbor] = _weight;
        layers[_layer + 1][_neighbor]->bweights[_node] = _weight;
    }

    std::string Network::toString()
    {
        std::ostringstream strs;
        strs << "Layers:   " << std::setw(10) << layers.size() << std::endl;
        strs << "Nodes:    " << std::setw(10) << size << endl;;
        strs << "Internal: " << endl;
        strs << endl;
        strs << "Layers: " << endl;
        for (int _l = 0; _l < layers.size(); _l++)
        {
            strs << "Layer " << setw(5) << _l << ": " << endl;
            for (auto node : layers[_l])
                strs << node->toString() << endl;
        }
        return strs.str();
    }
}