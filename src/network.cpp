#include "boltzmann/network.hpp"

namespace boltzmann
{
    Network::Network()
    {
        srand((unsigned)time(0));

#ifdef WITH_BOOST_MC_RNG
        // Set up the uniform generator using Boost
        boltzmann::mcEngine mcrng(rand()); // Seed the Mersenne generator
        boltzmann::mcDistribution uniform(0.0, 1.0);
        boltzmann::mcVariateGenerator mcgen(mcrng, uniform);

        mcGenerator = &mcgen;
#endif
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
    Network::Network(int _nlayers, vector<int> _lsizes, boltzFloat_t _temp)
    {
        srand((unsigned)time(0));

#ifdef WITH_BOOST_MC_RNG
        // Set up the uniform generator using Boost
        boltzmann::mcEngine mcrng(rand()); // Seed the Mersenne generator
        boltzmann::mcDistribution uniform(0.0, 1.0);
        boltzmann::mcVariateGenerator mcgen(mcrng, uniform);

        // Have to do this because of the template constructor
        mcGenerator = &mcgen;
#endif

        // This is a Metropolis-Hastings algorithm so seed well
        boost::random::mt19937_64 wtrng(rand()); // Seed the Mersenne generator
        boost::random::normal_distribution<boltzFloat_t> normal(0.0, 1.0);
        boost::random::variate_generator<
            boost::random::mt19937_64 &,
            boost::random::normal_distribution<boltzFloat_t>
        > normGenerator(wtrng, normal);

        /* Initialize matrix and weights */
        int _index = 0;
        for (int _l = 0; _l < _nlayers - 1; _l++)
        {
            // Create the matrix for the weight from _l to _l + 1
#ifdef USE_BOOST_UBLAS
            weights.push_back(matrix(_lsizes[_l], _lsizes[_l + 1], (boltzFloat_t) 0.0));
#else
            weights.push_back(new boltzFloat_t[_lsizes[_l]*_lsizes[_l + 1]]);
#endif
            for (int __mi = 0; __mi < _lsizes[_l]; __mi++)
                for (int __mj = 0; __mj < _lsizes[_l+1]; __mj++)
#ifdef USE_BOOST_UBLAS
                    weights[_l](__mi, __mj) = normGenerator();
#else
                    weights[_l][__mi*_lsizes[_l+1] + __mj] = normGenerator();
#endif

            // Create the nodes for layer _l
            vector<shared_ptr<Node>> temp(_lsizes[_l]);
            for (int _n = 0; _n < _lsizes[_l]; _n++)
#ifdef WITH_BOOST_MC_RNG
                temp[_n] = shared_ptr<Node>(new Node(_index++, _l, mcGenerator));
#else
                temp[_n] = shared_ptr<Node>(new Node(_index++, _l));
#endif
            
            // Add it to the list of layers
            layers.push_back(temp);
        }

        // Create the final layer of nodes; not included above
        vector<shared_ptr<Node>> temp(_lsizes[_nlayers-1]);
        for (int _n = 0; _n < _lsizes[_nlayers-1]; _n++)
#ifdef WITH_BOOST_MC_RNG
            temp[_n] = shared_ptr<Node>(new Node(_index++, _nlayers - 1, mcGenerator));
#else
            temp[_n] = shared_ptr<Node>(new Node(_index++, _nlayers - 1));
#endif
        layers.push_back(temp);

        // Set the final size of the system; number of nodes
        size = _index;

        /* Now point weights to individual nodes */
        vector<vector<shared_ptr<Node>>>::iterator __lf;
        vector<vector<shared_ptr<Node>>>::reverse_iterator __lr;
#ifdef USE_BOOST_UBLAS
        vector<matrix>::iterator __wf;
        vector<matrix>::reverse_iterator __wr;
#else
        vector<boltzFloat_t*>::iterator __wf;
        vector<boltzFloat_t*>::reverse_iterator __wr;
#endif
        vector<shared_ptr<Node>>::iterator __np, __nq;
        for (__lf = layers.begin(), __wf = weights.begin(); __lf < layers.end() - 1 && __wf < weights.end(); __lf++, __wf++)
        {
            for (__np = __lf->begin(); __np < __lf->end(); __np++)
            {
                for (__nq = (__lf + 1)->begin(); __nq < (__lf + 1)->end(); __nq++)
                {
                    (*__np)->neighbors.push_back(*__nq);
                    (*__np)->weights.push_back(
#ifdef USE_BOOST_UBLAS
                        (*__wf)(__np - __lf->begin(), __nq - (__lf + 1)->begin())
#else
                        (*__wf)[(__np - __lf->begin()) * (__lf + 1)->size() + (__nq - (__lf + 1)->begin())]
#endif
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
#ifdef USE_BOOST_UBLAS
                        (*__wr)(__nq - (__lr+1)->begin(), __np - __lr->begin())
#else
                        (*__wr)[(__nq - (__lr+1)->begin()) * __lr->size() + (__np - __lr->begin())]
#endif
                    );
                }
            }
        }
    }

    Network::~Network()
    {
#ifdef USE_BOOST_UBLAS
        // The Boost ublas data structures should clean themselves up
#else
        // But we need to clean up the arrays
        while(weights.size() > 0)
        {
            delete [] weights.back();
            weights.pop_back();
        }
#endif
    }

    void Network::initLayerState(int _layer)
    {
        
    }

    void Network::setLayerState(int _layer, vector<int> _state)
    {
        for (auto _tup : boost::combine(layers[_layer], _state))
        {
            shared_ptr<Node> _nodeptr;
            int _state;
            boost::tie(_nodeptr, _state) = _tup;
            _nodeptr->state = _state;
        }
    }

    void Network::updateLayerState(int _layer)
    {
        // Number of nodes in the input and output layers
        int numOutNodes = layers[_layer].size();
        int numInNodes = layers[_layer-1].size();

        // Cast everything into linear algebra
#ifdef USE_BOOST_UBLAS
        matrix activations(1, numInNodes, 0.0);
        for (int i = 0; i < numInNodes; i++)
            activations(0, i) = layers[_layer-1][i]->state;
        matrix biases(1, numOutNodes, 0.0);
        for (int i = 0; i < numOutNodes; i++)
            biases(0, i) = layers[_layer][i]->bias;
            
        // Grab the resulting activations
        auto result = boost::numeric::ublas::prod(activations, weights[_layer-1]) + biases;
#else
        // Here result should be allocated on the stack
        boltzFloat_t result[numOutNodes];
        for (int i = 0; i < numOutNodes; i++)
        {
            result[i] = layers[_layer][i]->bias;
            for (int j = 0; j < numInNodes; j++)
                result[i] += layers[_layer-1][j]->state * weights[_layer-1][j*numOutNodes+i];
        }
#endif

        // Insert the result into the node->states
        for (int row = 0; row < numOutNodes; row++)
        {
            // Invoke Metropolis-Hastings here for each
            layers[_layer][row]->state = __get_wts_elem(result, numOutNodes, 0, row); // B/c row height numOutNodes

            // Take one Monte Carlo step (needs to be tuned still)
            boltzFloat_t _prob =
                layers[_layer][row]
                    ->activation(
                        __get_wts_elem(result, numOutNodes, 0, row), // B/c row height numOutNodes
                        temperature
                    );
#ifdef WITH_BOOST_MC_RNG
            boltzFloat_t _rand = (*mcGenerator)();
#else
            boltzFloat_t _rand = (boltzFloat_t)rand() / (boltzFloat_t)RAND_MAX;
#endif
            if (_rand < _prob)
                layers[_layer][row]->state = 1;
            else
                layers[_layer][row]->state = 0;
        }
    }

    void Network::updateLayerStateBack(int _layer)
    {
        // Number of nodes in the input and output layers
        int numOutNodes = layers[_layer].size();
        int numInNodes = layers[_layer+1].size();

        // Cast everything into linear algebra
#ifdef USE_BOOST_UBLAS
        matrix activations(numInNodes, 1, 0.0); // Matrix dims transposed relative to forward
        for (int i = 0; i < numInNodes; i++)
            activations(i, 0) = layers[_layer+1][i]->state;
        matrix biases(numOutNodes, 1, 0.0); // Matrix dims transposed relative to forward
        for (int i = 0; i < numOutNodes; i++)
            biases(i, 0) = layers[_layer][i]->bias;

        // Grab the resulting activations; _layer+1-1 b/c _layer+1 weights are at _layer
        auto result = boost::numeric::ublas::prod(weights[_layer+1-1], activations) + biases;
#else
        // Here result should be allocated on the stack
        boltzFloat_t result[numOutNodes];
        for (int i = 0; i < numOutNodes; i++)
        {
            result[i] = layers[_layer][i]->bias;
            for (int j = 0; j < numInNodes; j++)
                result[i] += weights[_layer+1-1][i*numInNodes+j] * layers[_layer+1][j]->state;
        }
#endif

        // Insert the result into the node->states
        for (int row = 0; row < numOutNodes; row++)
        {
            // Invoke Metropolis-Hastings here for each
            layers[_layer][row]->state = __get_wts_elem(result, 1, row, 0); // B/c row height 1

            // Take one Monte Carlo step (needs to be tuned still)
            boltzFloat_t _prob =
                layers[_layer][row]
                    ->activation(
                        __get_wts_elem(result, 1, row, 0), // B/c row height 1
                        temperature
                    );
#ifdef WITH_BOOST_MC_RNG
            boltzFloat_t _rand = (*mcGenerator)();
#else
            boltzFloat_t _rand = (boltzFloat_t)rand() / (boltzFloat_t)RAND_MAX;
#endif
            if (_rand < _prob)
                layers[_layer][row]->state = 1;
            else
                layers[_layer][row]->state = 0;
        }
    }

    // Set the weight symmetrically; assumes that you're giving the layer in
    // which the source node lives first
    void Network::setNodeWeight(int _layer, int _node, int _neighbor, boltzFloat_t _weight)
    {
        int lsize = layers[_layer + 1].size();
        //weights[_layer](_node, _neighbor) = _weight;
        //weights[_layer][_node * lsize + _neighbor] = _weight;
        __get_wts_elem(weights[_layer], lsize, _node, _neighbor) = _weight;
        layers[_layer][_node]->weights[_neighbor] = _weight;
        layers[_layer + 1][_neighbor]->bweights[_node] = _weight;
    }

    void Network::initLayerWeights(int _layer)
    {

    }

    void trainNetworkCDStep(int _cdOrder, vector<int> _input)
    {

    }

    std::string Network::toString()
    {
        std::ostringstream strs;
        strs << "Layers:   " << std::setw(10) << layers.size() << std::endl;
        strs << "Nodes:    " << std::setw(10) << size << endl;
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