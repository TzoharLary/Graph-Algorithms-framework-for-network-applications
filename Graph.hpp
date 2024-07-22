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

        Graph operator+(const Graph& other) const;
        Graph& operator+=(const Graph& other);
        Graph operator+() const; // Unary plus operator
        Graph operator-(const Graph& other) const;
        Graph& operator-=(const Graph& other);
        Graph operator-() const;
        bool operator==(const Graph& other) const;
        bool operator!=(const Graph& other) const;
        bool operator<(const Graph& other) const;
        bool operator<=(const Graph& other) const;
        bool operator>(const Graph& other) const;
        bool operator>=(const Graph& other) const;
        Graph operator++(int);
        Graph& operator++();
        Graph operator--(int);
        Graph& operator--();
        Graph operator*(const Graph& other) const;
        Graph& operator*=(int scalar);
        Graph& operator/=(int scalar);
    };

    std::ostream& operator<<(std::ostream& outputStream, const Graph& graph);

}

#endif // GRAPH_HPP
