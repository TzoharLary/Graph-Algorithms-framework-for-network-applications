// Mail: tzohary1234@gmail.com
// Author: Tzohar Lary

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>

namespace ariel {

    class Graph {
    private:
        std::vector<std::vector<int>> adjacencyMatrix;

    public:
        void loadGraph(const std::vector<std::vector<int>>& matrix);
        bool isEmpty() const;
        void addNode();
        void removeNode();
        void setEdge(int fromNode, int toNode, int value);
        const std::vector<std::vector<int>>& getAdjacencyMatrix() const;
        std::string printGraph() const;


        // All the following operators with reference, it for avoid copy of the object and affect time complexity
        // all the const functions are for avoid changing the object
        
        Graph operator+(const Graph& other) const; // Matrix addition
        Graph& operator+=(const Graph& other); // Matrix addition 
        Graph operator+() const; // Unary plus operator - returns the original value of the graph (no change)
        Graph operator-(const Graph& other) const; // Matrix subtraction
        Graph& operator-=(const Graph& other); // Matrix subtraction
        Graph operator-() const; // Unary minus operator - returns the negative value of the graph (all values multiplied by -1)
        bool operator==(const Graph& other) const; // Matrix equality check
        bool operator!=(const Graph& other) const; // Matrix inequality check
        bool operator<(const Graph& other) const; // Matrix less than check
        bool operator<=(const Graph& other) const; // Matrix less than or equal to check
        bool operator>(const Graph& other) const; // Matrix greater than check
        bool operator>=(const Graph& other) const; // Matrix greater than or equal to check
        Graph operator++(int); // Postfix increment operator - returns the original value before increment
        Graph& operator++(); // Prefix increment operator - returns the value after increment
        Graph operator--(int); // Postfix decrement operator - returns the original value before decrement
        Graph& operator--(); // Prefix decrement operator - returns the value after decrement
        Graph operator*(const Graph& other) const; // Matrix multiplication
        Graph& operator*=(int scalar); // Scalar multiplication
        Graph& operator/=(int scalar); // Scalar division
    };

    std::ostream& operator<<(std::ostream& outputStream, const Graph& graph);

}

#endif // GRAPH_HPP
