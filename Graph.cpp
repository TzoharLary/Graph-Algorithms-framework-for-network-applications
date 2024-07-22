// Mail: tzohary1234@gmail.com
// Author: Tzohar Lary

#include "Graph.hpp"
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;
using namespace ariel;

void Graph::loadGraph(const vector<vector<int>>& matrix) {
    if (matrix.empty() || (matrix.size() == 1 && matrix[0].empty())) {
        throw invalid_argument("Graph is empty");
    }
    size_t size = matrix.size();
    adjacencyMatrix = matrix;
}

bool Graph::isEmpty() const {
    return adjacencyMatrix.empty();
}

void Graph::addNode() {
    int size = adjacencyMatrix.size();
    for (auto& row : adjacencyMatrix) {
        row.push_back(0);
    }
    adjacencyMatrix.push_back(vector<int>(size + 1, 0));
}

void Graph::removeNode() {
    if (!adjacencyMatrix.empty()) {
        adjacencyMatrix.pop_back();
        for (auto& row : adjacencyMatrix) {
            row.pop_back();
        }
    }
}

void Graph::setEdge(int fromNode, int toNode, int value) {
    if (fromNode < 0 || fromNode >= adjacencyMatrix.size() || toNode < 0 || toNode >= adjacencyMatrix.size()) {
        throw out_of_range("Index out of range");
    }
    adjacencyMatrix[fromNode][toNode] = value;
}

const vector<vector<int>>& Graph::getAdjacencyMatrix() const {
    return adjacencyMatrix;
}

std::string Graph::printGraph() const {
    std::ostringstream oss;
    for (const auto& row : adjacencyMatrix) {
        oss << "[";
        for (size_t i = 0; i < row.size(); ++i) {
            oss << row[i];
            if (i != row.size() - 1) {
                oss << ", ";
            }
        }
        oss << "]\n";
    }
    std::string result = oss.str();
    if (!result.empty()) {
        // Remove the last newline character
        result.pop_back();
    }
    return result;
}

// Operator overloads
std::ostream& ariel::operator<<(std::ostream& outputStream, const Graph& graph) {
    for (const auto& row : graph.getAdjacencyMatrix()) {
        for (const auto& value : row) {
            outputStream << value << " ";
        }
        outputStream << "\n";
    }
    return outputStream;
}

Graph Graph::operator+(const Graph& other) const {
    if (adjacencyMatrix.size() != other.adjacencyMatrix.size()) {
        throw invalid_argument("Graphs must be of the same size to add");
    }
    Graph result;
    result.adjacencyMatrix = adjacencyMatrix;
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
            result.adjacencyMatrix[i][j] += other.adjacencyMatrix[i][j];
        }
    }
    return result;
}

Graph& Graph::operator+=(const Graph& other) {
    *this = *this + other;
    return *this;
}

Graph Graph::operator+() const {
    return *this;
}

Graph Graph::operator-(const Graph& other) const {
    if (adjacencyMatrix.size() != other.adjacencyMatrix.size()) {
        throw invalid_argument("Graphs must be of the same size to subtract");
    }
    Graph result;
    result.adjacencyMatrix = adjacencyMatrix;
    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
        for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
            result.adjacencyMatrix[i][j] -= other.adjacencyMatrix[i][j];
        }
    }
    return result;
}

Graph& Graph::operator-=(const Graph& other) {
    *this = *this - other;
    return *this;
}

Graph Graph::operator-() const {
    Graph result = *this;
    for (auto& row : result.adjacencyMatrix) {
        for (auto& val : row) {
            val = -val;
        }
    }
    return result;
}

bool Graph::operator==(const Graph& other) const {
    return adjacencyMatrix == other.adjacencyMatrix;
}

bool Graph::operator!=(const Graph& other) const {
    return !(*this == other);
}

bool Graph::operator<(const Graph& other) const {
    if (adjacencyMatrix.size() < other.adjacencyMatrix.size()) {
        return true;
    }
    if (adjacencyMatrix.size() > other.adjacencyMatrix.size()) {
        return false;
    }
    return adjacencyMatrix < other.adjacencyMatrix;
}

bool Graph::operator<=(const Graph& other) const {
    return *this < other || *this == other;
}

bool Graph::operator>(const Graph& other) const {
    return !(*this <= other);
}

bool Graph::operator>=(const Graph& other) const {
    return !(*this < other);
}

Graph Graph::operator++(int) {
    Graph temp = *this; // Save current state

    size_t n = adjacencyMatrix.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            adjacencyMatrix[i][j]++;
        }
    }

    // Reset the main diagonal after incrementing
    for (size_t i = 0; i < n; ++i) {
        adjacencyMatrix[i][i] = 0;
    }

    return temp;
}

Graph& Graph::operator++() {
    size_t n = adjacencyMatrix.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            adjacencyMatrix[i][j]++;
        }
    }

    // Reset the main diagonal after incrementing
    for (size_t i = 0; i < n; ++i) {
        adjacencyMatrix[i][i] = 0;
    }

    return *this;
}

Graph Graph::operator--(int) {
    Graph temp = *this; // Save current state

    size_t n = adjacencyMatrix.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i != j) { // Decrement all values except the main diagonal
                adjacencyMatrix[i][j]--;
            }
        }
    }

    // Reset the main diagonal to 0
    for (size_t i = 0; i < n; ++i) {
        adjacencyMatrix[i][i] = 0;
    }

    return temp;
}

Graph& Graph::operator--() {
    size_t n = adjacencyMatrix.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i != j) { // Decrement all values except the main diagonal
                adjacencyMatrix[i][j]--;
            }
        }
    }

    // Reset the main diagonal to 0
    for (size_t i = 0; i < n; ++i) {
        adjacencyMatrix[i][i] = 0;
    }

    return *this;
}

Graph Graph::operator*(const Graph& other) const {
    size_t n = adjacencyMatrix.size();

    // Check if both matrices are square and of the same size
    if (n != adjacencyMatrix[0].size() || n != other.adjacencyMatrix.size() || n != other.adjacencyMatrix[0].size()) {
        throw invalid_argument("Both matrices must be square and of the same size.");
    }

    Graph result;
    result.adjacencyMatrix.resize(n, vector<int>(n, 0));

    // Multiply the matrices
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (size_t k = 0; k < n; ++k) {
                result.adjacencyMatrix[i][j] += adjacencyMatrix[i][k] * other.adjacencyMatrix[k][j];
            }
        }
    }

    // Reset the main diagonal
    for (size_t i = 0; i < n; ++i) {
        result.adjacencyMatrix[i][i] = 0;
    }

    return result;
}

Graph& Graph::operator*=(int scalar) {
    for (auto& row : adjacencyMatrix) {
        for (auto& val : row) {
            val *= scalar;
        }
    }
    return *this;
}

Graph& Graph::operator/=(int scalar) {
    if (scalar == 0) {
        throw invalid_argument("Division by zero");
    }
    for (auto& row : adjacencyMatrix) {
        for (auto& val : row) {
            val /= scalar;
        }
    }
    return *this;
}
