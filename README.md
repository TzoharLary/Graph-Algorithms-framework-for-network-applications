# Graph Algorithms framework for network applications

## Author:
Tzohar Lary

## Email:
tzohary1234@gmail.com

## Project Description
This project deals with graph algorithms, including finding the shortest path, detecting negative cycles, checking if a graph is bipartite, and more. Additionally, the `Graph` class has been extended with various operator overloads to facilitate easy manipulation and comparison of graphs. These include addition, subtraction, multiplication, increment, decrement, and comparison operators.

## Installation and Running
To run the project, you need to use the clang++ compiler and run the following commands:

1. **Clone the Repository**: First, you need to clone the repository to your local machine. Open a terminal and run the following command:

    ```bash
    git clone https://github.com/TzoharLary/Systems-Programming-2-Task-1.git
    ```

2. **Navigate to the Project Directory**: Change your current directory to the project directory:

    ```bash
    cd Systems_Programming-2_Task-2
    ```

3. **Build the Project**: You can build the project using the `make` command:

    ```bash
    make
    ```

4. **Clean the Project**: If you want to clean the project (remove all the build files), you can use the following command:

    ```bash
    make clean
    ```
## Testing
The project includes 19 different test cases to verify the functionality of the algorithms,These tests now also include verification of the newly added operator overloads in the `Graph` class, such as addition, subtraction, multiplication, increment, decrement, and comparison operators. To run the tests, use the following commands:
```bash
make test
./test
```
    
## Demo
To run the demo, use the following command in the terminal:

```bash
make demo
```

## Classes

### Graph
The `Graph` class represents a graph using an adjacency matrix. It provides methods to load a graph, add or remove nodes, set edges, and retrieve the adjacency matrix. Key methods include:

1. `void loadGraph(const vector<vector<int>>& matrix)`: Loads a graph from an adjacency matrix.
2. `bool isEmpty() const`: Checks if the graph is empty.
3. `void addNode()`: Adds a node to the graph.
4. `void removeNode()`: Removes a node from the graph.
5. `void setEdge(int fromNode, int toNode, int value)`: Sets the value of an edge in the graph.
6. `const vector<vector<int>>& getAdjacencyMatrix() const`: Returns the adjacency matrix.
7. `string printGraph() const`: Prints the adjacency matrix of the graph.
8. Overloaded operators to manipulate graphs (`+`, `-`, `*`, etc.).

#### Operator Overloads
- `Graph operator+(const Graph& other) const`: Adds two graphs.
- `Graph& operator+=(const Graph& other)`: Adds another graph to the current graph.
- `Graph operator-() const`: Negates the graph.
- `Graph operator-(const Graph& other) const`: Subtracts one graph from another.
- `Graph& operator-=(const Graph& other)`: Subtracts another graph from the current graph.
- `Graph operator*(const Graph& other) const`: Multiplies two graphs.
- `Graph& operator*=(int scalar)`: Multiplies the graph by a scalar.
- `Graph& operator/=(int scalar)`: Divides the graph by a scalar.
- `bool operator==(const Graph& other) const`: Checks if two graphs are equal.
- `bool operator!=(const Graph& other) const`: Checks if two graphs are not equal.
- `bool operator<(const Graph& other) const`: Checks if one graph is less than another.
- `bool operator<=(const Graph& other) const`: Checks if one graph is less than or equal to another.
- `bool operator>(const Graph& other) const`: Checks if one graph is greater than another.
- `bool operator>=(const Graph& other) const`: Checks if one graph is greater than or equal to another.
- `Graph operator++(int)`: Increments all edges of the graph.
- `Graph& operator++()`: Increments all edges of the graph and resets the main diagonal to zero.
- `Graph operator--(int)`: Decrements all edges of the graph except the main diagonal.
- `Graph& operator--()`: Decrements all edges of the graph except the main diagonal.

The `Graph` class uses several data structures like vectors and provides methods to manipulate and analyze graph properties.


### Algorithms
The `Algorithms` class provides various static methods to perform graph algorithms. Key methods include:

1. `string Algorithms::shortestPath(const Graph& g, int start, int end)`: This function calculates the shortest path between two nodes in a graph using the Bellman-Ford algorithm. If no path is found, it returns "-1".

2. `bool Algorithms::isContainsCycle(const Graph& g)`: This function checks if the graph contains a cycle using Depth-First Search (DFS).

3. `std::string Algorithms::isBipartite(const Graph& g)`: This function checks if the graph is bipartite and returns a string representing the two sets if it is.

4. `bool Algorithms::isDirected(const Graph& g)`: This function checks if the graph is directed by comparing the values in the adjacency matrix.

5. `string Algorithms::negativeCycle(const Graph& g)`: This function checks for a negative cycle in the graph using the Bellman-Ford algorithm. It uses the `hasNegativeEdge` function to determine if there are negative edges in the graph.

6. `bool Algorithms::bellmanFord(const Graph& g, vector<int>& dist)`: This function runs the Bellman-Ford algorithm on the graph and returns whether a negative cycle was found.

7. `bool Algorithms::hasNegativeEdge(const Graph& g, vector<int>& dist)`: This function checks if the graph contains any negative edges.

7. `bool Algorithms::hasNegativeCycle(const Graph& g, const vector<int>& dist)`: This function checks for a negative cycle in the graph after running the Bellman-Ford algorithm.

8. `void Algorithms::relax(const Graph& g, vector<int>& dist, vector<int>& parent)`: This function performs edge relaxation in the graph as part of the Bellman-Ford algorithm.

9. `bool Algorithms::isConnected(const Graph& g)`: This function checks if the graph is connected, meaning there is a path between every pair of nodes.

10. `void Algorithms::dfs(const Graph& g, size_t node, vector<bool>& visited, size_t n)`: This function performs Depth-First Search (DFS) on the graph to check connectivity.

The code uses several data structures like vectors and queues, and it also uses concepts like graph theory and algorithms like DFS (Depth-First Search) and the Bellman-Ford algorithm.
