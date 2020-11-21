#ifndef BOLTZMANN_NODE_HPP
#define BOLTZMANN_NODE_HPP

#include <string>
#include <vector>

#include <boost/container/vector.hpp>
#include <boost/array.hpp>

namespace boltzmann
{
    template<class T, int N>
    class Node
    {
    public:
        Node();

        /**
         * @brief Construct a new Node object
         * @param id The ID of the node to initialize to
         */
        Node(int id);

        /**
         * @brief Construct a new Node with a name
         * @param name The name of the node to initialize to
         */
        Node(std::string name);

        /**
         * @brief Construct a new Node with name and id
         * @param id The ID to initialize to
         * @param name The name to initialize to
         */
        Node(int id, std::string name);

        ~Node();

        /**
         * @brief Set the name of the Node
         * @param name The name to set it to
         */
        void setName(std::string name);

        /**
         * @brief Get the name of the Node
         * @return The string containing the name of the Node
         */
        std::string getName();

        /**
         * @brief Set the ID of the Node
         * @param id The id to set it to
         */
        void setId(int id);

        /**
         * @brief Get the the ID of the Node
         * @return The integer containing the ID
         */
        int getId();

        int getLayerId();

    private:
        /// @brief The ID of a node
        int nodeId = -1;

        /// @brief Optional node name; use for better readability
        std::string nodeName;

        /// @brief The ID of the layer in which it lives.
        /// The layerId is default set to -1 to indicate
        /// that it doesn't belong to a layer at the time
        int layerId = -1;

        /// @brief Contains the state parameters for the node.
        /// Examples of this include the bias parameter for
        /// a given node; this is a generalization of the bias
        /// to account for unforeseen configurations
        boost::array<T, N> stateParams;
    };

    template<class T, int N>
    Node<T, N>::Node()
    {
        stateParams.fill((T)0.0);
    }

    template<class T, int N>
    Node<T, N>::Node(int id)
    {
        nodeId = id;
        stateParams.fill((T)0.0);
    }

    template<class T, int N>
    Node<T, N>::Node(std::string name)
    {
        nodeName = name;
        stateParams.fill((T)0.0);
    }

    template<class T, int N>
    Node<T, N>::Node(int id, std::string name)
    {
        nodeId = id;
        nodeName = name;
        stateParams.fill((T)0.0);
    }

    template<class T, int N>
    Node<T, N>::~Node()
    {
        
    }
}

#endif